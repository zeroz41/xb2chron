#ifndef CLASSES_SSD_AUDIOMARKER_H
#define CLASSES_SSD_AUDIOMARKER_H

#include "classes/ssd/List.h"

namespace ssd {
// table 0x7100B82450: a node of an AudioMarkerList (its slot 0 holds List<AudioMarker>::Node's destructor, so
// its own destructor is inline; AudioFileBase's destructor deletes the markers in instance blocks of 0x248 bytes)
class AudioMarker : public ::ssd::List< ::ssd::AudioMarker>::Node {
public:
    // the marker's ID (AudioMarkerList::GetMarkerDataByID compares it as 16 bits, as an AIFF MARK entry's id;
    // the name is inferred)
    unsigned short id_;
    unsigned char pad_1A[0x22E];
};
}  // namespace ssd

#endif
