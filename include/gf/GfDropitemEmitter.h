#ifndef GF_GFDROPITEMEMITTER_H
#define GF_GFDROPITEMEMITTER_H

#include "mm/Vec3.h"

namespace gf {
// drops a treasure's items (GfFieldTbox and GfFieldCollect hold one; GfFobjDropitem's unit defines it)
class GfDropitemEmitter {
public:
    // what to drop and where (the names are not the original's)
    struct CreateInfo {
        mm::Vec3 m_pos;  // where the items drop from (the constructor's Vec3::zero copy)
        unsigned char pad_0x10[0xc];
        float m_dropDelay;  // seqWaitBeginDrop drops once m_timer reaches it
        unsigned char pad_0x20[0x10];
        // the items' rows (GfFobjDropitem::EmitInfo::createDropitemInfos takes them with m_itemCount); update runs
        // only with both
        unsigned char* m_items;
        int m_itemCount;
    };

    GfDropitemEmitter(const CreateInfo* info);
    ~GfDropitemEmitter() { dispose(); }
    void create(const CreateInfo& info);
    void dispose();
    void update(float dt);
    void seqWaitBeginDrop(float dt);
    void seqWaitEndDrop(float dt);

    CreateInfo m_info;  // create's copy (the name is not the original's)
    // whether the items have been dropped (GfFieldTbox::isDropitemsEmitted reads it; the name is not the original's)
    bool m_isEmitted;
    float m_timer;  // update adds each frame's time step (the name is not the original's)
    // seqWaitBeginDrop sets it to m_timer plus the time GfFobjDropitem::emitDropitems returns; seqWaitEndDrop ends
    // the sequence there (the name is not the original's)
    float m_endTime;
    // the step update runs (seqWaitBeginDrop, then seqWaitEndDrop, by its symbols; the name is not the original's)
    void (GfDropitemEmitter::*m_seq)(float dt);
};
}  // namespace gf

#endif
