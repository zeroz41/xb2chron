#ifndef CLASSES_GMK_GMKFORM_H
#define CLASSES_GMK_GMKFORM_H

#include "mm/Vec3.h"

namespace gmk {
// no table; the class and member names come from the symbols (GmkForm::create, dispose, getPosRotY,
// validatePosRotY); the fields' names are not the original's
class GmkForm {
public:
    // one position and rotation; checks them (validatePosRotY); true
    bool create(const mm::Vec3& pos, float rotY);
    void dispose();
    // the position and rotation at index
    void getPosRotY(mm::Vec3& pos, float& rotY, unsigned int index) const;
    void validatePosRotY();

    int pad_0;  // 1 once created, 0 after dispose
    unsigned char pad_4[0xc];
    mm::Vec3 pad_10[6];  // 0x10: positions by index (create sets the first)
    float pad_70[6];  // 0x70: rotations by index (create sets the first; the count is not known, taken as 6)
};
}  // namespace gmk

#endif
