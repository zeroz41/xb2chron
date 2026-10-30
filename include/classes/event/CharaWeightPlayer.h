#ifndef CLASSES_EVENT_CHARAWEIGHTPLAYER_H
#define CLASSES_EVENT_CHARAWEIGHTPLAYER_H

#include "event/CvType.h"

namespace gf { enum AnimLayer : unsigned int; }

namespace event {
// which weight layer a CharaWeightPlayer ease plays on (1.0.0's mangled names spell event::WeightLayer); its values
// are not known
enum WeightLayer {};

// table 0x7100B3CA78
class CharaWeightPlayer {
public:
    virtual ~CharaWeightPlayer();  // slot 0
    void easeIn(gf::AnimLayer, const char*, float, float, float, CV_TYPE, WeightLayer);  // 0x71000D37EC
};
}  // namespace event

#endif
