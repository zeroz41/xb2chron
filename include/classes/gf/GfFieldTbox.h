#ifndef CLASSES_GF_GFFIELDTBOX_H
#define CLASSES_GF_GFFIELDTBOX_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "gf/GfDropitemEmitter.h"

namespace fw { class UpdateInfo; }
namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class GfFieldTbox; }
namespace gf { class GfSetupParam; }
namespace gf { class MapjumpCallbackInfo; }
namespace gf { enum GEV : int; }

namespace gf {
// table 0x7100B525F8; opening a field treasure box: a sequence of steps (m_seq), each run with the frame's time
class GfFieldTbox : public ::mm::mtl::PtrSingleton< ::gf::GfFieldTbox> {
public:
    GfFieldTbox(const GfSetupParam& param)  // 1.0.0's (3.0.1's build inlines it)
        : m_fsStartTime(0.0f), m_openStartTime(0.0f), m_isCreate(false), m_isUIEnd(false), m_isFsOK(false),
          m_handle(reinterpret_cast<GF_OBJ_HANDLE*>(-1)), m_rscId(-1), m_isExcavation(false), m_seq(nullptr),
          m_seqTime(0.0f), m_emitter(nullptr) {
        create(param);
    }
    virtual ~GfFieldTbox();  // slot 0
    void create(const GfSetupParam&) { m_isCreate = true; }  // 1.0.0's
    bool isDropitemsEmitted() const;
    void gevMapjump(GEV gev, const MapjumpCallbackInfo& info);
    // 1.0.0's: back to no box
    void end() {
        m_seqTime = 0.0f;
        m_emitter.dispose();
        m_isExcavation = false;
        m_rscId = -1;
        m_seq = nullptr;
        m_handle = reinterpret_cast<GF_OBJ_HANDLE*>(-1);
    }
    void start(GF_OBJ_HANDLE* handle);
    void seqWaitCheckFs(float dt);
    // 1.0.0's
    void dispose() {
        end();
        if (m_isCreate) {
            m_isCreate = false;
        }
    }
    // 1.0.0's
    void update(float dt) {
        if (m_seq) {
            (this->*m_seq)(dt);
        }
        m_emitter.update(dt);
    }
    static void build(const GfSetupParam& param);
    static void destroy();
    static void update(const fw::UpdateInfo& info);
    void seqCheckFs(float dt);
    void seqWaitUIEnd(float dt);
    void seqWaitOpenFieldTbox(float dt);
    void seqWaitDigEnd(float dt);
    void seqWaitDropBegin(float dt);

    float m_fsStartTime;  // FS_starttime: how long before the field skill check
    float m_openStartTime;  // TBOX_open_starttime: how long before the box opens
    bool m_isCreate;  // create sets it, dispose clears it (the name is not the original's)
    bool m_isUIEnd;  // seqWaitUIEnd sets it once the field skill menu is gone (the name is not the original's)
    // seqCheckFs's: whether the party's field skills pass the box's check (the name is not the original's)
    bool m_isFsOK;
    GF_OBJ_HANDLE* m_handle;  // the box's object
    int m_rscId;  // the box's RSC_ID
    // the box is dug up: its FSID2 and its C_excavation animation (the name is not the original's)
    bool m_isExcavation;
    void (GfFieldTbox::*m_seq)(float dt);  // the step update runs, none when done
    float m_seqTime;  // the step's time so far
    GfDropitemEmitter m_emitter;
};
}  // namespace gf

#endif
