#ifndef CLASSES_EVENT_SEOBJ_H
#define CLASSES_EVENT_SEOBJ_H

#include "event/CvType.h"

namespace event {
// table 0x7100B3D408
class SeObj {
public:
    virtual ~SeObj();  // slot 0
    void changeVolume(float volume, float frame);  // 0x71000FE29C
    void pan(float pan, float frame, CV_TYPE type);  // 0x71000FE480

    // bit 0: in use (SeManager::changeVolume/pan forward only then); the name is not the original's
    unsigned int m_flags;  // 0x8
    unsigned char pad_c[0x298 - 0xC];  // SeManager keeps them 0x298 bytes apart
};
}  // namespace event

#endif
