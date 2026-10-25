#ifndef CLASSES_EVENT_CHARAOBJ_H
#define CLASSES_EVENT_CHARAOBJ_H

#include "classes/event/CharaEffectPlayer.h"

namespace mm { class Vec3; }
namespace event { class AttachActorBase; }

namespace event {
// which weapon a hide request is for (the evt_chara script commands pass 3); no enumerator is named
enum WPNHIDEID : int {};
// table 0x7100B3CAF8
class CharaObj {
public:
    virtual ~CharaObj();  // slot 0
    void playMotion(const char* name, float a, float b, float c);
    void playFade(bool fade, float time);
    void playWink(int a, float b, bool c, float d, float e, int f, bool g, bool h);
    void playTalk(bool a, float b, bool c, bool d, float e, float f, float g, float h);
    void playVolumeFadeAnim(CharaEffectPlayer::VF_TYPE type, float time, float delay);
    void playVolumeFade(CharaEffectPlayer::VF_TYPE type, int a, const mm::Vec3& b, const mm::Vec3& c, float d, float e,
                        int f, float g);
    void stopVolumeFade(CharaEffectPlayer::VF_TYPE type);
    void resetDynamics(int type);
    void playRimBloom(int type);
    void stopRimBloom();
    void setExtDisp(const char* name, bool disp);
    void setExtParam(const char* name, float value);
    void setHideWeapon(WPNHIDEID id, bool hide, bool flag);

    unsigned char pad_8[0xc98];
    // bit 5: playFade's flag (it sets or clears it); the name is not the original's
    unsigned int m_flags;  // 0xca0
    unsigned char pad_ca4[0xb4];
    // initModel stores a new AttachActorGf here (the destructor deletes it); the name is not the original's
    AttachActorBase* m_attach;  // 0xd58
};
}  // namespace event

#endif
