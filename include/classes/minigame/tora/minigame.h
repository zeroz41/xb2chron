#ifndef CLASSES_MINIGAME_TORA_MINIGAME_H
#define CLASSES_MINIGAME_TORA_MINIGAME_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace minigame { namespace tora { class minigame; }}
namespace minigame { namespace tora { struct _sTask; }}
namespace minigame { namespace tora { class mytask; }}

namespace minigame { namespace tora {
// table 0x7100B72080
// The minigame (the "TT" bdat sheets MIN_TT_PC/MIN_TT_Enemy/MIN_TT_Tbox; the unit is minigame_tora.cpp): a small
// sprite game drawn into m_screen. Field and helper type names are not the original's.
class minigame : public ::mm::mtl::PtrSingleton< ::minigame::tora::minigame> {
public:
    // one sprite piece of a sprite set (8 bytes)
    struct SprtCell {
        unsigned char m_attr;   // 0x0: flip bits, xored with the task's
        unsigned char pad_1;
        unsigned short m_tile;  // 0x2: first tile, from the set's m_tileBase
        unsigned char m_w;      // 0x4: pixels
        unsigned char m_h;      // 0x5: pixels
        signed char m_ox;       // 0x6
        signed char m_oy;       // 0x7
    };
    // a sprite set (0x18 bytes; draw_obj's first argument picks one)
    struct SprtSet {
        int m_tileBase;           // 0x00
        unsigned char pad_4[0x4];
        const SprtCell* m_cells;  // 0x08: none, nothing is drawn
        unsigned char pad_10[0x8];
    };
    // one sprite queued for the frame (16 bytes)
    struct Oam {
        unsigned char m_attr;   // 0x0: flip bits
        unsigned char m_prio;   // 0x1
        unsigned char pad_2[0x2];
        short m_x;              // 0x4
        short m_y;              // 0x6
        short m_tile;           // 0x8
        unsigned char m_w;      // 0xA: tiles
        unsigned char m_h;      // 0xB: tiles
        unsigned char pad_C[0x4];
    };
    // the work block initialize allocates (0x4BD00 bytes, 0x40 aligned)
    struct Screen {
        unsigned char pad_0[0x1C];
        short m_ofsX;           // 0x1C: added to every sprite's position
        short m_ofsY;           // 0x1E
        unsigned char pad_20[0x210E0];
        Oam m_oam[64];          // 0x21100: m_oamNum used
        unsigned char pad_21500[0x2A800];
    };

    // the pad as the game reads it (update_pad)
    union PadBits {
        unsigned int m_all;
        struct {
            unsigned int m_btn : 24;  // the pad's buttons (16 bits used)
            unsigned int m_up : 1;    // 24..27: the stick's direction (update_pad's table)
            unsigned int m_right : 1;
            unsigned int m_down : 1;
            unsigned int m_left : 1;
            unsigned int pad_28 : 4;
        };
    };

    virtual ~minigame();  // slot 0

    void update_pad();
    void draw_obj(int sprt, int cell, const _sTask* task, unsigned char prio);

    unsigned char pad_8[0x8];
    PadBits m_padHold;        // 0x10: the buttons and stick directions held
    PadBits m_padTrig;        // 0x14: those pressed this frame
    Screen* m_screen;         // 0x18
    unsigned char pad_20[0x10];
    SprtSet m_sprt[65];       // 0x30
    unsigned char pad_648[0x2F10];
    int m_scrollSpd;          // 0x3558: 24.8 fixed point; effects drift down by it
    unsigned char pad_355C[0xB54];
    unsigned char m_oamNum;   // 0x40B0: sprites queued in m_screen->m_oam
    unsigned char pad_40B1[0x7];
    mytask* m_task;           // 0x40B8
};

void effect_move(void* task);
void effect_draw(void* task);
void enemy_draw(void* task);
}}  // namespace minigame::tora

#endif
