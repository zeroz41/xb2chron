#ifndef CLASSES_EVENT_VOICEMANAGER_H
#define CLASSES_EVENT_VOICEMANAGER_H
#include "classes/event/IManager.h"
#include "classes/mm/mtl/Singleton.h"

namespace event { enum MSG_TYPE : int; }

namespace event {
// table 0x7100B3D888; base at 0x0 event::IManager, base at 0x8 mm::mtl::Singleton<event::VoiceManager>
class VoiceManager : public IManager, public mm::mtl::Singleton<VoiceManager> {
public:
    virtual ~VoiceManager();  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
    // out of line (mm::mtl::Singleton<event::VoiceManager>::getPtr's static calls it)
    VoiceManager();
    void playOneshot(const char* name, float volume);
    void preload(float frame, const char* name);
    void preloadAuto(float frame, const char* name);
};
}  // namespace event

#endif
