#ifndef CLASSES_GF_GFMENUOBJTARGETINFO_ENEMYLISTENER_H
#define CLASSES_GF_GFMENUOBJTARGETINFO_ENEMYLISTENER_H

#include "classes/gf/GfMenuObjTargetInfo.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B64C20
class GfMenuObjTargetInfo::EnemyListener {
public:
    virtual ~EnemyListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
