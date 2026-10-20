#ifndef CLASSES_GF_GFMENUOBJOPERATIONINFO_MAINLISTENER_H
#define CLASSES_GF_GFMENUOBJOPERATIONINFO_MAINLISTENER_H

#include "classes/gf/GfMenuObjOperationInfo.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B63C80
class GfMenuObjOperationInfo::MainListener {
public:
    virtual ~MainListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
