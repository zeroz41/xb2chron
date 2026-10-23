#ifndef FW_PADDATA_H
#define FW_PADDATA_H

namespace fw {

// one pad's state for a frame (no table): fw::PadManager::makePadData fills it from ml::DevPad (its buttons, the
// ones pressed and released this frame, the double presses, then the sticks' axes as its pad maps them; 0x48
// bytes apart in the manager). The names are not the original's.
struct PadData {
    unsigned int m_btn;     // ml::DevPad::getBtn: held
    unsigned int m_down;    // ml::DevPad::getDown: pressed this frame
    unsigned int m_up;      // ml::DevPad::getUp: released this frame
    unsigned int m_repeat;  // held long enough to repeat (ui::UIInputPad moves its selection by it as by m_down)
    unsigned int m_dbl;     // ml::DevPad::getDbl
    unsigned int pad_14;  // fw::PadRelay::checkAction tests a key's bit in it for an action of kind 7
    unsigned int pad_18;  // fw::PadRelay::checkAction tests a key's bit in it for an action of kind 6
    float m_lx;  // from ml::DevPad::getALX/getALY: ui::UIInputWheel turns with them
    float m_ly;
    float m_rx;  // from ml::DevPad::getARX/getARY: ui::UIInputPointer moves with them
    float m_ry;
    unsigned char pad_2C[0x1C];
};

}  // namespace fw

#endif
