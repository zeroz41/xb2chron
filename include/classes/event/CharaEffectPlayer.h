#ifndef CLASSES_EVENT_CHARAEFFECTPLAYER_H
#define CLASSES_EVENT_CHARAEFFECTPLAYER_H

namespace event {
// table 0x7100B3CA98
class CharaEffectPlayer {
public:
    virtual ~CharaEffectPlayer();  // slot 0
    // the volume fade's kind (the evt_chara script commands pass 1); no enumerator is named
    enum VF_TYPE : int {};
};
}  // namespace event

#endif
