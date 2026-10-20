// not proven yet: its table differs from the original's (word 18: _ZN2fw13EffectManager8finalizeEv where the original has =-8)
#ifndef CLASSES_FW_EFFECTMANAGER_H
#define CLASSES_FW_EFFECTMANAGER_H

#include "classes/fw/ManagerObject.h"
#include "classes/ml/IScnRender.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace fw { class EffectManager; }
namespace fw { class UpdateInfo; }
namespace ml { class IDrDrawWorkInfo; }

namespace fw {
// a base of fw::EffectManager no evidence names yet
class TUnk_B41508 {
public:
    virtual ~TUnk_B41508();
    virtual void begin() = 0;
    virtual void end() = 0;
    virtual void apply(ml::IDrDrawWorkInfo const*) = 0;
    virtual void opacityRender(ml::IDrDrawWorkInfo const*) = 0;
    virtual void alphaRender(ml::IDrDrawWorkInfo const*) = 0;
    virtual void lastRender(ml::IDrDrawWorkInfo const*) = 0;
    virtual void blurRender(ml::IDrDrawWorkInfo const*) = 0;
    virtual void finalRender(ml::IDrDrawWorkInfo const*) = 0;
};
// table 0x7100B41428; base at 0x18 unknown (TUnk_B41508)
class EffectManager : public ::mm::mtl::PtrSingleton< ::fw::EffectManager>, public ::fw::ManagerObject, public TUnk_B41508, public ::ml::IScnRender {
public:
    virtual ~EffectManager();  // slot 0
    virtual void initialize();  // slot 2
    virtual void vf3();  // slot 3
    virtual void update(fw::UpdateInfo const&);  // slot 4
    virtual void updateLayer(fw::UpdateInfo const&, unsigned int);  // slot 5
    virtual void updateLayerPost(fw::UpdateInfo const&, unsigned int);  // slot 6
    virtual void tail(fw::UpdateInfo const&, bool);  // slot 7
    virtual void begin();  // slot 8
    virtual void end();  // slot 9
    virtual void apply(ml::IDrDrawWorkInfo const*);  // slot 10
    virtual void opacityRender(ml::IDrDrawWorkInfo const*);  // slot 11
    virtual void alphaRender(ml::IDrDrawWorkInfo const*);  // slot 12
    virtual void lastRender(ml::IDrDrawWorkInfo const*);  // slot 13
    virtual void blurRender(ml::IDrDrawWorkInfo const*);  // slot 14
    virtual void finalRender(ml::IDrDrawWorkInfo const*);  // slot 15
    virtual void finalize();  // overrides a secondary base's
};
}  // namespace fw

#endif
