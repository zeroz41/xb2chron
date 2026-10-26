#ifndef CLASSES_GF_GFMENUOBJPARTYGAUGE_H
#define CLASSES_GF_GFMENUOBJPARTYGAUGE_H

#include "classes/gf/GfMenuObject.h"

namespace gf {
// table 0x7100B63F40
class GfMenuObjPartyGauge : public ::gf::GfMenuObject {
public:
    static void close();  // 1.0.0 symbol
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its address lies in this
    // class's unit. What it does: clears the byte at 0x7100EAB929 (GfMenuManager::fn_710035CE3C calls it after
    // terminating ui layer 102; reciveEvent calls it too).
    static void fn_71004569F8();
    // 1.0.0 symbol; 3.0.1's copy still carries a placeholder name (fn_7100456A1C), see the menu manager's renames
    static void disp(bool disp);
    // Placeholder names: new in 3.0.1, nothing in 1.0.0's place names them. Members because their addresses lie in
    // this class's unit. What they do: while GfMenuObjUtil::fn_710048FD30(3) holds (the last four also
    // GfMenuReference::fn_7100368418(4)), each sends an event to a child of the attached party gauge object:
    // fn_7100456B60 / fn_7100456EA0 event 0x101 with the flag to "LAY_gauge" / "LAY_siren" (GfMenuReference::
    // fn_7100368570, record 1 / 0; btl::UIManager::fn_71000B2238 calls fn_7100456B60 too); fn_7100456CB4 event 0x103
    // with the flag to "LAY_gauge"; fn_7100456E00 / fn_7100456D60 event 0x22 / 0x21 to "LAY_siren" (all three from
    // GfMenuReference::fn_7100368600).
    static void fn_7100456B60(bool flag);
    static void fn_7100456EA0(bool flag);
    static void fn_7100456CB4(bool flag);
    static void fn_7100456E00();
    static void fn_7100456D60();
    class GaugeListener;
    virtual ~GfMenuObjPartyGauge();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
};
}  // namespace gf

#endif
