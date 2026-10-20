#ifndef CLASSES_GF_GFMENUOBJQUESTLOG_LOGLISTENER_H
#define CLASSES_GF_GFMENUOBJQUESTLOG_LOGLISTENER_H

#include "classes/gf/GfMenuObjQuestLog.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B64510
class GfMenuObjQuestLog::LogListener {
public:
    virtual ~LogListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
