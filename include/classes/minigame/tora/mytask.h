#ifndef CLASSES_MINIGAME_TORA_MYTASK_H
#define CLASSES_MINIGAME_TORA_MYTASK_H

namespace minigame { namespace tora {

// one task of the minigame (200 bytes each in mytask's pool, minigame::initialize): a doubly linked node with its
// move and draw callbacks (mytask::executeMove/executeDraw call them with the node). The kinds (player, enemy, item,
// effect) keep their own work from 0x40 on. Field names are not the original's.
// a task's hit box (8 bytes; check_map, check_dmg_map_obj, check_atk_obj). Names are not the
// original's.
struct _sHit {
    unsigned char m_kind;  // 0x0: the kinds it hits (anded with the other's)
    unsigned char m_hit;   // 0x1: set when hit (0: can be hit)
    short m_x;             // 0x2: pixels from the task's position
    short m_y;             // 0x4
    unsigned char m_w;     // 0x6: pixels
    unsigned char m_h;     // 0x7
};

struct _sTask {
    _sTask* m_next;               // 0x00
    _sTask* m_prev;               // 0x08
    void (*m_move)(void* task);   // 0x10
    void (*m_draw)(void* task);   // 0x18
    const char* m_name;           // 0x20: the kind's name ("item", enemy_damage)
    unsigned char m_attr;         // 0x28: bit 0 flips the sprite horizontally, bit 1 vertically (draw_obj)
    unsigned char pad_29[0x3];
    int m_x;                      // 0x2C: 24.8 fixed point
    int m_y;                      // 0x30: 24.8 fixed point
    _sHit m_hit;                  // 0x34
    unsigned char pad_3C[0x4];
};

// the minigame's task pool (minigame::m_task; 0x30 bytes, built with (200, 0x100)): m_count nodes of m_size bytes in
// one block, a free list and the live list. Field names are not the original's.
class mytask {
public:
    mytask(int size, int count);
    ~mytask();
    void reset();
    void* entry();
    void remove(void* task);
    void executeMove();
    void executeDraw();
    void* enum_next(void* task);

    void* m_buf;       // 0x00
    int m_size;        // 0x08
    int m_count;       // 0x0C
    _sTask* m_free;    // 0x10
    _sTask* m_head;    // 0x18
    _sTask* m_tail;    // 0x20
    _sTask* m_cur;     // 0x28: the node after the one executeMove/executeDraw runs (remove steps it on)
};

}}  // namespace minigame::tora

#endif
