#ifndef CLASSES_FW_ANIMVOLUMEFADEMODIFIER_H
#define CLASSES_FW_ANIMVOLUMEFADEMODIFIER_H

#include "classes/fw/AnimAfterModifierInterface.h"
#include "mm/mtl/IntrusivePtr.h"
#include "mm/mtl/Delegate.h"

namespace fw {
class ModelObject;
// table 0x7100B40B48
// AnimationManager::addAfterModifier keeps it (GfComModel::setup passes its own, no adjustment)
class AnimVolumeFadeModifier : public AnimAfterModifierInterface {
public:
    AnimVolumeFadeModifier();
    virtual ~AnimVolumeFadeModifier();  // slot 0
    virtual void apply();  // slot 2
    // keeps a reference to model and finds its "VolumeFade_<part>" etc parameters (GfComModel::setup)
    void bind(ModelObject* model);
    // undoes bind: releases m_model (GfComModel::cleanup)
    void unbind();
    // bind's; unbind releases it. A plain pointer: the destructor is empty (the name is not the original's)
    ModelObject* m_model;
    // each gf::VFPARTS's opacity: GfVolumeFade::applyFadeRatio stores 1 - the part's fade ratio (the name is not
    // the original's)
    float m_partsAlpha[6];
    // per part, the model's "VolumeFade_<part>" etc parameter (bind finds them, -1 if none; apply sets each to
    // its part's opacity; the name is not the original's)
    int m_paramIndices[6];
    // apply does nothing while it is set and returns false (GfComModel::setup sets it to its own member;
    // GfComModel::cleanup clears its invoker before unbind; the name is not the original's)
    mm::mtl::Delegate<bool()> m_condition;
    // set when bind finds no "VolumeFade_" parameter: apply sets the model's volume fade ratios instead (the
    // constructor sets it; the name is not the original's)
    bool m_useVolumeFadeAcc;
    unsigned char pad_71[0x7];  // 0x78 bytes: GfComModel holds one at 0x10c8, its vectors follow at 0x1140
};
}  // namespace fw

#endif
