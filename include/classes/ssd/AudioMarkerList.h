#ifndef CLASSES_SSD_AUDIOMARKERLIST_H
#define CLASSES_SSD_AUDIOMARKERLIST_H

#include "classes/ssd/AudioMarker.h"
#include "classes/ssd/List.h"

namespace ssd {
// table 0x7100B82260 (its slot 0 holds List<AudioMarker>'s destructor: the class's own is inline)
class AudioMarkerList : public ::ssd::List< ::ssd::AudioMarker> {
public:
    virtual ~AudioMarkerList() {}  // slot 0
};
}  // namespace ssd

#endif
