#ifndef CLASSES_EVENT_VOICEMANAGER_H
#define CLASSES_EVENT_VOICEMANAGER_H
#include "classes/event/IManager.h"
#include "classes/mm/mtl/Singleton.h"
#include "classes/event/VoiceMaker.h"
#include "classes/event/VoiceOneShoter.h"
#include "classes/event/VoicePlayer.h"

namespace event { enum MSG_TYPE : int; }
namespace event { class IVoiceEvent; }

namespace event {
// table 0x7100B3D888; base at 0x0 event::IManager, base at 0x8 mm::mtl::Singleton<event::VoiceManager>
class VoiceManager : public IManager, public mm::mtl::Singleton<VoiceManager> {
public:
    virtual ~VoiceManager();  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
    // out of line (mm::mtl::Singleton<event::VoiceManager>::getPtr's static calls it)
    VoiceManager();
    // with bit 0 of pad_10 set: the voice's lip-sync target (bit 1: found), then the voice unless skipping
    bool playAuto(const char* name, float frame, IVoiceEvent* event);
    // the result of VoiceOneShoter::play (unit_71006665E4's caller ignores it)
    bool playOneshot(const char* name, float volume);
    void preload(float frame, const char* name);
    void preloadAuto(float frame, const char* name);

    unsigned int pad_10;  // bit 0: preloadAuto and playAuto run; cleared by messages 4 and 12
    unsigned int pad_14;  // bit 0: message 16 draws the voice state ("VOICE")
    VoiceMaker m_maker;  // 0x18 (the name is not the original's)
    VoicePlayer m_player;  // 0x230 (the name is not the original's)
    VoiceOneShoter m_oneShoter;  // 0x6f8 (the name is not the original's)
};
}  // namespace event

#endif
