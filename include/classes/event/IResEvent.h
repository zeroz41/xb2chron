#ifndef CLASSES_EVENT_IRESEVENT_H
#define CLASSES_EVENT_IRESEVENT_H

namespace event {
// what a resource load reports to: ResManager::load mangles an event::IResEvent* parameter (a class, not a
// namespace); MdlstmObj's table holds OnResEvent(IResEvent::PARAM const&) in slot 0, ahead of its destructor
class IResEvent {
public:
    // what a load reports (LipsyncRes/MstxtRes/EffectRes::OnResEvent read it); the names are not the original's
    class PARAM {
    public:
        int m_type;  // 0x0: 3 = loaded (the data below is valid), 4 = failed (MstxtRes calls Manager::failureSkip)
        const char* m_name;  // 0x8: EffectRes hands it to EffectPack::createFromMemory as the pack's name
        void* m_data;  // 0x10: the loaded file
        unsigned long m_size;  // 0x18: its size (ResManager::updateNormal stores 8 bytes)
    };
    virtual void OnResEvent(PARAM const&) = 0;
};
}  // namespace event

#endif
