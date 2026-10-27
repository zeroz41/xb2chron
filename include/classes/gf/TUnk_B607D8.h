#ifndef CLASSES_GF_TUNK_B607D8_H
#define CLASSES_GF_TUNK_B607D8_H

#include "classes/gf/GfMenuObject.h"
#include "gf/GfMenuSequence.h"
#include "mm/mtl/IntrusivePtr.h"

namespace gf { class GfMenuCallContext; }
namespace gf { class GfMenuReferenceNumber; }

namespace gf {
// table 0x7100B607D8: the menu object of gf_menu_obj_btlch_telop.cpp (new in 3.0.1; nothing names the class yet). It
// shows the battle challenge's telops (LAY_start, TXT_wave_title, ...)
class TUnk_B607D8 : public ::gf::GfMenuObject {
public:
    TUnk_B607D8(unsigned int handle);
    virtual ~TUnk_B607D8();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    // Placeholder names: new in 3.0.1, nothing in 1.0.0's place names them. Members because they are its sequence's
    // jobs (m_seq calls them on this object; the functions that queue them are this class's too).
    // fn_71003B1DA4 waits for m_animHandle's animation; fn_71003B219C sends LAY_main the close event (0x22);
    // fn_71003B2558 waits for m_ctrl's control; fn_71003B259C and fn_71003B26B4 do nothing (true at once).
    bool fn_71003B1DA4();
    bool fn_71003B219C();
    bool fn_71003B2558();
    bool fn_71003B259C();
    bool fn_71003B26B4();
    // what fn_71003B0CE4 sends with its open event (0x21); the names are not the original's
    struct OpenParam {
        int m_type;   // the event's first parameter
        int m_value;  // its second, for types 1, 2 and 3 only
    };
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its unit holds only this
    // class's functions. What it does: when GfMenuObjUtil::fn_710048FD30(1), GfGameManager::fn_71002AC580 and
    // checkCCStart(context) hold and attached object 0x88 lives, sends it the open event (0x21) with param and
    // starts the context on it (true); otherwise aborts the context (false). TUnk_B60848::fn_71003B3EF4 calls it.
    static bool fn_71003B0CE4(GfMenuCallContext* context, const OpenParam& param);
    unsigned char pad_24[4];
    GfMenuSequence<TUnk_B607D8, 8> m_seq;
    int m_ctrl;  // a control slot update and fn_71003B2558 wait for, -1 for none (the name is not the original's)
    unsigned int m_animHandle;  // the object fn_71003B1DA4 waits for (the name is not the original's)
    mm::mtl::IntrusivePtr<GfMenuReferenceNumber> m_number;  // the reference adapters' number (the name is not the original's)
    unsigned char pad_2C8[4];
    unsigned int m_wave;  // cleared by the constructor (the name is not the original's)
};
}  // namespace gf

#endif
