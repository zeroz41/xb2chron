#ifndef CLASSES_EVENT_LIGHTMANAGER_H
#define CLASSES_EVENT_LIGHTMANAGER_H

namespace event { enum MSG_TYPE : int; }

namespace event {
// a base of event::LightManager no evidence names yet
class TUnk_B3D208 {
public:
    virtual ~TUnk_B3D208();
    virtual void OnEventProc(event::MSG_TYPE) = 0;
};
// a base of event::LightManager no evidence names yet
class TUnk_B3D230 {
public:
    virtual ~TUnk_B3D230();
};
// table 0x7100B3D208; base at 0x0 unknown (TUnk_B3D208), base at 0x8 unknown (TUnk_B3D230)
class LightManager : public TUnk_B3D208, public TUnk_B3D230 {
public:
    virtual ~LightManager();  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
};
}  // namespace event

#endif
