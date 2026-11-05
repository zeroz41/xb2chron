#include "classes/minigame/tora/minigame.h"
#include "classes/minigame/tora/mytask.h"
#include "classes/fw/PadManager.h"
#include "classes/gf/GfGamePad.h"
#include "classes/fw/SoundManager.h"
#include "classes/gf/GfDataManager.h"
#include "classes/gf/GfAllocator.h"
#include "csvb/CsvbData.h"
#include <string.h>
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
    unsigned char pad_40;
    unsigned char m_type;   // 0x41: its type (minigame::SaveData::m_kills index)
    unsigned char m_flags;  // 0x42: bit 2 the animation frame, bit 5 faces left (kind 0x3E)
    unsigned char pad_43[0x2];
    unsigned char m_damage;      // 0x45: damage blink frames left (bit 0 hides it)
    unsigned char m_damageKind;  // 0x46: what hit it last (enemy_damage's argument)
    unsigned char pad_47;
    int m_vx;               // 0x48: 24.8 fixed point; an item it drops gets it
    int m_vy;               // 0x4C
    unsigned char pad_50[0x18];
    unsigned char m_hp;          // 0x68: at most 1, a hit beats it
    unsigned char m_damageTime;  // 0x69: blink frames per hit
    unsigned char pad_6A[0x2];
    unsigned short m_score;      // 0x6C: its points
    unsigned char pad_6E[0x3];
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

void minigame::finalize() {
    fw::SoundManager::sys()->stopBgmAll();
    fw::SoundManager::sys()->stopSeAll();
    gf::SDataGame* game = gf::GfDataManager::getDataGame();
    memset(game->m_toraSave, 0, 0x100);
    memcpy(game->m_toraSave, &m_save, sizeof(m_save));
    if (m_task != nullptr) {
        delete m_task;
        m_task = nullptr;
    }
    if (m_screen != nullptr) {
        gf::getAllocator(gf::ALLOCATOR(0))->deallocate(m_screen);
        m_screen = nullptr;
    }
}

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

void minigame::getResult(_sResult* result) {
    unsigned int best = 0;
    for (int i = 0; i < 5; i++) {
        if (best < m_save.m_rank[i].m_score) best = m_save.m_rank[i].m_score;
    }
    ResultItem* item = result->m_items;
    result->m_score = best;
    if (m_resultFlag != 0) {
        item->m_id = 0xFFFE;
        item->m_num = m_resultSub | 0x100;
        item++;
    }
    if (m_resultNum != 0) {
        item->m_id = 0xFFFF;
        item->m_num = m_resultNum;
        item++;
    }
    for (int i = 0; i < 0x80; i++) {
        if (m_resultItems[i].m_num != 0) {
            item->m_id = m_resultItems[i].m_id;
            item->m_num = m_resultItems[i].m_num;
            item++;
        }
    }
    item->m_id = 0;
    item->m_num = 0;
}

void minigame::tora_cell_anime_setup(int no) {
    const unsigned char* anime = reinterpret_cast<const unsigned char*>(m_res) + ((m_res[0] + 0x10) & ~0xFu);
    if (no + 8 > 0) anime += m_res[no + 8];
    m_cellAnime.m_data = anime;
    m_cellAnime.m_frame = 0;
    m_cellAnime.m_wait = 1;
    csvb::CCsvbData csv;
    gf::GfAllocator* allocator = gf::getAllocator(gf::ALLOCATOR(0));
    const unsigned char* data = reinterpret_cast<const unsigned char*>(m_res) + ((m_res[0] + 0x10) & ~0xFu);
    csv.Load(allocator, data + m_res[7], m_res[8] - m_res[7]);
    m_cellAnime.m_frameWait[0] = csv.GetInt(no, 0);
    m_cellAnime.m_frameWait[1] = csv.GetInt(no, 1);
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

void minigame::draw_obj(int sprt, int cell, const _sTask* task, unsigned char prio) {
    const SprtCell* cells = m_sprt[sprt].m_cells;
    if (cells == nullptr) return;
    const SprtCell& c = cells[cell];
    int x = task->m_x >> 8;
    int y = task->m_y >> 8;
    if (task->m_attr & 1) {
        x = x - (c.m_ox + c.m_w);
    } else {
        x = c.m_ox + x;
    }
    if (task->m_attr & 2) {
        y = y - (c.m_oy + c.m_h);
    } else {
        y = c.m_oy + y;
    }
    if (y >= -c.m_h && y <= 240) {
        if (m_oamNum < sizeof(m_screen->m_oam) / sizeof(m_screen->m_oam[0])) {
            Oam& o = m_screen->m_oam[m_oamNum];
            m_oamNum++;
            o.m_attr = (c.m_attr ^ task->m_attr) & 3;
            o.m_prio = prio;
            o.m_x = m_screen->m_ofsX + x;
            o.m_y = m_screen->m_ofsY + y;
            o.m_tile = c.m_tile + m_sprt[sprt].m_tileBase;
            o.m_w = c.m_w >> 3;
            o.m_h = c.m_h >> 3;
        }
    }
}

void effect_draw(void* task) {
    _sEffect* t = static_cast<_sEffect*>(task);
    if (t->m_wait != 0) return;
    minigame::get()->draw_obj(0x32, 0, t, 0x80);
}

void enemy_draw(void* task) {
    _sEnemy* t = static_cast<_sEnemy*>(task);
    if (t->m_damage & 1) return;
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
