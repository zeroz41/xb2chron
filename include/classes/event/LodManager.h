#ifndef CLASSES_EVENT_LODMANAGER_H
#define CLASSES_EVENT_LODMANAGER_H

namespace event {
// a base of event::LodManager no evidence names yet
class TUnk_B3D250 {
public:
    virtual ~TUnk_B3D250();
    virtual void vf2();
};
// a base of event::LodManager no evidence names yet
class TUnk_B3D278 {
public:
    virtual ~TUnk_B3D278();
};
// table 0x7100B3D250; base at 0x0 unknown (TUnk_B3D250), base at 0x8 unknown (TUnk_B3D278)
class LodManager : public TUnk_B3D250, public TUnk_B3D278 {
public:
    virtual ~LodManager();  // slot 0
    virtual void vf2();  // slot 2
};
}  // namespace event

#endif
