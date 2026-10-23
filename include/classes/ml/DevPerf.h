#ifndef CLASSES_ML_DEVPERF_H
#define CLASSES_ML_DEVPERF_H

#include "classes/ml/WorkObj.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace ml {

// passed in a register by value: enums (DevPerfNx::setPerfConfig maps 1 and 2 to the SDK's normal and boost modes)
enum DevPerfMode {};
enum DevPerfConfig {};
enum DevPerfOperationMode {};

// the platform's performance interface ml::DevPerf holds at 0x1B0 and ml::DevPerfNx implements; no evidence names it yet
class TUnk_B76808 {
public:
    virtual ~TUnk_B76808() {}
    virtual void update() = 0;
    virtual DevPerfOperationMode getOperationMode() const = 0;
    virtual DevPerfMode getPerformanceMode() const = 0;
    virtual int getFocusState() const = 0;
    virtual void setPerfConfig(DevPerfMode mode, DevPerfConfig config) = 0;
    virtual DevPerfConfig getPerfConfig(DevPerfMode mode) const = 0;
    virtual void changeOperationMode(DevPerfOperationMode mode) = 0;
    virtual void changePerformanceMode(DevPerfMode mode) = 0;
    virtual void resumeApplication() = 0;
};

// table 0x7100B760F8; its singleton at 0x1A8 (the destructor stores PtrSingleton<ml::DevPerf>'s table there)
class DevPerf : public ::ml::WorkObj, public ::mm::mtl::PtrSingleton<DevPerf> {
public:
    virtual ~DevPerf();  // slot 0
    virtual void wkUpdate();  // slot 9
    virtual bool wkStandbyLogin();  // slot 14
    virtual bool wkStandbyLogout();  // slot 15
    // through the singleton's platform object; normal operation mode (1) while there is none
    static DevPerfOperationMode getOperationMode();
    static void setPerfConfig(DevPerfMode mode, DevPerfConfig config);

    TUnk_B76808* m_impl;  // 0x1B0 the platform object: the destructor deletes it (the name is not the original's)
};
}  // namespace ml

#endif
