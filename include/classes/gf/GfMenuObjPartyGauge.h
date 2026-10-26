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
    class GaugeListener;
    virtual ~GfMenuObjPartyGauge();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
};
}  // namespace gf

#endif
