#ifndef CLASSES_EVENT_OBJECTMANAGER_H
#define CLASSES_EVENT_OBJECTMANAGER_H

namespace event { enum MSG_TYPE : int; }

namespace event {
// a base of event::ObjectManager no evidence names yet
class TUnk_B3E118 {
public:
    virtual ~TUnk_B3E118();
    virtual void OnEventProc(event::MSG_TYPE) = 0;
};
// a base of event::ObjectManager no evidence names yet
class TUnk_B3E140 {
public:
    virtual ~TUnk_B3E140();
};
// table 0x7100B3E118; base at 0x0 unknown (TUnk_B3E118), base at 0x8 unknown (TUnk_B3E140)
class ObjectManager : public TUnk_B3E118, public TUnk_B3E140 {
public:
    virtual ~ObjectManager();  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
};
}  // namespace event

#endif
