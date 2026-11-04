#ifndef CLASSES_GF_GFMENUOBJPARTYGAUGE_GAUGELISTENER_H
#define CLASSES_GF_GFMENUOBJPARTYGAUGE_GAUGELISTENER_H

#include "classes/gf/GfMenuObjPartyGauge.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B63FA0: initialize makes it for "LAY_gauge"
class GfMenuObjPartyGauge::GaugeListener : public ::ui::UIObjectListener {
public:
    // its state: a 4-aligned aggregate at 0xC that initialize zeroes after storing the table (the names are not the
    // original's)
    struct State {
        int m_ctrl;  // the slot of its last fade (-1 for none)
        int m_open;  // open (0x21) sets it, close (0x22) clears it
        unsigned char pad_8[0x8];
    };
    GaugeListener(GfMenuObjPartyGauge* owner) : m_state(), m_owner(owner) {}
    virtual ~GaugeListener() {}  // slot 0: weak in the original, and its D1 slot is the base's destructor
    virtual void reciveEvent(const ui::EventData& event, unsigned int handle);  // slot 2
    State m_state;
    GfMenuObjPartyGauge* m_owner;
};

// table 0x7100B63FC8: initialize makes it for "LAY_siren". Unnamed class (TUnk_<table low address>): the symbols
// leave it unnamed (no RTTI in 3.0.1, nothing in 1.0.0).
class GfMenuObjPartyGauge::SirenListener : public ::ui::UIObjectListener {
public:
    // its state, as GaugeListener's (the names are not the original's)
    struct State {
        int m_ctrl;       // the slot of its last fade (-1 for none)
        int m_open;       // open (0x21) sets it, close (0x22) clears it
        int m_gaugeCtrl;  // the slot of the colour control on "IMG_siren_en_gauge" (-1 for none)
        int m_hold;       // close with parameter 1 sets it: open fades in only after an open with parameter 1
    };
    SirenListener(GfMenuObjPartyGauge* owner) : m_state(), m_owner(owner) {}
    virtual ~SirenListener() {}  // slot 0: weak in the original, and its D1 slot is the base's destructor
    // slot 2 (the symbols spell it fn_71004574D4)
    virtual void reciveEvent(const ui::EventData& event, unsigned int handle);
    State m_state;
    GfMenuObjPartyGauge* m_owner;
};
}  // namespace gf

#endif
