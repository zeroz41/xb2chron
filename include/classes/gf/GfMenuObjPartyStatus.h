#ifndef CLASSES_GF_GFMENUOBJPARTYSTATUS_H
#define CLASSES_GF_GFMENUOBJPARTYSTATUS_H

#include "classes/gf/GfMenuObject.h"

namespace ui { class UIObjectAcc; }

namespace gf {

class GfMenuCallContext;

// table 0x7100B63FF0
class GfMenuObjPartyStatus : public ::gf::GfMenuObject {
public:
    // what openComboRequest and resetComboRequest pass on to setupComboReq through their events (the names are not
    // the original's)
    struct RequestParam {
        unsigned short m_combo;   // the elemental combo whose name and colour the request shows
        unsigned short m_effect;  // the effect image's index + 1 (0 hides it)
        unsigned int m_button;    // the button whose icon it shows (0: the request slot's default)
        bool m_showButton;        // shows "IMG_combo_req2_btn"
    };

    GfMenuObjPartyStatus(unsigned int handle);

    static void open(bool flag);  // 1.0.0 symbol
    static void close(bool flag);  // 1.0.0 symbol
    static void lock(bool lock);  // 1.0.0 symbol (GfMenuReference::clearPartyStatusLock calls it)
    static void attachComboRequest(GfMenuCallContext* context);  // btl::DataManager::InitializeComboRequestUI
    // events to the combo request object: open (0x101), close (0x102) and reset (0x103) a request slot
    static void openComboRequest(unsigned short index, const RequestParam& param);
    static void closeComboRequest(unsigned short index, bool flag);
    static void resetComboRequest(unsigned short index, const RequestParam& param);
    // an event (0x109) to the party status object: a party member changed
    static void memberChange(unsigned short member, unsigned int value);

    class ComboReqListener;
    class MainListener;

    virtual ~GfMenuObjPartyStatus();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4

    // shows the party's members on the object of that handle and opens the combo requests; -1 without a leader,
    // else the value it is given
    int openPartyStatus(unsigned int handle, int value);
    void closePartyStatus(unsigned int handle, int value);
    void setupComboReq(const ui::UIObjectAcc& acc, unsigned short index, unsigned short combo, bool showButton,
                       unsigned short effect, unsigned int button);

    unsigned char pad_24[0xC];
    // per request slot: the control of its "IMG_combo_req2_eff" rotation (-1 for none) (the name is not the
    // original's)
    int m_effectCtrl[3];
    bool m_locked;  // lock sets it: close waits while it is set (the name is not the original's)
    // per request slot: the control of its "LAY_combo_req2" fade (-1 for none) (the name is not the original's)
    int m_slotCtrl[3];
};

}  // namespace gf

#endif
