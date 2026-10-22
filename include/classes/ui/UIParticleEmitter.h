#ifndef CLASSES_UI_UIPARTICLEEMITTER_H
#define CLASSES_UI_UIPARTICLEEMITTER_H

namespace fw { class UpdateInfo; }
namespace ui { class UIParticleData; }

namespace ui {
// table 0x7100B74FD8
class UIParticleEmitter {
public:
    virtual ~UIParticleEmitter();  // slot 0
    static UIParticleEmitter* create(const UIParticleData& data);  // null when it makes none
    void update(const fw::UpdateInfo& info);
    float m_rate;  // UIParticleManager gives it 1 less its load reduction (the name is not the original's)
    unsigned char pad_0C[0x4];
    float m_x;    // UIParticleManager::setEmitterPos
    float m_y;
    unsigned char pad_18[0x8];
    float m_rot;  // UIParticleManager::setEmitterRot
};
}  // namespace ui

#endif
