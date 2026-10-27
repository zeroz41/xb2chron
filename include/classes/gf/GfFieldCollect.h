#ifndef CLASSES_GF_GFFIELDCOLLECT_H
#define CLASSES_GF_GFFIELDCOLLECT_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "gf/GfDropitemEmitter.h"
#include "mm/mtl/FixedVector.h"

namespace gf { class GfFieldCollect; }
namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class GfSetupParam; class MapjumpCallbackInfo; class GF_OBJ_HANDLE; enum GEV : int; enum RELOAD_BDAT : int; }
namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B51488; gathering at a field collection point: a sequence of steps (m_seq), each run with the frame's
// time, then the point's items dropped by up to four emitters
class GfFieldCollect : public ::mm::mtl::PtrSingleton< ::gf::GfFieldCollect> {
public:
    GfFieldCollect(const GfSetupParam& param)  // 1.0.0's (3.0.1's build inlines it)
        : m_isUIEnd(false), m_handle(reinterpret_cast<GF_OBJ_HANDLE*>(-1)), m_seqTime(0.0f), m_doStartTime(0.0f),
          m_fsId(0), m_isPreciousOnly(false) {
        create(param);
    }
    virtual ~GfFieldCollect();  // slot 0
    // 1.0.0's
    void create(const GfSetupParam&) {
        m_seq = &GfFieldCollect::seqEnd;
        m_isCreate = true;
    }
    // 1.0.0's: whether every emitter has dropped its items
    bool isDropitemsEmitted() const {
        unsigned int count = m_emitters.size();
        for (unsigned int i = 0; i < count; ++i) {
            if (!m_emitters[i].m_isEmitted) {
                return false;
            }
        }
        return true;
    }
    // 1.0.0's: back to no point
    void end() {
        m_emitters.clear();
        m_handle = reinterpret_cast<GF_OBJ_HANDLE*>(-1);
        m_seq = &GfFieldCollect::seqEnd;
    }
    // 1.0.0's
    void dispose() {
        end();
        if (m_isCreate) {
            m_isCreate = false;
        }
    }
    // 1.0.0's
    void update(float dt) {
        unsigned long count = get()->m_emitters.size();
        for (unsigned long i = 0; i < count; ++i) {
            get()->m_emitters[i].update(dt);
        }
        if (m_seq) {
            (this->*m_seq)(dt);
        }
    }
    // GfFieldManager's forwards (its initialize, finalize, update and gevMapjump call them)
    static void build(const GfSetupParam& param);
    static void destroy();
    static void update(const fw::UpdateInfo& info);
    void gevMapjump(GEV gev, const MapjumpCallbackInfo& info);
    void start(GF_OBJ_HANDLE* handle);  // GfPlayComCollect::start calls it
    void createDropitemEmitter(const GfDropitemEmitter::CreateInfo& info);
    void seqEnd(float dt);
    void seqWaitDo(float dt);
    void seqWaitUIEnd(float dt);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because seqWaitUIEnd stores it
    // as the next step (m_seq) when m_isPreciousOnly is set. What it does: adds dt to m_seqTime and moves on to
    // seqDo once a second has passed.
    void fn_71002681C4(float dt);
    void seqDo(float dt);
    void seqWaitDrop(float dt);

    void (GfFieldCollect::*m_seq)(float dt);  // the step update runs
    bool m_isCreate;  // create sets it, dispose clears it (the name is not the original's)
    bool m_isUIEnd;  // seqWaitUIEnd sets it once the field skill menu is gone (the name is not the original's)
    GF_OBJ_HANDLE* m_handle;  // the collection point's object
    mm::mtl::FixedVector<GfDropitemEmitter, 4> m_emitters;  // seqDo's drops (the name is not the original's)
    float m_seqTime;  // the step's time so far (the name is not the original's)
    // how long seqWaitDo waits before the field skill check (a bdat float; the name is not the original's)
    float m_doStartTime;
    unsigned short m_fsId;  // the point's field skill (FSID; the name is not the original's)
    unsigned char pad_1ca[0x6];
    // the blades whose field skill rolls succeeded, each gathering once more (the name is not the original's)
    mm::mtl::FixedVector<unsigned int, 3> m_blades;
    // every item of the point's CollectionTable row is precious or none (3.0.1's; seqWaitUIEnd then waits a second;
    // the name is not the original's)
    bool m_isPreciousOnly;
};
}  // namespace gf

#endif
