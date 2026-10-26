#ifndef PTLIB_EMITTER_EMITTEROBJ_H
#define PTLIB_EMITTER_EMITTEROBJ_H

#include "ptlib/IntrusiveList.h"
#include "mm/Mat44.h"

namespace ptlib { class FxHeader; class DrDrawWorkInfoEF; }
namespace ptlib { namespace renderer { class StreamObj; class RenderSet; } }

namespace ptlib { namespace emitter {

// what an emitter is created or updated with. The field names are not the original's; the size is not known yet.
class EmitterParam {
public:
    mm::Mat44 m_mtx;  // EmitterManager::emitter_set_param_pos_only takes it whole, _pos_only2 its translation
    unsigned char pad_40[0x3C];
    // EmitterManager::emitter_set_param(handle, ...) runs the emitter ahead by so many frames, two at a time
    float m_preFrames;
};

// an emitter (particle_emitter.cpp); its links are EmitterManager's active list. The field names are not the
// original's unless a comment says so; the size is not known yet.
class EmitterObj : public IntrusiveListNode {
public:
    void emitter_set_param_sub(EmitterParam* pParam);
    // m_fadeCount out of m_fadeFrames, 1 without a fade
    float calc_fade();
    // EmitterManager's speed of the emitter's category
    float getCateSpd();
    void* lockStream(const DrDrawWorkInfoEF* pDrInfo);
    void unlockStream(const DrDrawWorkInfoEF* pDrInfo, unsigned int count);
    void renderStreamNum(renderer::RenderSet& set, const DrDrawWorkInfoEF* pDrInfo);

    unsigned char pad_10[0x48];
    FxHeader* m_pHeader;  // EmitterManager::emitter_set_param(FxHeader*, ...) picks the emitters of a header
    renderer::StreamObj* m_pStream;
    unsigned char pad_68[0x18];
    // what it points at is not known yet; while it is set, the emitter_set_param_pos_only* setters leave m_mtx alone
    void* m_pAttach;
    unsigned char pad_88[0x8];
    void* m_pGrp;  // ParticleManager::getGrp(m_viewNum) (the name is the original's: "em->m_pGrp")
    unsigned char pad_98[0x48];
    mm::Mat44 m_mtx;  // the emitter's placement: EmitterParam::m_mtx
    unsigned char pad_120[0xC];
    float m_alpha;  // emitter_set_alpha's
    unsigned char pad_130[0x21];
    unsigned char m_disp;    // emitter_set_disp's
    unsigned char m_nowait;  // emitter_set_nowait's
    unsigned char pad_153[0x5];
    float m_speed;  // emitter_set_speed's
    unsigned char pad_15c[0x14];
    unsigned int m_category;  // emitter_set_category's; indexes EmitterManager::m_categorySpeed
    unsigned char pad_174[0xD];
    unsigned char m_fadeCount;   // calc_fade's numerator
    unsigned char m_fadeFrames;  // calc_fade's denominator
    unsigned char pad_183[0xE1];
    unsigned int m_handle;  // the handle the emitter_set_* setters look for
    unsigned char pad_268[0xC];
    unsigned char m_viewNum;  // emitter_set_viewnum's
};

}}  // namespace ptlib::emitter

#endif
