#ifndef CLASSES_EVENT_DATAMANAGER_H
#define CLASSES_EVENT_DATAMANAGER_H

namespace event { enum MSG_TYPE : int; }

namespace event {
// a base of event::DataManager no evidence names yet
class TUnk_B3E2B0 {
public:
    virtual ~TUnk_B3E2B0();
    virtual void OnEventProc(event::MSG_TYPE) = 0;
};
// a base of event::DataManager no evidence names yet
class TUnk_B3E2D8 {
public:
    virtual ~TUnk_B3E2D8();
};
// table 0x7100B3E2B0; base at 0x0 unknown (TUnk_B3E2B0), base at 0x8 unknown (TUnk_B3E2D8)
class DataManager : public TUnk_B3E2B0, public TUnk_B3E2D8 {
public:
    virtual ~DataManager();  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
};
}  // namespace event

#endif
