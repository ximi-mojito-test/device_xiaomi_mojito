/*
 * Copyright (C) 2022 PixelExperience
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <vector>

#include <android-base/properties.h>
#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/_system_properties.h>
#include <sys/sysinfo.h>

using android::base::GetProperty;

void property_override(char const prop[], char const value[], bool add = true) {
    prop_info* pi;

    pi = (prop_info*)__system_property_find(prop);
    if (pi)
        __system_property_update(pi, value, strlen(value));
    else if (add)
        __system_property_add(prop, strlen(prop), value, strlen(value));
}

void load_dalvikvm_props() {
    struct sysinfo sys;
    sysinfo(&sys);

    if (sys.totalram > 5072ull * 1024 * 1024) {
        // from - phone-xhdpi-6144-dalvik-heap.mk
        property_override("dalvik.vm.heapstartsize", "16m");
        property_override("dalvik.vm.heapgrowthlimit", "256m");
        property_override("dalvik.vm.heaptargetutilization", "0.5");
        property_override("dalvik.vm.heapmaxfree", "32m");
    } else if (sys.totalram > 3072ull * 1024 * 1024) {
        // from - phone-xhdpi-4096-dalvik-heap.mk
        property_override("dalvik.vm.heapstartsize", "8m");
        property_override("dalvik.vm.heapgrowthlimit", "192m");
        property_override("dalvik.vm.heaptargetutilization", "0.6");
        property_override("dalvik.vm.heapmaxfree", "16m");
    }

    property_override("dalvik.vm.heapsize", "512m");
    property_override("dalvik.vm.heapminfree", "8m");
}

void load_vendor_props() {

    const char *board_fp = "Redmi/mojito/mojito:12/SKQ1.210908.001/V14.0.9.0.SKGMIXM:user/release-keys";
    const char *product_name = "mojito";

    property_override("bluetooth.device.default_name", "Redmi Note 10");
    property_override("vendor.usb.product_string", "Redmi Note 10");
    property_override("ro.product.brand", "Redmi");
    property_override("ro.product.manufacturer", "Xiaomi");
    property_override("ro.product.model", "M2101K7AI");
    property_override("ro.build.description", "mojito-user 12 SKQ1.210908.001 V14.0.9.0.SKGMIXM release-keys");

    property_override("ro.boot.hwname", product_name);
    property_override("ro.boot.product.hardware.sku", product_name);
    property_override("ro.build.product", product_name);
    property_override("ro.product.bootimage.device", product_name);
    property_override("ro.product.bootimage.name", product_name);
    property_override("ro.product.device", product_name);
    property_override("ro.product.name", product_name);
    property_override("ro.product.odm.device", product_name);
    property_override("ro.product.product.device", product_name);
    property_override("ro.product.system.device", product_name);
    property_override("ro.product.system_ext.device", product_name);
    property_override("ro.product.vendor.device", product_name);
    property_override("ro.product.vendor_dlkm.device", product_name);

    property_override("ro.bootimage.build.fingerprint", board_fp);
    property_override("ro.build.fingerprint", board_fp);
    property_override("ro.odm.build.fingerprint", board_fp);
    property_override("ro.product.build.fingerprint", board_fp);
    property_override("ro.system.build.fingerprint", board_fp);
    property_override("ro.system_ext.build.fingerprint", board_fp);
    property_override("ro.vendor.build.fingerprint", board_fp);
    property_override("ro.vendor_dlkm.build.fingerprint", board_fp);

}

void vendor_load_properties() {
    std::string region = GetProperty("ro.boot.hwc", "");
    load_vendor_props();
    load_dalvikvm_props();
}
