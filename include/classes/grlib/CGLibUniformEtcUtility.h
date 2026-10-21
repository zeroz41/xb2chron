#ifndef CLASSES_GRLIB_CGLIBUNIFORMETCUTILITY_H
#define CLASSES_GRLIB_CGLIBUNIFORMETCUTILITY_H

namespace grlib {
// table 0x7100B79E30
class CGLibUniformEtcUtility {
public:
    virtual ~CGLibUniformEtcUtility() {}  // slot 0
    virtual void getBuff();  // slot 2
    virtual void updateData();  // slot 3
    virtual void setUniformBlock();  // slot 4
    virtual void setStorageBuffer();  // slot 5
    virtual void setMoveMem();  // slot 6
};
}  // namespace grlib

#endif
