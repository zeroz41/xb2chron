#include "classes/ssd/AudioMarkerList.h"
#include "classes/ssd/ExtendedFloat.h"

namespace ssd {

AudioMarker* AudioMarkerList::GetMarkerDataByID(int id) {
    Node* node = head_.next;
    while (node != &head_) {
        if (static_cast<AudioMarker*>(node)->id_ == id) {
            break;
        }
        node = node->next;
    }
    if (node == &head_) {
        return nullptr;
    }
    return static_cast<AudioMarker*>(node);
}


double ExtendedFloat::FP80toFP64() {
    union {
        double value;
        unsigned char bytes[8];
    } result;
    result.value = 0.0;

    // the 15-bit exponent, rebiased from 16383 to 1023; one lower when the explicit integer bit is clear
    int biased = (bytes_[0] << 8 | bytes_[1]) & 0x7fff;
    int bias = 1023 - 16383;
    if (!(bytes_[2] & 0x80)) {
        bias--;
    }
    int exponent = bias + biased;
    result.bytes[7] = (bytes_[0] & 0x80) | (exponent >> 4);
    result.bytes[6] = exponent << 4;
    // the fraction starts after the integer bit (bit 16), one later when that bit is clear
    int start = (bytes_[2] & 0x80) ? 17 : 18;
    int i = 0;
    do {
        int src = start + i;
        int dst = 12 + i;
        result.bytes[7 - dst / 8] |= ((bytes_[src / 8] >> (7 - (src & 7))) & 1) << (7 - (dst & 7));
    } while (++i < 52);
    return result.value;
}

}  // namespace ssd
