#ifndef CLASSES_EVENT_COPYDATAMANAGER_H
#define CLASSES_EVENT_COPYDATAMANAGER_H

namespace event { enum MSG_TYPE : int; }

namespace event {
// a base of event::CopydataManager no evidence names yet
class TUnk_B3E160 {
public:
    virtual ~TUnk_B3E160();
    virtual void OnEventProc(event::MSG_TYPE) = 0;
};
// a base of event::CopydataManager no evidence names yet
class TUnk_B3E188 {
public:
    virtual ~TUnk_B3E188();
};
// table 0x7100B3E160; base at 0x0 unknown (TUnk_B3E160), base at 0x8 unknown (TUnk_B3E188)
class CopydataManager : public TUnk_B3E160, public TUnk_B3E188 {
public:
    virtual ~CopydataManager();  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
};
}  // namespace event

#endif
