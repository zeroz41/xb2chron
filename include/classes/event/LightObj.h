#ifndef CLASSES_EVENT_LIGHTOBJ_H
#define CLASSES_EVENT_LIGHTOBJ_H
#include "mm/mtl/FixStr.h"
#include "mm/Vec3.h"
#include "classes/ml/ScnObjLight.h"

namespace event {
// table 0x7100B3D1E0
class LightObj {
public:
    // 1.0.0's LightObj(int) (0x71000E2D00 there); inline in 3.0.1 (ObjectLight's constructor holds its stores)
    LightObj(int id)
        : m_state(0), m_lgt(nullptr), m_id(id), m_name(), m_stmData(nullptr), m_pos(mm::Vec3::zero),
          m_rot(mm::Vec3::zero) {}
    virtual ~LightObj();  // slot 0
    void clear();  // 0x71000F76D8 (the destructor calls it)
    // starts the named light animation (ObjectLight::play forwards to it); returns nothing that ObjectLight uses
    void play(const char* name, float frame);
    // out of line (LightManager::render calls it): the light's debug panel at x, y
    void render(int x, int y);

    // 1.0.0's LightObj(int) zeroes m_state, m_lgt, m_name, m_stmData and sets m_id, m_pos/m_rot to Vec3::zero; the
    // field names are not the original's
    int m_state;  // 0x8: clear() zeroes it
    // the light: 1.0.0's update passes m_pos and m_rot to its slots at 0x90 and 0x98, clear() releases it to the scene
    ml::ScnObjLight* m_lgt;  // 0x10
    int m_id;  // 0x18: LightObj(int)'s argument
    mm::mtl::FixStr<128> m_name;  // 0x1c: render shows its file name
    // freed through MotstmManager in stream mode (LightManager::isStreamMode) when clear() drops it
    void* m_stmData;  // 0xa0
    float m_life;  // 0xa8: render's "life(%.2f)"; 1.0.0's update counts it down and releases the light below 0
    mm::Vec3 m_pos;  // 0xb0: render's "pos:"
    mm::Vec3 m_rot;  // 0xc0: render's "rot:" (radians, shown in degrees)
};
}  // namespace event

#endif
