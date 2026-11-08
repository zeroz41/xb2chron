#ifndef CLASSES_EVENT_CHARAWEIGHTPLAYER_H
#define CLASSES_EVENT_CHARAWEIGHTPLAYER_H

#include "event/CvType.h"
#include "mm/mtl/FixedVector.h"

namespace gf { enum AnimLayer : unsigned int; }

namespace gf { class GF_OBJ_HANDLE; }
namespace event { class CharaWeightItem; }

namespace event {
// which weight layer a CharaWeightPlayer ease plays on (1.0.0's mangled names spell event::WeightLayer); its values
// are not known
enum WeightLayer {};

// table 0x7100B3CA78
class CharaWeightPlayer {
public:
    virtual ~CharaWeightPlayer();  // slot 0
    void easeIn(gf::AnimLayer, const char*, float, float, float, CV_TYPE, WeightLayer);  // 0x71000D37EC
    // 0x71000D36C8: eases the named item's curve on layer down to 0 over the time (the AnimLayer is not used)
    void easeOut(gf::AnimLayer, const char*, float, CV_TYPE, WeightLayer);
    // 0x71000D3F78: eases every item's motion out and deletes the items
    void destroy();
    gf::GF_OBJ_HANDLE* m_handle;  // 0x8: easeIn's object (the field names are not the original's)
    unsigned long pad_10;  // destroy zeroes it
    // the items the eases look up by name (easeIn pushes new ones)
    mm::mtl::FixedVector<CharaWeightItem*, 12> m_items;  // 0x18, count at 0x78
};
}  // namespace event

#endif
