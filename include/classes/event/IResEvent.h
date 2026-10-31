#ifndef CLASSES_EVENT_IRESEVENT_H
#define CLASSES_EVENT_IRESEVENT_H

namespace event {
// what a resource load reports to: ResManager::load mangles an event::IResEvent* parameter (a class, not a
// namespace); MdlstmObj's table holds OnResEvent(IResEvent::PARAM const&) in slot 0, ahead of its destructor
class IResEvent {
public:
    class PARAM;
    virtual void OnResEvent(PARAM const&) = 0;
};
}  // namespace event

#endif
