#ifndef CLASSES_GF_GFMENUOBJQUESTLOG_COMPLETELISTENER_H
#define CLASSES_GF_GFMENUOBJQUESTLOG_COMPLETELISTENER_H

#include "classes/gf/GfMenuObjQuestLog.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B64560
class GfMenuObjQuestLog::CompleteListener {
public:
    virtual ~CompleteListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
