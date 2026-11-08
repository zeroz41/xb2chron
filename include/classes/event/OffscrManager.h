#ifndef CLASSES_EVENT_OFFSCRMANAGER_H
#define CLASSES_EVENT_OFFSCRMANAGER_H
#include "classes/event/IManager.h"
#include "classes/mm/mtl/Singleton.h"

namespace ml { class ScnRenderDrViewCtrl; }

namespace event { enum MSG_TYPE : int; }

namespace event {
// table 0x7100B3C168; base at 0x0 event::IManager, base at 0x8 mm::mtl::Singleton<event::OffscrManager>
class OffscrManager : public IManager, public mm::mtl::Singleton<OffscrManager> {
public:
    virtual ~OffscrManager() {}  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
    // deletes the views of screens 1-3 (handing each back to the scene renderer first)
    void clear();
    // news the view of screen id (1-3, 256x256) and hands it to the scene renderer, unless it has one
    void createScreen(unsigned int id);

    // the offscreen views by screen id (createScreen fills 1-3; 0 is never used); the name is not the original's
    ml::ScnRenderDrViewCtrl* m_views[4];  // 0x10
};
}  // namespace event

#endif
