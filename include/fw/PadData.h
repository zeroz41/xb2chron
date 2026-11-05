#ifndef FW_PADDATA_H
#define FW_PADDATA_H

namespace fw {

// one pad's state for a frame (no table): fw::PadManager::makePadData fills it from ml::DevPad (its buttons, the
// ones pressed and released this frame, the double presses, then the sticks' axes as its pad maps them; 0x48
// bytes apart in the manager). The names are not the original's.
struct PadData {
    // what a holder that is not a pad's own starts with (GfGamePad's constructor, as 1.0.0's): no pad, no buttons,
    // the sticks centred, the four 0.2f m_nullPad holds (inline: no copy in the symbols; the assignment order is the
    // one whose stores match GfGamePad::build)
    PadData() {
        m_style = 0;
        m_isConnect = false;
        m_padNo = -1;
        m_btn = 0;
        m_down = 0;
        m_up = 0;
        m_repeat = 0;
        m_dbl = 0;
        pad_14 = 0;
        pad_18 = 0;
        m_lx = 0.0f;
        m_ly = 0.0f;
        m_rx = 0.0f;
        m_ry = 0.0f;
        pad_2C[0] = 0.2f;
        pad_2C[1] = 0.2f;
        pad_2C[2] = 0.2f;
        pad_2C[3] = 0.2f;
    }

    // back to what the constructor makes, in place (fw::PadManager::update clears a pad it does not read so: its
    // stores come in this order, with no temporary; inline, the name is not the original's)
    void clear() {
        m_btn = 0;
        m_down = 0;
        m_up = 0;
        m_repeat = 0;
        m_dbl = 0;
        pad_14 = 0;
        pad_18 = 0;
        m_lx = 0.0f;
        m_ly = 0.0f;
        m_rx = 0.0f;
        m_ry = 0.0f;
        m_style = 0;
        m_isConnect = false;
        m_padNo = -1;
        pad_2C[0] = 0.2f;
        pad_2C[1] = 0.2f;
        pad_2C[2] = 0.2f;
        pad_2C[3] = 0.2f;
    }

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
    // four 0.2f in fw::PadManager::m_nullPad; makePadData copies them from the raw pad
    float pad_2C[4];
    // the ml::DevPad pad number the data comes from (-1: none): fw::PadManager::playVibration and finalize hand
    // the first control pad's to ml::DevPad::playVibration/stopVibration. The name is not the original's.
    int m_padNo;
    // set while that pad is connected (playVibration and finalize skip a pad without it; updateControlPadNo picks
    // only pads with it). The name is not the original's.
    bool m_isConnect;
    unsigned char pad_41[0x3];
    // the pad's style (updateControlPadNo picks a pad whose style is 1 or 2). The name is not the original's.
    int m_style;
};

}  // namespace fw

#endif
