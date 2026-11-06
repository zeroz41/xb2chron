#ifndef CLASSES_ML_EVENTVIEW_H
#define CLASSES_ML_EVENTVIEW_H

#include "mm/Pnt.h"

namespace ml {
// what a view passes its work events (ml::IWorkEvent's slots): the pointer position first (BouManager's mouse
// slots pass the event itself as the mm::Pnt<int> updateActive takes). No table (the position is at 0x0).
class EventView {
public:
    mm::Pnt<int> m_pos;  // 0x0 (the name is not the original's)
    // 8-aligned: the original reads the words at 0x28 and 0x2c as one 64-bit load (CamFree::OnKeyDown)
    unsigned long pad_8;
    // 0x10: the pointer's move since the last event (CamFree::OnMouseMove passes it to ctrlTumble/ctrlDolly)
    mm::Pnt<int> pad_10;
    unsigned char pad_18[0xc];
    // bit 0 tested by BouManager::OnMouseButtonDown before it starts a drag: presumably the left button (the name is
    // not the original's); CamFree's mouse slots test bits 0-2 (ldr w: a 32-bit word)
    unsigned int m_buttons;  // 0x24
    // bit 0 tested by CamFree::OnKeyUp before it stops the camera's key move (a key state; ldr w in
    // CamFree::OnMouseButtonDown)
    unsigned int pad_28;
    // bit 0: a key went down (CamFree::OnKeyDown acts on its key code only then)
    unsigned int pad_2c;  // 0x2c
    unsigned char pad_30[3];
    // 0x33: the key code CamFree::OnKeyDown switches on (0x25-0x28: the arrow keys' virtual-key codes)
    unsigned char pad_33;
};
}  // namespace ml

#endif
