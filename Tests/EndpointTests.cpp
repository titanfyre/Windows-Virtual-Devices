#include "VirtualDevice.h"
#include <iostream>
#include <stdexcept>
#include <utility>

namespace VirtualDevice::Detail {
// Internal SDK helper exercised without opening a driver or creating a device.
std::pair<std::uint8_t,std::uint8_t> Input_Endpoint(const Device_Config&) noexcept;
}

namespace {
void Require(bool value,const char* message) {
    if (!value) throw std::runtime_error(message);
}
VirtualDevice::Device_Config Config(std::initializer_list<std::uint8_t> endpoints) {
    VirtualDevice::Device_Config result;
    VirtualDevice::Descriptor device;
    device.data={18,1,0,2,0,0,0,64,0xff,0xff,1,0,0,1,0,0,0,1};
    VirtualDevice::Descriptor configuration;
    const auto total=static_cast<std::uint8_t>(18+7*endpoints.size());
    configuration.data={9,2,total,0,1,1,0,0x80,50,
        9,4,0,0,static_cast<std::uint8_t>(endpoints.size()),0xff,0,0,0};
    for (const auto address:endpoints)
        configuration.data.insert(configuration.data.end(),{7,5,address,3,64,0,1});
    result.descriptors={device,configuration};return result;
}
}

int main() {
    try {
        for (const auto& endpoints : {std::initializer_list<std::uint8_t>{}, {0x01}, {0x81}, {0x82,0x01}, {0x81,0x82}, {0x01,0x81,0x02,0x82}}) {
            const auto config=Config(endpoints);
            Require(bool(VirtualDevice::Check(config)),"A supported test layout was rejected.");
            const auto selection=VirtualDevice::Detail::Input_Endpoint(config);
            std::uint8_t count=0,first=0;
            for (const auto endpoint:endpoints) if (endpoint&0x80) {if (!count) first=endpoint;++count;}
            Require(selection.first==count && selection.second==first,"Input endpoint selection differs from the declared topology.");
        }
        VirtualDevice::Device inactive;
        const auto automatic=VirtualDevice::Send(inactive,{1,2,3});
        Require(!automatic && automatic.error==6 && automatic.message=="Device is not active.","Automatic Send did not reject an inactive device.");
        const auto explicitEndpoint=VirtualDevice::Send(inactive,0x81,{1,2,3});
        Require(!explicitEndpoint && explicitEndpoint.error==6,"Explicit Send did not reject an inactive device.");
        std::cout << "WindowsVirtualDevices endpoint selection and inactive-device checks passed; no driver opened.\n";
        return 0;
    } catch (const std::exception& error) {
        std::cerr << error.what() << '\n';return 1;
    }
}
