#ifndef CLASSES_ML_DEVPERFNX_H
#define CLASSES_ML_DEVPERFNX_H

namespace ml { class DevPerfConfig; }
namespace ml { class DevPerfMode; }
namespace ml { class DevPerfOperationMode; }

namespace ml {
// a base of ml::DevPerfNx no evidence names yet
class TUnk_B76808 {
public:
    virtual ~TUnk_B76808();
    virtual void update() = 0;
    virtual void getOperationMode() const = 0;
    virtual void getPerformanceMode() const = 0;
    virtual void getFocusState() const = 0;
    virtual void setPerfConfig(ml::DevPerfMode, ml::DevPerfConfig) = 0;
    virtual void getPerfConfig(ml::DevPerfMode) const = 0;
    virtual void changeOperationMode(ml::DevPerfOperationMode) = 0;
    virtual void changePerformanceMode(ml::DevPerfMode) = 0;
    virtual void resumeApplication() = 0;
};
// a base of ml::DevPerfNx no evidence names yet
class TUnk_B76870 {
public:
    virtual ~TUnk_B76870();
    virtual void changeOperationMode(ml::DevPerfOperationMode) = 0;
    virtual void changePerformanceMode(ml::DevPerfMode) = 0;
    virtual void resumeApplication() = 0;
};
// table 0x7100B76808; base at 0x0 unknown (TUnk_B76808), base at 0x8 unknown (TUnk_B76870)
class DevPerfNx : public TUnk_B76808, public TUnk_B76870 {
public:
    virtual ~DevPerfNx();  // slot 0
    virtual void update();  // slot 2
    virtual void getOperationMode() const;  // slot 3
    virtual void getPerformanceMode() const;  // slot 4
    virtual void getFocusState() const;  // slot 5
    virtual void setPerfConfig(ml::DevPerfMode, ml::DevPerfConfig);  // slot 6
    virtual void getPerfConfig(ml::DevPerfMode) const;  // slot 7
    virtual void changeOperationMode(ml::DevPerfOperationMode);  // slot 8
    virtual void changePerformanceMode(ml::DevPerfMode);  // slot 9
    virtual void resumeApplication();  // slot 10
};
}  // namespace ml

#endif
