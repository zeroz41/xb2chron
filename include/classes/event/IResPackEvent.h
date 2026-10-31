#ifndef CLASSES_EVENT_IRESPACKEVENT_H
#define CLASSES_EVENT_IRESPACKEVENT_H

namespace event {
// what a ResPack reports to: ResPack::load and ResPackManager::load take an event::IResPackEvent* (their mangled
// names), ResManager::loadPack passes its base at 0x10, whose only slot is OnPackEvent(IResPackEvent::PARAM const&);
// ResPack::func_loading calls slot 0 on it
class IResPackEvent {
public:
    class PARAM;
    virtual void OnPackEvent(PARAM const&) = 0;
};
}  // namespace event

#endif
