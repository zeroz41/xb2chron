#ifndef CLASSES_ML_EVENTVIEW_H
#define CLASSES_ML_EVENTVIEW_H

#include "mm/Pnt.h"

namespace ml {
// what a view passes its work events (ml::IWorkEvent's slots): the pointer position first (BouManager's mouse
// slots pass the event itself as the mm::Pnt<int> updateActive takes). No table (the position is at 0x0).
class EventView {
public:
    mm::Pnt<int> m_pos;  // 0x0 (the name is not the original's)
    unsigned char pad_8[0x1c];
    // bit 0 tested by BouManager::OnMouseButtonDown before it starts a drag: presumably the left button (the name is
    // not the original's)
    unsigned char m_buttons;  // 0x24
    unsigned char pad_25[3];
    // bit 0 tested by CamFree::OnKeyUp before it stops the camera's key move (a key state)
    unsigned char pad_28;
};
}  // namespace ml

#endif
