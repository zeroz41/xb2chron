#ifndef CLASSES_EVENT_VOICEMANAGER_H
#define CLASSES_EVENT_VOICEMANAGER_H

namespace event { enum MSG_TYPE : int; }

namespace event {
// a base of event::VoiceManager no evidence names yet
class TUnk_B3D888 {
public:
    virtual ~TUnk_B3D888();
    virtual void OnEventProc(event::MSG_TYPE) = 0;
};
// a base of event::VoiceManager no evidence names yet
class TUnk_B3D8B0 {
public:
    virtual ~TUnk_B3D8B0();
};
// table 0x7100B3D888; base at 0x0 unknown (TUnk_B3D888), base at 0x8 unknown (TUnk_B3D8B0)
class VoiceManager : public TUnk_B3D888, public TUnk_B3D8B0 {
public:
    virtual ~VoiceManager();  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
};
}  // namespace event

#endif
