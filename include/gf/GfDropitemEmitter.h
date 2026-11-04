#ifndef GF_GFDROPITEMEMITTER_H
#define GF_GFDROPITEMEMITTER_H

#include "mm/Vec3.h"

namespace gf {
// drops a treasure's items (GfFieldTbox and GfFieldCollect hold one; GfFobjDropitem's unit defines it)
class GfDropitemEmitter {
public:
    // what to drop and where (the names are not the original's)
    struct CreateInfo {
        // the constructor's defaults (the emitter's constructor, create and dispose store them)
        CreateInfo()
            : m_pos(mm::Vec3::zero), m_angle(0.0f), m_angleRange(3.14159265f), m_dropDistance(0.0f),
              m_dropDelay(0.0f), m_appearDelay(0.0f), m_appearDelayRange(0.0f), pad_0x28(0), pad_0x29(0),
              m_items(nullptr), m_itemCount(0) {}

        mm::Vec3 m_pos;  // where the items drop from (the constructor's Vec3::zero copy)
        // copied into GfFobjDropitem::EmitInfo, where emitDropitems spreads the drops over m_angle - m_angleRange
        // onwards (the names are not the original's)
        float m_angle;
        float m_angleRange;
        // seqWaitBeginDrop copies it into EmitInfo::m_dropDistance (the name is not the original's)
        float m_dropDistance;
        float m_dropDelay;  // seqWaitBeginDrop drops once m_timer reaches it
        // seqWaitBeginDrop copies them into EmitInfo::m_appearDelay/m_appearDelayRange (the names are not the
        // original's)
        float m_appearDelay;
        float m_appearDelayRange;
        // seqWaitBeginDrop builds the drops with createDropitemInfosBattleChallenge when set, else with EmitInfo::createDropitemInfos
        unsigned char pad_0x28;
        unsigned char pad_0x29;  // seqWaitBeginDrop copies it into EmitInfo::pad_0x56
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
