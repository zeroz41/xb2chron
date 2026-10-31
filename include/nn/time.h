#ifndef NN_TIME_H
#define NN_TIME_H

namespace nn { namespace time {
// the SDK's time library (ml::DeviceNx::initializeSDK starts it, ~DeviceNx ends it)
void Initialize();
void Finalize();
}}  // namespace nn::time

#endif
