#ifndef CLASSES_EVENT_MODELOBJ_H
#define CLASSES_EVENT_MODELOBJ_H

#include "classes/event/IResEvent.h"
#include "mm/mtl/FixStr.h"
#include <string.h>

namespace gf { class GfEvtModel; class GF_OBJ_HANDLE; }
namespace ml { class DrStmReadCheck; }

namespace event {
// which model setupModel makes: 1 a driver, 2 a blade, 3 an NPC, 4 an enemy, 5 a weapon (the GfGameEvent creator
// each case calls); no evidence names the enumerators yet
enum MODEL_TYPE {};

// table 0x7100B3C1B0
// an IResEvent: the constructor passes this to ResManager::load (an IResEvent* parameter), and slot 0 is
// OnResEvent(IResEvent::PARAM const&), as in MdlstmObj's table
class ModelObj : public IResEvent {
public:
    virtual void OnResEvent(event::IResEvent::PARAM const&);  // slot 0
    virtual ~ModelObj();  // slot 1

    // what setupModel(const DESC&) makes the model from: two files already in memory, the second one optional
    // (setRefResource indices 0 and 1; the names are not the original's)
    struct DESC {
        struct FILE {
            // the constructors store null and 0 in data and size one by one (no memset of the struct)
            FILE() : data(nullptr), size(0) {}
            mm::mtl::FixStr<64> name;
            void* data;
            unsigned long size;
        };
        // two members, not an array: the constructors build the second FILE straight after the first (an array's
        // construction loop orders the second one's stores differently). The mdo file is setRefResource index 0,
        // the arc file (optional) index 1, as OnResEvent fills them; the names are not the original's
        FILE mdo;  // 0x0
        FILE arc;  // 0x58
    };

    // setupModel's choices (the names are not the original's)
    struct OPTION {
        // zeroes the three fields only: MdlstmManager's constructor clears an MdlstmObj's OPTION with a word and a
        // halfword store, not the padding after it
        OPTION() : bladeId(0), left(false), bladeFlag(false) {}
        // a driver's blade (0: the debug manager's for the driver) or a weapon's driver
        unsigned int bladeId;
        // a weapon for the left hand (setupBladeForEventLeftCS, pad_1e1) rather than the right
        bool left;
        // GfInitParamBlade::setupForEvent's bool argument
        bool bladeFlag;
    };

    // 1.0.0's ModelObj::ModelObj() (0x710009B13C, kind 3 with bit 1 of pad_8); 3.0.1 inlines it into
    // ModelManager::createModel(int)
    ModelObj()
        : m_kind(3), m_type(), m_id(0), pad_5c(0), m_stmReader(nullptr),
          m_handle(reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)), m_model(nullptr), m_busyWait(-1), m_reserve(0) {
        pad_8 = 2;
    }
    ModelObj(const char* name, bool flag, unsigned int arg);
    ModelObj(const char* name, const DESC& desc, bool flag, unsigned int arg);
    // 1.0.0's ModelObj::setReserve, isReserve and isSame overloads (0x710009C838-0x710009CA70); 3.0.1 inlines them
    // into ModelManager's createModel, searchModel and destroyModel. isReserve(-1) tests every user but bit 31
    void setReserve(unsigned int index, bool on) {
        if (on) {
            m_reserve |= 1 << index;
        } else {
            m_reserve &= ~(1 << index);
        }
    }
    // 1.0.0's ModelObj::isBusy (0x710009C7E4; inlined in 3.0.1, defined inline in CharaObj.cpp)
    bool isBusy() const;
    bool isReserve(int index) {
        return m_reserve & (index >= 0 ? 1 << index : 0x7fffffff);
    }
    bool isSame(const char* name, bool flag, unsigned int arg) {
        if (m_kind != 0) {
            return false;
        }
        if (strcmp(m_name.m_str, name) != 0) {
            return false;
        }
        if ((pad_8 & 1) != flag) {
            return false;
        }
        return pad_5c == arg;
    }
    bool isSame(const char* name, const DESC& desc, bool flag, unsigned int arg) {
        if (m_kind != 1) {
            return false;
        }
        if (strcmp(m_name.m_str, name) != 0) {
            return false;
        }
        if (strcmp(m_desc.mdo.name.m_str, desc.mdo.name.m_str) != 0) {
            return false;
        }
        if (m_desc.mdo.data != desc.mdo.data || m_desc.mdo.size != desc.mdo.size) {
            return false;
        }
        if (strcmp(m_desc.arc.name.m_str, desc.arc.name.m_str) != 0) {
            return false;
        }
        if (m_desc.arc.data != desc.arc.data || m_desc.arc.size != desc.arc.size) {
            return false;
        }
        if ((pad_8 & 1) != flag) {
            return false;
        }
        return pad_5c == arg;
    }
    bool isSame(MODEL_TYPE type, unsigned int id, const OPTION& option, bool flag, unsigned int arg) {
        if (m_kind != 2) {
            return false;
        }
        if (m_type != type || m_id != id) {
            return false;
        }
        if (m_option.bladeId != option.bladeId || m_option.left != option.left ||
            m_option.bladeFlag != option.bladeFlag) {
            return false;
        }
        if ((pad_8 & 1) != flag) {
            return false;
        }
        return pad_5c == arg;
    }
    // m_kind 3 with bit 1 of pad_8 (what createModel(int) makes)
    bool isSame() {
        return m_kind == 3 && (pad_8 & 2);
    }

    void setupModel(const DESC& desc);
    void setupModel(MODEL_TYPE type, unsigned int id, const OPTION& option);

    // bit 0: the init parameters get creation type 3 instead of 2 (what it means is not known yet)
    unsigned int pad_8;
    // what the model is made from, as ModelManager's searchModel overloads compare it: 0 a name, 1 a DESC, 2 a
    // MODEL_TYPE with an id and OPTION, 3 createModel(int)'s ghost (the name is not the original's)
    int m_kind;  // 0xc
    // m_kind 2's type and id (the names are not the original's)
    MODEL_TYPE m_type;  // 0x10
    unsigned int m_id;  // 0x14
    // the constructor's name (the name is not the original's)
    mm::mtl::FixStr<64> m_name;  // 0x18
    // the constructor's last argument; setupModel passes it as the init parameter's pad_24
    unsigned int pad_5c;
    // m_kind 1's files (the name is not the original's)
    DESC m_desc;  // 0x60
    // m_kind 2's choices (the name is not the original's)
    OPTION m_option;  // 0x110
    // the stream reader setupModel makes (ml::ScnObjAccStmReadObj::create); the destructor releases it; the name is
    // not the original's
    ml::DrStmReadCheck* m_stmReader;  // 0x118
    // the model's object: setupModel copies m_model's handle (-1 from the constructor; the name is not the
    // original's)
    gf::GF_OBJ_HANDLE* m_handle;
    // the game model; ModelManager::update counts m_busyWait down and resets it to 2 while it is busy; the name is not the original's
    gf::GfEvtModel* m_model;  // 0x128
    int m_busyWait;  // 0x130
    // bit n: user n holds the model (setReserve, isReserve; ModelManager::createModel sets 1 << its last argument,
    // searchModel skips models the user holds; the name is not the original's)
    unsigned int m_reserve;  // 0x134
};
}  // namespace event

#endif
