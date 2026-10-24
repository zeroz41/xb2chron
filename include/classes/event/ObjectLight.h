#ifndef CLASSES_EVENT_OBJECTLIGHT_H
#define CLASSES_EVENT_OBJECTLIGHT_H

#include "classes/event/Object.h"
#include "classes/event/LightObj.h"

namespace mm { class Col4; }

namespace event {
// table 0x7100B3E038
class ObjectLight : public ::event::Object {
public:
    virtual ~ObjectLight();  // slot 0
    virtual void update();  // slot 7
    virtual void render(mm::Col4 const&);  // slot 8
    void play(const char* name, float frame);

    // the light the object drives (play forwards to LightObj::play); the name is not the original's
    LightObj* m_light;  // 0x68
};
}  // namespace event

#endif
