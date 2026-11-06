#ifndef CLASSES_EVENT_CHARAEFFECTPLAYER_H
#define CLASSES_EVENT_CHARAEFFECTPLAYER_H

#include "classes/event/AnmF32.h"
#include "fw/Message.h"
#include "mm/Vec3.h"

namespace gf { class GF_OBJ_HANDLE; }

namespace event {
// table 0x7100B3CA98
class CharaEffectPlayer {
public:
    virtual ~CharaEffectPlayer();  // slot 0
    // the volume fade's kind (the evt_chara script commands pass 1); no enumerator is named. Each kind keeps its
    // own state below (index 0 or 1) and its own flag bits (1/2 playing, 0x10/0x20 animating)
    enum VF_TYPE {};
    // the message playRimBloom sends the effect caster (id 0x1000056; BattleCharacter::SetOneShotRimBloom sends the
    // same one). No symbol names it: the names are not the original's
    struct RimBloomMessage : fw::Message {
        RimBloomMessage() : fw::Message(0x1000056, 0x80) {
            m_flag = false;
            m_on = true;
        }
        int m_type;  // playRimBloom's type
        bool m_on;
        bool m_flag;
    };
    void playVolumeFade(VF_TYPE type, int id, const mm::Vec3& color0, const mm::Vec3& color1, float value0,
                        float value1, int index, float ratio);
    // the ratio curve from the current ratio to ratio over frame frames
    void playVolumeFadeAnim(VF_TYPE type, float ratio, float frame);
    void updateVolumeFadeAnim(VF_TYPE type, float step);
    void stopVolumeFade(VF_TYPE type);
    void playRimBloom(int type);
    void stopRimBloom();
    void playAfterImage(int src, int dst, float param0, float param1, float param2);
    void stopAfterImage();

    // bits 0/1: a volume fade on (kind 0/1); bit 2: a rim bloom on; bit 3: an after image is on (stopAfterImage
    // releases it); bits 4/5: a volume fade curve playing (kind 0/1); the name is not the original's
    unsigned int m_flags;  // 0x8
    gf::GF_OBJ_HANDLE* m_handle;  // 0x10, -1 when none; the name is not the original's
    // playVolumeFade's arguments per kind (what fw::EffectManager::getVolumeFadeParam's parameters are overridden
    // with); the names are not the original's
    int m_fadeIds[2];  // 0x18
    mm::Vec3 m_fadeColors0[2];  // 0x20
    mm::Vec3 m_fadeColors1[2];  // 0x40
    float m_fadeValues0[2];  // 0x60
    float m_fadeValues1[2];  // 0x68
    int m_fadeIndices[2];  // 0x70
    float m_fadeRatios[2];  // 0x78
    // the ratio curves playVolumeFadeAnim plays, one per kind; the names are not the original's
    AnmF32 m_anm[2];  // 0x80
    int m_rimBloom;  // 0x2a0 playRimBloom's type; the name is not the original's
    // playAfterImage's arguments; the names are not the original's
    int m_afterImageSrc;  // 0x2a4
    int m_afterImageDst;  // 0x2a8
    float m_afterImageParams[3];  // 0x2ac
};
}  // namespace event

#endif
