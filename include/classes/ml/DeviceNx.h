#ifndef CLASSES_ML_DEVICENX_H
#define CLASSES_ML_DEVICENX_H

#include "classes/ml/Device.h"

namespace ml {
// table 0x7100B76A18
class DeviceNx : public ::ml::Device {
public:
    // Device::create's WorkUtil::createWork<DeviceNx> builds it inline
    DeviceNx(const char* name, WorkObj* parent) : Device(name, parent) {}
    static void initializeSDK(const Device::InitParam& param);
    virtual ~DeviceNx();  // slot 0
    virtual void createDevice();  // slot 17
    virtual void createDevicePort(char const*);  // slot 18

    // initializeSDK ran (set at its end; the destructor finalizes the SDK and clears it)
    static bool m_onceInitialize;
};
}  // namespace ml

#endif
