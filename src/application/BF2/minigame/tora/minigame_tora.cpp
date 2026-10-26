#include "classes/minigame/tora/minigame.h"
#include "classes/minigame/tora/mytask.h"
#include "classes/fw/PadManager.h"
#include "classes/gf/GfGamePad.h"
#include <math.h>

namespace minigame {
namespace tora {

namespace {
// an effect task's work (effect_move/effect_draw). The names are not the original's.
struct _sEffect : _sTask {
    unsigned char m_wait;   // 0x40: not 0, the effect neither moves nor draws
    unsigned char m_frame;  // 0x41
    unsigned char m_life;   // 0x42: frames left (0: until it leaves the top)
    unsigned char pad_43;
    int m_vx;               // 0x44: 24.8 fixed point, plus a sine sway
    int m_vy;               // 0x48: 24.8 fixed point
};

// an enemy task's work (enemy_move/enemy_draw). The names are not the original's.
struct _sEnemy : _sTask {
    unsigned char pad_40[0x2];
    unsigned char m_flags;  // 0x42: bit 2 the animation frame, bit 5 faces left (kind 0x3E)
    unsigned char pad_43[0x2];
    unsigned char m_hide;   // 0x45: bit 0 hides it
    unsigned char pad_46[0x2B];
    unsigned char m_sprt;   // 0x71: its sprite set
    unsigned char pad_72[0x6];
    unsigned char m_step;   // 0x78: kind 0x3D's animation step
};
}  // namespace

// Proposed name, not the original's: the symbols leave it unnamed (lbl_71009C6A3C).
// update_pad's stick octant (bit 0 left, bit 1 down, bit 2 more horizontal, +8 off the axis) to direction bits.
static const unsigned char s_stickDirTbl[16] = {1, 1, 4, 4, 2, 8, 2, 8, 3, 9, 6, 12, 3, 9, 6, 12};
// Proposed name, not the original's: the symbols leave it unnamed (lbl_71009C6E06).
// enemy_draw: sprite cell of sprite set 0x3D per animation step.
static const unsigned char s_enemy3DCellTbl[6] = {0, 0, 0, 1, 2, 0};

void minigame::update_pad() {
    PadBits prev = m_padHold;
    PadBits hold;
    hold.m_all = (unsigned short)gf::GfGamePad::getPadPlayer()->m_btn;
    float lx = gf::GfGamePad::getPadPlayer()->m_lx;
    float ly = gf::GfGamePad::getPadPlayer()->m_ly;
    if (fabsf(lx * lx + ly * ly) > fw::PadManager::ANALOG_TRIGGER_THRESHOLD) {
        float ax = fabsf(lx);
        float ay = fabsf(ly);
        unsigned char oct = lx < 0.0f;
        if (ly < 0.0f) oct |= 2;
        float r;
        if (ax > ay) {
            oct |= 4;
            r = ay / ax;
        } else {
            r = ax / ay;
        }
        if (r > 0.41421357f) oct += 8;
        unsigned char dir = s_stickDirTbl[oct];
        hold.m_up = dir & 1;
        hold.m_right = (dir >> 1) & 1;
        hold.m_down = (dir >> 2) & 1;
        hold.m_left = (dir >> 3) & 1;
    }
    m_padHold = hold;
    m_padTrig.m_all = hold.m_all & ~prev.m_all;
}

void effect_move(void* task) {
    _sEffect* t = static_cast<_sEffect*>(task);
    if (t->m_wait != 0) return;
    t->m_frame++;
    t->m_x += t->m_vx + (int)(sinf(t->m_frame * 0.2f) * 256.0f);
    minigame* m = minigame::get();
    t->m_y += t->m_vy - m->m_scrollSpd / 256;
    if (t->m_y < 0 || (t->m_life != 0 && --t->m_life == 0)) {
        m->m_task->remove(t);
    }
}

void effect_draw(void* task) {
    _sEffect* t = static_cast<_sEffect*>(task);
    if (t->m_wait != 0) return;
    minigame::get()->draw_obj(0x32, 0, t, 0x80);
}

void enemy_draw(void* task) {
    _sEnemy* t = static_cast<_sEnemy*>(task);
    if (t->m_hide & 1) return;
    switch (t->m_sprt) {
    case 0x34:
    case 0x35:
    case 0x36:
    case 0x37:
    case 0x39:
    case 0x3A:
    case 0x3B:
    case 0x3C:
    case 0x3F:
        minigame::get()->draw_obj(t->m_sprt, (t->m_flags >> 2) & 1, t, 0x50);
        break;
    case 0x3D:
        minigame::get()->draw_obj(0x3D, s_enemy3DCellTbl[t->m_step], t, 0x50);
        break;
    case 0x3E:
        t->m_attr = (t->m_flags >> 5) & 1;
        minigame::get()->draw_obj(0x3E, 0, t, 0x40);
        break;
    case 0x40:
        break;
    default:
        minigame::get()->draw_obj(t->m_sprt, 0, t, 0x50);
        break;
    }
}

}  // namespace tora
}  // namespace minigame
