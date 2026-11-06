#ifndef CLASSES_EVENT_IRESPACKEVENT_H
#define CLASSES_EVENT_IRESPACKEVENT_H

namespace event {
// what a ResPack reports to: ResPack::load and ResPackManager::load take an event::IResPackEvent* (their mangled
// names), ResManager::loadPack passes its base at 0x10, whose only slot is OnPackEvent(IResPackEvent::PARAM const&);
// ResPack::func_loading calls slot 0 on it
class IResPackEvent {
public:
    // what a pack reports for each of its files (ResManager::OnPackEvent reads it); the names are not the original's
    class PARAM {
    public:
        const char* m_name;  // 0x0: the file's name
        void* m_data;  // 0x8: its data
        unsigned long m_size;  // 0x10: its size
    };
    virtual void OnPackEvent(PARAM const&) = 0;
};
}  // namespace event

#endif
