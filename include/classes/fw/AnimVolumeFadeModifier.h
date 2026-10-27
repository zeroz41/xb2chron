#ifndef CLASSES_FW_ANIMVOLUMEFADEMODIFIER_H
#define CLASSES_FW_ANIMVOLUMEFADEMODIFIER_H

#include "classes/fw/AnimAfterModifierInterface.h"
#include "mm/mtl/IntrusivePtr.h"

namespace fw {
class ModelObject;
// table 0x7100B40B48
// AnimationManager::addAfterModifier keeps it (GfComModel::setup passes its own, no adjustment)
class AnimVolumeFadeModifier : public AnimAfterModifierInterface {
public:
    AnimVolumeFadeModifier();
    virtual ~AnimVolumeFadeModifier();  // slot 0
    virtual void apply();  // slot 2
    // undoes bind: releases m_model (GfComModel::cleanup)
    void unbind();
    // bind's; unbind releases it. A plain pointer: the destructor is empty (the name is not the original's)
    ModelObject* m_model;
    // each gf::VFPARTS's opacity: GfVolumeFade::applyFadeRatio stores 1 - the part's fade ratio (the name is not
    // the original's)
    float m_partsAlpha[6];
    unsigned char pad_38[0x20];
    void* pad_58;  // GfComModel::cleanup clears it before unbind
    unsigned char pad_60[0x18];  // 0x78 bytes: GfComModel holds one at 0x10c8, its vectors follow at 0x1140
};
}  // namespace fw

#endif
