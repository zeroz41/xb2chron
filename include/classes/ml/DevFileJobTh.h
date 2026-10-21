#ifndef CLASSES_ML_DEVFILEJOBTH_H
#define CLASSES_ML_DEVFILEJOBTH_H

namespace ml {
// table 0x7100B776E0
class DevFileJobTh {
public:
    virtual ~DevFileJobTh();  // slot 0
    virtual bool asyncUpdate() { return true; }  // slot 2
    virtual void getJobType() const;  // slot 3
    virtual void getReader();  // slot 4
};
}  // namespace ml

#endif
