#ifndef CLASSES_EVENT_RESMANAGER_H
#define CLASSES_EVENT_RESMANAGER_H

namespace event { enum MSG_TYPE : int; }
namespace event { namespace IResPackEvent { class PARAM; }}

namespace event {
// a base of event::ResManager no evidence names yet
class TUnk_B3C098 {
public:
    virtual ~TUnk_B3C098();
    virtual void OnEventProc(event::MSG_TYPE) = 0;
    virtual void OnPackEvent(event::IResPackEvent::PARAM const&) = 0;
};
// a base of event::ResManager no evidence names yet
class TUnk_B3C0C8 {
public:
    virtual ~TUnk_B3C0C8();
};
// a base of event::ResManager no evidence names yet
class TUnk_B3C0E8 {
public:
    virtual void OnPackEvent(event::IResPackEvent::PARAM const&) = 0;
};
// table 0x7100B3C098; base at 0x0 unknown (TUnk_B3C098), base at 0x8 unknown (TUnk_B3C0C8), base at 0x10 unknown (TUnk_B3C0E8)
class ResManager : public TUnk_B3C098, public TUnk_B3C0C8, public TUnk_B3C0E8 {
public:
    virtual ~ResManager();  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
    virtual void OnPackEvent(event::IResPackEvent::PARAM const&);  // slot 3
};
}  // namespace event

#endif
