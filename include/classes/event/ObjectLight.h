#ifndef CLASSES_EVENT_OBJECTLIGHT_H
#define CLASSES_EVENT_OBJECTLIGHT_H

#include "classes/event/Object.h"
#include "classes/event/LightObj.h"
#include "classes/event/PosAxis.h"
#include "classes/event/RotAxis.h"

namespace mm { class Col4; }

namespace event {
// table 0x7100B3E038
class ObjectLight : public ::event::Object {
public:
    // 0x71001271CC; ObjectList::createLight passes its name and id
    ObjectLight(const char* name, unsigned int id);
    virtual ~ObjectLight();  // slot 0
    virtual void update();  // slot 7
    virtual void render(mm::Col4 const&);  // slot 8
    void play(const char* name, float frame);
    void setPosAxis(const PosAxis& pos);
    void setRotAxis(const RotAxis& rot);

    // the light the object drives (play forwards to LightObj::play); the name is not the original's
    LightObj* m_light;  // 0x68
    // the constructor sets both axes up with type 1 (as ObjectEffect's); ObjectList::createLight allocates 0xb0
    PosAxis m_pos;  // 0x70
    RotAxis m_rot;  // 0x90
};
}  // namespace event

#endif
