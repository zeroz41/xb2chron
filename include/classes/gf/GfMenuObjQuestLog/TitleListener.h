#ifndef CLASSES_GF_GFMENUOBJQUESTLOG_TITLELISTENER_H
#define CLASSES_GF_GFMENUOBJQUESTLOG_TITLELISTENER_H

#include "classes/gf/GfMenuObjQuestLog.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B644E8
class GfMenuObjQuestLog::TitleListener {
public:
    virtual ~TitleListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
