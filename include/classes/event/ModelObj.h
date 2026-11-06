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
class ModelObj {
public:
    virtual void OnResEvent(event::IResEvent::PARAM const&);  // slot 0
    virtual ~ModelObj();  // slot 1

    // what setupModel(const DESC&) makes the model from: two files already in memory, the second one optional
    // (setRefResource indices 0 and 1; the names are not the original's)
    struct DESC {
        struct FILE {
            mm::mtl::FixStr<64> name;
            void* data;
            unsigned long size;
        };
        FILE files[2];
    };

    // setupModel's choices (the names are not the original's)
    struct OPTION {
        // a driver's blade (0: the debug manager's for the driver) or a weapon's driver
        unsigned int bladeId;
        // a weapon for the left hand (setupBladeForEventLeftCS, pad_1e1) rather than the right
        bool left;
        // GfInitParamBlade::setupForEvent's bool argument
        bool bladeFlag;
    };

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
        if (strcmp(m_desc.files[0].name.m_str, desc.files[0].name.m_str) != 0) {
            return false;
        }
        if (m_desc.files[0].data != desc.files[0].data || m_desc.files[0].size != desc.files[0].size) {
            return false;
        }
        if (strcmp(m_desc.files[1].name.m_str, desc.files[1].name.m_str) != 0) {
            return false;
        }
        if (m_desc.files[1].data != desc.files[1].data || m_desc.files[1].size != desc.files[1].size) {
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
