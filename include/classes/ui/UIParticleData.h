#ifndef CLASSES_UI_UIPARTICLEDATA_H
#define CLASSES_UI_UIPARTICLEDATA_H

namespace ui {
// table 0x7100B74FB8; an emitter's parameters, read from a "UIP " block (deserialize)
class UIParticleData {
public:
    UIParticleData();
    virtual ~UIParticleData();  // slot 0
    void deserialize(const void* data, unsigned int size);
    unsigned char pad_08[0x64];
    // the particles' life and its random addition: UIShapeParticle sizes its quads for (m_life + m_lifeRange) *
    // m_rate particles; UIParticleEmitter::create copies both (the names are not the original's)
    float m_life;
    float m_lifeRange;
    float m_rate;  // particles a second: UIParticleEmitter::create's interval is 1 / m_rate (not the original's name)
    unsigned char pad_78[0x30];
};
}  // namespace ui

#endif
