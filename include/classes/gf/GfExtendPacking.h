#ifndef CLASSES_GF_GFEXTENDPACKING_H
#define CLASSES_GF_GFEXTENDPACKING_H

#include "classes/gf/GfExtendResource.h"
#include "mm/mtl/FixedQueue.h"
#include "mm/mtl/RTTI.h"
namespace anm { class ResASM; }
namespace fw { class EffectResData; }
namespace fw { struct ResSoundTrigger; }

namespace gf {
// table 0x7100B69EE0; a pack's state machine resource, its effect data and the sound triggers
// addExtendPackingSoundTrigger queues for it (1.0.0's gf::addExtendPackingSoundTrigger(gf::GF_ASSET_HANDLE*,
// gf::GfFileIdx, gf::GfExtendPacking*)); 0x70 bytes (the object factory allocates them)
class GfExtendPacking : public GfExtendResource {
public:
    GfExtendPacking();
    virtual ~GfExtendPacking();  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    static mm::mtl::RTTI m_rtti;

    void registerSoundTrigger();

    // the fields' names are not the original's
    anm::ResASM* m_pResASM;  // anm::Factory::createASMResource fills it; GfComEffectCaster registers its effects
    fw::EffectResData* m_pEffectResData;  // GfComEffectCaster::registerAsmCallbackEffect's effect data
    mm::mtl::FixedQueue<const fw::ResSoundTrigger*, 8> m_soundTriggers;  // fixed_queue.h's `!full()` as one is added
};
}  // namespace gf

#endif
