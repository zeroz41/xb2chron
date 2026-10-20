#ifndef CLASSES_GF_GFMENUSCRIPTMANAGER_SCRIPTLISTENER_H
#define CLASSES_GF_GFMENUSCRIPTMANAGER_SCRIPTLISTENER_H

#include "classes/gf/GfMenuScriptManager.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B5EFE8
class GfMenuScriptManager::ScriptListener {
public:
    virtual ~ScriptListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
