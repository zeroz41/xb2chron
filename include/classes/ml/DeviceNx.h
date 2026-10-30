#ifndef CLASSES_ML_DEVICENX_H
#define CLASSES_ML_DEVICENX_H

#include "classes/ml/Device.h"

namespace ml {
// table 0x7100B76A18
class DeviceNx : public ::ml::Device {
public:
    static void initializeSDK(const Device::InitParam& param);
    virtual ~DeviceNx();  // slot 0
    virtual void createDevice();  // slot 17
    virtual void createDevicePort(char const*);  // slot 18
};
}  // namespace ml

#endif
