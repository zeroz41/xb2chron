#ifndef CLASSES_EVENT_MDLSTMMANAGER_H
#define CLASSES_EVENT_MDLSTMMANAGER_H

namespace event { enum MSG_TYPE : int; }

namespace event {
// a base of event::MdlstmManager no evidence names yet
class TUnk_B3C510 {
public:
    virtual ~TUnk_B3C510();
    virtual void OnEventProc(event::MSG_TYPE) = 0;
};
// a base of event::MdlstmManager no evidence names yet
class TUnk_B3C538 {
public:
    virtual ~TUnk_B3C538();
};
// table 0x7100B3C510; base at 0x0 unknown (TUnk_B3C510), base at 0x8 unknown (TUnk_B3C538)
class MdlstmManager : public TUnk_B3C510, public TUnk_B3C538 {
public:
    virtual ~MdlstmManager();  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
};
}  // namespace event

#endif
