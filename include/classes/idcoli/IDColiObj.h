#ifndef CLASSES_IDCOLI_IDCOLIOBJ_H
#define CLASSES_IDCOLI_IDCOLIOBJ_H

namespace idcoli {
// table 0x7100B7F088
class IDColiObj {
public:
    virtual ~IDColiObj();  // slot 0
    virtual void release();  // slot 2
    virtual void sizeUpdate();  // slot 3
    virtual void update();  // slot 4
    virtual void SweepAndPruneUpdate();  // slot 5
    virtual void consistentUpdate();  // slot 6
};
}  // namespace idcoli

#endif
