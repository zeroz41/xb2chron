#ifndef CLASSES_ML_DEVPERFNX_H
#define CLASSES_ML_DEVPERFNX_H

#include "classes/ml/DevPerf.h"
#include "classes/ml/WorkCpu.h"
#include "nn/oe.h"

namespace ml {
// the base at 0x8: ml::DevPerfNx's destructor passes it to WorkCpu::removeSystemInfoListener(IWorkInfomation*)
class IWorkInfomation {
public:
    virtual ~IWorkInfomation() {}
    virtual void changeOperationMode(DevPerfOperationMode mode) = 0;
    virtual void changePerformanceMode(DevPerfMode mode) = 0;
    virtual void resumeApplication() = 0;
};

// table 0x7100B76808
class DevPerfNx : public TUnk_B76808, public IWorkInfomation {
public:
    // inline: ml::DeviceNx::createDevice builds it (the original has no out-of-line copy)
    DevPerfNx() {
        m_operationMode = DevPerfOperationMode(nn::oe::GetOperationMode() != 0);
        m_performanceMode = DevPerfMode(nn::oe::GetPerformanceMode() == 1 ? 2 : 1);
        m_perfConfig[0] = DevPerfConfig(0);
        m_perfConfig[1] = DevPerfConfig(0);
        m_perfConfig[2] = DevPerfConfig(2);
        WorkCpu::addSystemInfoListener(this);
        nn::oe::SetOperationModeChangedNotificationEnabled(true);
        nn::oe::SetPerformanceModeChangedNotificationEnabled(true);
        nn::oe::SetResumeNotificationEnabled(true);
        nn::oe::EnterExitRequestHandlingSection();
    }
    virtual ~DevPerfNx();  // slot 0
    virtual void update();  // slot 2
    virtual DevPerfOperationMode getOperationMode() const;  // slot 3
    virtual DevPerfMode getPerformanceMode() const;  // slot 4
    virtual int getFocusState() const;  // slot 5
    virtual void setPerfConfig(DevPerfMode mode, DevPerfConfig config);  // slot 6
    virtual DevPerfConfig getPerfConfig(DevPerfMode mode) const;  // slot 7
    virtual void changeOperationMode(DevPerfOperationMode mode);  // slot 8
    virtual void changePerformanceMode(DevPerfMode mode);  // slot 9
    virtual void resumeApplication();  // slot 10

    // the member names are not the original's
    DevPerfConfig m_perfConfig[3];        // 0x10 setPerfConfig stores the config by mode
    DevPerfOperationMode m_operationMode;  // 0x1C changeOperationMode
    DevPerfMode m_performanceMode;        // 0x20 changePerformanceMode
    int m_focusState;                     // 0x24 update: the SDK's focus state, 0 when out of range
};
}  // namespace ml

#endif
