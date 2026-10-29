#ifndef CLASSES_EVENT_LIGHTMANAGER_H
#define CLASSES_EVENT_LIGHTMANAGER_H
#include "classes/event/IManager.h"
#include "classes/mm/mtl/Singleton.h"

namespace event { enum MSG_TYPE : int; }

namespace event { class LightEvt; }

namespace event {
// table 0x7100B3D208; base at 0x0 event::IManager, base at 0x8 mm::mtl::Singleton<event::LightManager>
class LightManager : public IManager, public mm::mtl::Singleton<LightManager> {
public:
    // out of line: Singleton<LightManager>::getPtr registers it with __cxa_atexit (see DofManager.h)
    virtual ~LightManager();  // slot 0
    LightManager();  // out of line (Singleton<LightManager>::getPtr calls it)
    // called by the evt_setup script plugin (application/BF2/ScriptPlayText); a result its callers ignore is declared void
    void loadResource(const char* name);
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
    // fields the constructor initializes; what they hold is not known yet
    // 1.0.0's clear/clearEvtLight/clearOffScrLight (3.0.1 inlines them; defined inline in CharaObj.cpp)
    void clear();
    void clearEvtLight();
    void clearOffScrLight();
    void update();  // out of line
    void render();  // out of line
    unsigned int m_flags;          // 0x10 bit 0: setLightDisp (the name is not the original's)
    unsigned int m_modeFlags;      // 0x14 bit 0: setStreamMode (the name is not the original's)
    LightEvt* m_offScrLights[4];   // 0x18 playOffScrLight indexes it (the name is not the original's)
    LightEvt* m_evtLight;          // 0x38 clearEvtLight deletes it (the name is not the original's)
};
}  // namespace event

#endif
