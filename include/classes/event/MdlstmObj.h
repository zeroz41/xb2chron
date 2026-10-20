#ifndef CLASSES_EVENT_MDLSTMOBJ_H
#define CLASSES_EVENT_MDLSTMOBJ_H

namespace event { namespace IResEvent { class PARAM; }}

namespace event {
// table 0x7100B3C4E8
class MdlstmObj {
public:
    virtual void OnResEvent(event::IResEvent::PARAM const&);  // slot 0
    virtual ~MdlstmObj();  // slot 1
};
}  // namespace event

#endif
