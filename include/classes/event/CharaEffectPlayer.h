#ifndef CLASSES_EVENT_CHARAEFFECTPLAYER_H
#define CLASSES_EVENT_CHARAEFFECTPLAYER_H

namespace mm { class Vec3; }

namespace event {
// table 0x7100B3CA98
class CharaEffectPlayer {
public:
    virtual ~CharaEffectPlayer();  // slot 0
    // the volume fade's kind (the evt_chara script commands pass 1); no enumerator is named
    enum VF_TYPE : int {};
    void playVolumeFade(VF_TYPE type, int a, const mm::Vec3& b, const mm::Vec3& c, float d, float e, int f, float g);
    void playVolumeFadeAnim(VF_TYPE type, float time, float delay);
    void stopVolumeFade(VF_TYPE type);
    void playRimBloom(int type);
    void stopRimBloom();
};
}  // namespace event

#endif
