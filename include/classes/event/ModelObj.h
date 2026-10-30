#ifndef CLASSES_EVENT_MODELOBJ_H
#define CLASSES_EVENT_MODELOBJ_H

namespace event { namespace IResEvent { class PARAM; }}
#include "mm/mtl/FixStr.h"

namespace gf { class GfEvtModel; class GF_OBJ_HANDLE; }

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
            unsigned int size;
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

    void setupModel(const DESC& desc);
    void setupModel(MODEL_TYPE type, unsigned int id, const OPTION& option);

    // bit 0: the init parameters get creation type 3 instead of 2 (what it means is not known yet)
    unsigned int pad_8;
    unsigned char pad_c[0x5C - 0xC];
    // the constructor's last argument; setupModel passes it as the init parameter's pad_24
    unsigned int pad_5c;
    unsigned char pad_60[0x120 - 0x60];
    // the model's object: setupModel copies m_model's handle (-1 from the constructor; the name is not the
    // original's)
    gf::GF_OBJ_HANDLE* m_handle;
    // the game model; ModelManager::update counts m_busyWait down and resets it to 2 while it is busy; the name is not the original's
    gf::GfEvtModel* m_model;  // 0x128
    int m_busyWait;  // 0x130
};
}  // namespace event

#endif
