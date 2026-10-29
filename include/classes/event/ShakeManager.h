#ifndef CLASSES_EVENT_SHAKEMANAGER_H
#define CLASSES_EVENT_SHAKEMANAGER_H

#include "classes/event/Shaker.h"
#include "mm/mtl/FixStr.h"
#include "classes/event/IManager.h"
#include "classes/mm/mtl/Singleton.h"

namespace event { enum MSG_TYPE : int; }

namespace event {
// table 0x7100B3D4F8; base at 0x0 event::IManager, base at 0x8 mm::mtl::Singleton<event::ShakeManager>
class ShakeManager : public IManager, public mm::mtl::Singleton<ShakeManager> {
public:
    virtual ~ShakeManager();  // slot 0
    ShakeManager();  // out of line (Singleton<ShakeManager>::getPtr calls it)
    void play(const char* name, float p0, float p1, float p2);
    void setIdleShake(bool enable);
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
    static const mm::mtl::FixStr<32> s_names[4];  // the shake types' names
    // 1.0.0 has it out of line (0x71000EDE80); 3.0.1 inlines it into OnEventProc
    void clear();
    void update();

    unsigned int m_flags;  // @0x10, update() tests bit 1; the name is not the original's
    unsigned char pad_0x14[0x4];
    Shaker m_shaker;  // @0x18 (the constructor stores event::Shaker's table there); the name is not the original's
};
}  // namespace event

#endif
