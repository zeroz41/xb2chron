#ifndef CLASSES_EVENT_MODELOBJ_H
#define CLASSES_EVENT_MODELOBJ_H

namespace event { namespace IResEvent { class PARAM; }}

namespace event {
// table 0x7100B3C1B0
class ModelObj {
public:
    virtual void OnResEvent(event::IResEvent::PARAM const&);  // slot 0
    virtual ~ModelObj();  // slot 1
};
}  // namespace event

#endif
