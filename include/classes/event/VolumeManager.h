#ifndef CLASSES_EVENT_VOLUMEMANAGER_H
#define CLASSES_EVENT_VOLUMEMANAGER_H

namespace event { enum MSG_TYPE : int; }

namespace event {
// a base of event::VolumeManager no evidence names yet
class TUnk_B3D930 {
public:
    virtual ~TUnk_B3D930();
    virtual void OnEventProc(event::MSG_TYPE) = 0;
};
// a base of event::VolumeManager no evidence names yet
class TUnk_B3D958 {
public:
    virtual ~TUnk_B3D958();
};
// table 0x7100B3D930; base at 0x0 unknown (TUnk_B3D930), base at 0x8 unknown (TUnk_B3D958)
class VolumeManager : public TUnk_B3D930, public TUnk_B3D958 {
public:
    virtual ~VolumeManager() {}  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
};
}  // namespace event

#endif
