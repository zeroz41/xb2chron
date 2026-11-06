#ifndef CLASSES_EVENT_MDLSTMOBJ_H
#define CLASSES_EVENT_MDLSTMOBJ_H

#include "classes/event/IResEvent.h"
#include "classes/event/ModelObj.h"
#include "classes/event/ModelUtil.h"
#include "mm/mtl/FixStr.h"
#include "mm/mtl/Bitflag.h"
#include "classes/ml/DrStmReadCheck.h"

namespace event {
// table 0x7100B3C4E8
// slot 0 OnResEvent comes from IResEvent; the destructor (out of line, D2/D0 mid-text before finishFree) is the key
// function. Size 0xF0: MdlstmManager destroys an array of them at stride 0xF0.
// Field names are not the original's; they follow 1.0.0's member functions (init, isLoading(float), isBuildable,
// isDisposeable, finishLoaded/Delay/Busy store the state numbers).
class MdlstmObj : public IResEvent {
public:
    // inline: MdlstmManager's constructor (Singleton<MdlstmManager>::getPtr) zeroes these ranges of each object
    // (0x8-0x14, 0x94-0xA5, 0xA8, 0xB0-0xE7)
    MdlstmObj()
        : m_flags(), m_state(0), m_frame(0), m_name(), m_type(), pad_9c(0), m_option(),
          m_id(0), pad_b0(0), pad_b8(0), pad_c0(0), pad_c8(0), m_reader(nullptr), m_model(nullptr), m_buildModel(nullptr) {}
    virtual ~MdlstmObj();  // slot 1
    virtual void OnResEvent(event::IResEvent::PARAM const&);  // slot 0

    void finishFree();
    void exec(float, float);
    void finishLoad();
    // 1.0.0's MdlstmObj::finishLoaded (inlined in 3.0.1)
    void finishLoaded() { m_state = 4; }
    void finishModel();
    // 1.0.0's MdlstmObj::finishDelay (inlined in 3.0.1)
    void finishDelay() { m_state = 6; }
    // 1.0.0's MdlstmObj::finishBusy (inlined in 3.0.1)
    void finishBusy() {
        ModelUtil::setupRenderState(m_buildModel->m_handle);
        m_state = 7;
    }
    void init(float frame, const char* name, unsigned int id, bool flag, int user);
    // 1.0.0's init(float, MODEL_TYPE, unsigned int, unsigned int, bool, int) (inlined in 3.0.1)
    void init(float frame, MODEL_TYPE type, unsigned int no, unsigned int id, bool flag, int user) {
        m_flags.reset(0);
        m_frame = frame;
        m_name.clear();
        m_option.bladeFlag = flag;
        m_type = type;
        pad_9c = no;
        m_option.bladeId = 0;
        m_option.left = false;
        m_id = id;
        pad_b0 = 0;
        pad_c0 = 0;
        m_buildModel = nullptr;
        pad_e8 = 0;
        m_user = user;
        m_state = 1;
    }
    ModelObj* build();
    // 1.0.0's MdlstmObj::dispose (inlined in 3.0.1)
    void dispose() {
        m_state = 9;
        pad_e8 = 1;
    }
    // 1.0.0's MdlstmObj::isBuildable(char const*, unsigned int) (inlined in 3.0.1)
    bool isBuildable(const char* name, unsigned int id) const {
        if (m_state != 7) {
            return false;
        }
        if (!m_flags.test(0)) {
            return false;
        }
        if (m_id != id) {
            return false;
        }
        return strcmp(m_name.m_str, name) == 0;
    }

    // bit 0: init by name; finishLoad sets bits 1/2 as it loads the mdo/arc, OnResEvent turns them into bit 3/4
    // (a Bitflag: exec reads it alone where a plain int let the state's load widen into one 8-byte load)
    mm::mtl::Bitflag<32> m_flags;  // 0x8
    // 1 init, 2 load, 3 loaded, 4 model, 5 delay, 6 busy, 7 buildable, 8 built, 9 dispose (1.0.0's finish* store them)
    int m_state;  // 0xc
    // the cut frame it loads at (1.0.0's isLoading(float) compares it)
    float m_frame;  // 0x10
    mm::mtl::FixStr<128> m_name;  // 0x14, length @0x94
    MODEL_TYPE m_type;  // 0x98: a model by type (1.0.0's init(MODEL_TYPE, ...)) when not 0
    unsigned int pad_9c;
    // finishLoad's createModel(MODEL_TYPE, ...) takes it; init copies a replace info's fields into it
    ModelObj::OPTION m_option;  // 0xa0
    unsigned int m_id;  // 0xa8: isBuildable compares it
    unsigned long pad_b0;
    unsigned long pad_b8;
    unsigned long pad_c0;
    unsigned long pad_c8;
    // finishLoad's stream reader (ml::ScnObjAccStmReadObj::create); finishFree releases it (slot 2)
    ml::DrStmReadCheck* m_reader;  // 0xd0
    // 1.0.0's checkByHandle compares both models' handles; isDisposeable compares m_buildModel
    ModelObj* m_model;  // 0xd8
    ModelObj* m_buildModel;  // 0xe0: build() returns it
    int pad_e8;  // exec counts it down in states 5 and 9; MdlstmManager::clear sets 1
    int m_user;  // 0xec: ModelManager::destroyModel's user
};
}  // namespace event

#endif
