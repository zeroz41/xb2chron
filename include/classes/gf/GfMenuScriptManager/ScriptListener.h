#ifndef CLASSES_GF_GFMENUSCRIPTMANAGER_SCRIPTLISTENER_H
#define CLASSES_GF_GFMENUSCRIPTMANAGER_SCRIPTLISTENER_H

#include "classes/gf/GfMenuScriptManager.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B5EFE8: queues a UI object's events on the script tied to it
class GfMenuScriptManager::ScriptListener : public ::ui::UIObjectListener {
public:
    virtual ~ScriptListener() {}  // slot 0: weak in the original, and its D1 slot is the base's destructor
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
