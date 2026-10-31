#ifndef CLASSES_UI_UIPARTICLEDATA_H
#define CLASSES_UI_UIPARTICLEDATA_H

namespace ui {
// table 0x7100B74FB8; an emitter's parameters, read from a "UIP " block (deserialize): each item is an id (1 to 23)
// and an 8-byte value, a float or a Range. The field names are not the original's: the ids are deserialize's,
// what a field does is UIParticleEmitter::update's use of it.
class UIParticleData {
public:
    // a value and how far a random draw may move it either way (UIParticleEmitter::update: value + range * [-1, 1))
    struct Range {
        float value;
        float range;
    };
    // a colour, each component a Range (update clamps the draws to [0, 1])
    struct ColorRange {
        Range r;
        Range g;
        Range b;
        Range a;
    };

    UIParticleData();
    virtual ~UIParticleData();  // slot 0
    void deserialize(const void* data, unsigned int size);
    Range m_item1;              // id 1: a particle's float at 0x00 (not used by the emitter itself)
    Range m_item2;              // id 2: a particle's float at 0x04
    Range m_item3;              // id 3: a particle's float at 0x28
    Range m_item4;              // id 4: a particle's float at 0x2C
    ColorRange m_colorStart;    // ids 5 to 8: a particle's first colour
    ColorRange m_colorEnd;      // ids 9 to 12: its second colour
    float m_duration;           // id 13: how long the emitter emits, -1 for ever
    // id 14: the particles' life: UIShapeParticle sizes its quads for (value + range) * m_rate particles
    Range m_life;
    float m_rate;               // id 15: particles a second: UIParticleEmitter::create's interval is 1 / m_rate
    Range m_angle;              // id 16: the direction a particle leaves in, in degrees
    Range m_speed;              // id 17: its speed (update divides it by 30)
    float m_spreadX;            // id 18: how far from the emitter a particle starts, either way
    float m_spreadY;            // id 19
    float m_gravityX;           // id 20: an acceleration on every particle (create scales it by 1 / 900)
    float m_gravityY;           // id 21 (create scales it by -1 / 900)
    Range m_radialAccel;        // id 22: a particle's acceleration away from the emitter (scaled by 1 / 900)
    Range m_tangentialAccel;    // id 23: its acceleration across that direction (scaled by 1 / 900)
};
}  // namespace ui

#endif
