#ifndef CLASSES_EVENT_AGELOGMANAGER_H
#define CLASSES_EVENT_AGELOGMANAGER_H

namespace event { enum MSG_TYPE : int; }

namespace event {
// a base of event::AgelogManager no evidence names yet
class TUnk_B3C618 {
public:
    virtual ~TUnk_B3C618();
    virtual void OnEventProc(event::MSG_TYPE) = 0;
};
// a base of event::AgelogManager no evidence names yet
class TUnk_B3C640 {
public:
    virtual ~TUnk_B3C640();
};
// table 0x7100B3C618; base at 0x0 unknown (TUnk_B3C618), base at 0x8 unknown (TUnk_B3C640)
class AgelogManager : public TUnk_B3C618, public TUnk_B3C640 {
public:
    virtual ~AgelogManager();  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
};
}  // namespace event

#endif
