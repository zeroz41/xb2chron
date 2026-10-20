#ifndef CLASSES_GF_GFMENUOBJBATTLETELOP_UNITECOMBOLISTENER_H
#define CLASSES_GF_GFMENUOBJBATTLETELOP_UNITECOMBOLISTENER_H

#include "classes/gf/GfMenuObjBattleTelop.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B5FD90
class GfMenuObjBattleTelop::UniteComboListener {
public:
    virtual ~UniteComboListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
