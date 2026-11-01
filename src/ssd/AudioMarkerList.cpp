#include "classes/ssd/AudioMarkerList.h"

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

}  // namespace ssd
