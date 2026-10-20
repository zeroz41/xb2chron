#ifndef CLASSES_EVENT_MSTXTRES_H
#define CLASSES_EVENT_MSTXTRES_H

namespace event { namespace IResEvent { class PARAM; }}

namespace event {
// table 0x7100B3C5A0
class MstxtRes {
public:
    virtual void OnResEvent(event::IResEvent::PARAM const&);  // slot 0
    virtual ~MstxtRes();  // slot 1
};
}  // namespace event

#endif
