#ifndef CLASSES_SSD_AUDIOMARKERLIST_H
#define CLASSES_SSD_AUDIOMARKERLIST_H

#include "classes/ssd/List.h"

namespace ssd { class AudioMarker; }

namespace ssd {
// table 0x7100B82260
class AudioMarkerList : public ::ssd::List< ::ssd::AudioMarker> {
public:
    virtual ~AudioMarkerList();  // slot 0
};
}  // namespace ssd

#endif
