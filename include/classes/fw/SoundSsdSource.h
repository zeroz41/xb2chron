#ifndef CLASSES_FW_SOUNDSSDSOURCE_H
#define CLASSES_FW_SOUNDSSDSOURCE_H

#include "classes/fw/SoundReferenceObject.h"
#include "mm/mtl/FixStr.h"

namespace fw {
// table 0x7100B42EA0
class SoundSsdSource : public ::fw::SoundReferenceObject {
public:
    virtual ~SoundSsdSource();  // slot 0

    unsigned char pad_c[0x128];
    // the name SoundPack::findSource looks sources up by: the wave constructor copies its setup's second name here
    // (the field's name is not the original's)
    mm::mtl::FixStr<256> m_label;
};
}  // namespace fw

#endif
