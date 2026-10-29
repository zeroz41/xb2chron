#ifndef CLASSES_EVENT_SKIPMANAGER_H
#define CLASSES_EVENT_SKIPMANAGER_H
#include "classes/event/IManager.h"
#include "classes/mm/mtl/Singleton.h"

namespace event { enum MSG_TYPE : int; }

namespace event {
// table 0x7100B3E1F0; base at 0x0 event::IManager, base at 0x8 mm::mtl::Singleton<event::SkipManager>
class SkipManager : public IManager, public mm::mtl::Singleton<SkipManager> {
public:
    SkipManager();  // out of line (0x7100133CD4); the script plugins' getPtr statics call it
    virtual ~SkipManager();  // slot 0
    // whether the scene is being skipped fast (evt_chara's mount then queues nothing)
    bool isSkipFast() const;
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
    bool isSkip() const;
    // 1.0.0's clear/update/tail (3.0.1 inlines them; defined inline in CharaObj.cpp)
    void clear();
    void update();
    void tail();
    void setSkipVolume(bool);  // out of line

private:
    // bit 0: skipping (isSkip); the name is not the original's
    unsigned int m_flags;  // 0x10
    // fields the constructor initializes; what they hold is not known yet
    unsigned int pad_14;
    float m_endFrame;  // 0x18 -1.0f at first; getEndFrame returns it (the name is not the original's)
    unsigned char pad_1c[0x4];
};
}  // namespace event

#endif
