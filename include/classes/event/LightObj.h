#ifndef CLASSES_EVENT_LIGHTOBJ_H
#define CLASSES_EVENT_LIGHTOBJ_H

namespace event {
// table 0x7100B3D1E0
class LightObj {
public:
    virtual ~LightObj();  // slot 0
    void clear();  // 0x71000F76D8 (the destructor calls it)
    // starts the named light animation (ObjectLight::play forwards to it); returns nothing that ObjectLight uses
    void play(const char* name, float frame);
};
}  // namespace event

#endif
