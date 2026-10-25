#ifndef CLASSES_PTLIB_EMITTER_COMPUTEMANAGER_H
#define CLASSES_PTLIB_EMITTER_COMPUTEMANAGER_H

namespace ptlib { namespace emitter {
// table 0x7100B80790
class ComputeManager {
public:
    virtual ~ComputeManager();  // slot 0
    static ComputeManager*& getPtr();
    void update(unsigned int view);
    void resetUpdate();
};
}}  // namespace ptlib::emitter

#endif
