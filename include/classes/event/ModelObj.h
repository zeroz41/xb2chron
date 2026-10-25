#ifndef CLASSES_EVENT_MODELOBJ_H
#define CLASSES_EVENT_MODELOBJ_H

namespace event { namespace IResEvent { class PARAM; }}
namespace gf { class GfEvtModel; }

namespace event {
// table 0x7100B3C1B0
class ModelObj {
public:
    virtual void OnResEvent(event::IResEvent::PARAM const&);  // slot 0
    virtual ~ModelObj();  // slot 1

    unsigned char pad_8[0x120];
    // the game model; ModelManager::update counts m_busyWait down and resets it to 2 while it is busy; the name is not the original's
    gf::GfEvtModel* m_model;  // 0x128
    int m_busyWait;  // 0x130
};
}  // namespace event

#endif
