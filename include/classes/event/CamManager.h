#ifndef CLASSES_EVENT_CAMMANAGER_H
#define CLASSES_EVENT_CAMMANAGER_H
#include "classes/event/IManager.h"
#include "classes/mm/mtl/Singleton.h"
#include "classes/event/CamFree.h"
#include "classes/event/CamInterface.h"
#include "mm/mtl/FixedVector.h"

namespace event { enum MSG_TYPE : int; class CamObj; }

namespace event {
// table 0x7100B3C9A8; base at 0x0 event::IManager, base at 0x8 mm::mtl::Singleton<event::CamManager>
class CamManager : public IManager, public mm::mtl::Singleton<CamManager> {
public:
    virtual ~CamManager();  // slot 0
    CamManager();  // out of line (0x71000D0134; the evt_setup plugin's Singleton<CamManager>::getPtr calls it)
    // called by the evt_setup script plugin (application/BF2/ScriptPlayText); a result its callers ignore is declared void
    void loadResource(const char* name);
    // named by 1.0.0's symbols (_ZN5event10CamManager8setFocalEb, the evt_setup plugin's focal calls it at the same site)
    void setFocal(bool focal);
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
    void init();
    void clear();
    void update();
    void render();
    unsigned int pad_10;  // 0x10: init clears it
    unsigned int pad_14;
    mm::mtl::FixedVector<CamObj*, 8> m_cams;  // 0x18 (the name is not the original's)
    mm::mtl::FixedVector<CamInterface*, 4> m_interfaces;  // 0x60: init creates 4 (the name is not the original's)
    CamObj* m_cur;  // 0x88 (the name is not the original's)
    CamFree m_free;  // 0x90 (the name is not the original's)
};
}  // namespace event

#endif
