#ifndef CLASSES_GF_GFMENUOBJENVIRONMENTINFO_LISTLISTENER_H
#define CLASSES_GF_GFMENUOBJENVIRONMENTINFO_LISTLISTENER_H

#include "classes/gf/GfMenuObjEnvironmentInfo.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B61DB0
class GfMenuObjEnvironmentInfo::ListListener {
public:
    virtual ~ListListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
