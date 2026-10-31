#ifndef CLASSES_UI_UIPARTICLEEMITTER_H
#define CLASSES_UI_UIPARTICLEEMITTER_H

#include "classes/ui/UIParticleData.h"
#include "mm/Col4.h"
#include "mm/Vec2.h"
#include "mm/mtl/Vector.h"

namespace fw { class UpdateInfo; }

namespace ui {
// table 0x7100B74FD8
class UIParticleEmitter {
public:
    // one live particle (1.0.0's name; its field names are not the original's: each is named after the emitter
    // parameter update draws it from)
    struct Particle {
        float m_item1;  // UIParticleData's id 1
        float m_item2;  // id 2
        mm::Col4 m_colorStart;
        mm::Col4 m_colorEnd;
        float m_item3;  // id 3
        float m_item4;  // id 4
        mm::Vec2 m_pos;
        mm::Vec2 m_velocity;
        float m_radialAccel;
        float m_tangentialAccel;
        float m_age;   // seconds lived: update erases the particle when it reaches m_life
        float m_life;
    };
    // the data's particle parameters, as create copies them (the name is not the original's)
    struct Param {
        UIParticleData::Range m_item1;
        UIParticleData::Range m_item2;
        UIParticleData::Range m_item3;
        UIParticleData::Range m_item4;
        UIParticleData::ColorRange m_colorStart;
        UIParticleData::ColorRange m_colorEnd;
        UIParticleData::Range m_life;
        float m_spreadX;
        float m_spreadY;
        UIParticleData::Range m_angle;
        UIParticleData::Range m_speed;
        UIParticleData::Range m_radialAccel;
        UIParticleData::Range m_tangentialAccel;
    };

    // 1.0.0 has it out of line; 3.0.1 only inlines it into create (defined inline in the .cpp)
    UIParticleEmitter();
    virtual ~UIParticleEmitter();  // slot 0
    static UIParticleEmitter* create(const UIParticleData& data);  // null when it makes none
    void update(const fw::UpdateInfo& info);
    float m_rate;  // UIParticleManager gives it 1 less its load reduction (the name is not the original's)
    unsigned char pad_0C[0x4];
    float m_x;    // UIParticleManager::setEmitterPos
    float m_y;
    unsigned char pad_18[0x8];
    float m_rot;  // UIParticleManager::setEmitterRot
    // the names below are not the original's
    float m_time;        // seconds emitted (update; held at m_duration unless that is -1)
    float m_duration;    // the data's
    float m_interval;    // seconds between two particles: 1 / the data's rate
    unsigned int m_count;  // particles emitted so far
    unsigned char pad_34[0xC];
    mm::Vec2 m_gravity;  // the data's gravity scaled by 1 / 900 and -1 / 900
    Param m_param;
    mm::mtl::Vector<Particle> m_particles;
    bool m_enable;  // update emits only while it is set
};
}  // namespace ui

#endif
