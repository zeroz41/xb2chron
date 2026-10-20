#ifndef CLASSES_ML_MICROTHREAD_H
#define CLASSES_ML_MICROTHREAD_H

namespace ml {
// table 0x7100B78478
class MicroThread {
public:
    class MTHREAD;
    virtual ~MicroThread();  // slot 0
    virtual void vf2() = 0;  // slot 2
    virtual void vf3() = 0;  // slot 3
    virtual void vf4() = 0;  // slot 4
    virtual void vf5() = 0;  // slot 5
};
}  // namespace ml

#endif
