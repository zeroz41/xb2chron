#ifndef CLASSES_EVENT_GROUPMANAGER_H
#define CLASSES_EVENT_GROUPMANAGER_H

namespace event { enum MSG_TYPE : int; }

namespace event {
// a base of event::GroupManager no evidence names yet
class TUnk_B3D010 {
public:
    virtual ~TUnk_B3D010();
    virtual void OnEventProc(event::MSG_TYPE) = 0;
};
// a base of event::GroupManager no evidence names yet
class TUnk_B3D038 {
public:
    virtual ~TUnk_B3D038();
};
// table 0x7100B3D010; base at 0x0 unknown (TUnk_B3D010), base at 0x8 unknown (TUnk_B3D038)
class GroupManager : public TUnk_B3D010, public TUnk_B3D038 {
public:
    virtual ~GroupManager();  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
};
}  // namespace event

#endif
