#ifndef CLASSES_EVENT_CAMMANAGER_H
#define CLASSES_EVENT_CAMMANAGER_H
#include "classes/event/IManager.h"
#include "classes/mm/mtl/Singleton.h"

namespace event { enum MSG_TYPE : int; }

namespace event {
// table 0x7100B3C9A8; base at 0x0 event::IManager, base at 0x8 mm::mtl::Singleton<event::CamManager>
class CamManager : public IManager, public mm::mtl::Singleton<CamManager> {
public:
    virtual ~CamManager();  // slot 0
    CamManager();  // out of line (Singleton<CamManager>::getPtr calls it)
    // called by the evt_setup script plugin (application/BF2/ScriptPlayText); a result its callers ignore is declared void
    void loadResource(const char* name);
    // named by 1.0.0's symbols (_ZN5event10CamManager8setFocalEb, the evt_setup plugin's focal calls it at the same site)
    void setFocal(bool focal);
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
    void init();
    void clear();
    void update();
    void render();
};
}  // namespace event

#endif
