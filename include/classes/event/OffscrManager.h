#ifndef CLASSES_EVENT_OFFSCRMANAGER_H
#define CLASSES_EVENT_OFFSCRMANAGER_H

namespace event { enum MSG_TYPE : int; }

namespace event {
// a base of event::OffscrManager no evidence names yet
class TUnk_B3C168 {
public:
    virtual ~TUnk_B3C168();
    virtual void OnEventProc(event::MSG_TYPE) = 0;
};
// a base of event::OffscrManager no evidence names yet
class TUnk_B3C190 {
public:
    virtual ~TUnk_B3C190();
};
// table 0x7100B3C168; base at 0x0 unknown (TUnk_B3C168), base at 0x8 unknown (TUnk_B3C190)
class OffscrManager : public TUnk_B3C168, public TUnk_B3C190 {
public:
    virtual ~OffscrManager() {}  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
};
}  // namespace event

#endif
