#ifndef CLASSES_MINIGAME_TORA_MINIGAME_H
#define CLASSES_MINIGAME_TORA_MINIGAME_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace minigame { namespace tora { class minigame; }}
namespace minigame { namespace tora { struct _sTask; }}
namespace minigame { namespace tora { class mytask; }}
namespace fw { class SoundResource; }

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
        unsigned char pad_20[0x6];
        short m_scrollY;        // 0x26: pixels; check_map's map row is m_scrollY / 16
        unsigned char pad_28[0xD8];
        // 0x100: the character tiles, 32 bytes (8 rows of 8 4bpp pixels) each (decode_4bpp_sprt's first argument
        // picks the first; tora_cell_anime rewrites 0x40 from 0x140)
        unsigned int m_chr[0x1080][8];
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

    // the map check_map reads: a 0x10-byte head, then rows of 16 cells (a negative cell is solid)
    struct MapData {
        unsigned char m_head[0x10];
        signed char m_rows[1][16];  // 0x10
    };
    // an id and its count, as getResult reports them
    struct ResultItem {
        unsigned short m_id;
        unsigned short m_num;
    };
    // what getResult fills: the best score, then id/count pairs ended by a zero pair
    struct _sResult {
        unsigned int m_score;
        ResultItem m_items[0x100];  // MinigameUpdatableObject::update's copy is 0x404 bytes
    };
    // one ranking row (8 bytes)
    struct RankEntry {
        unsigned int m_score : 31;
        unsigned int m_flag : 1;
        unsigned char pad_4[0x4];
    };
    // the tile animation tora_cell_anime_setup picks and tora_cell_anime plays 
    struct CellAnime {
        const unsigned char* m_data;  // 0x0: two 0x800-byte frames of 0x40 tiles from 0x40
        unsigned char m_frame;        // 0x8: the frame shown (0/1)
        unsigned char m_wait;         // 0x9: frames until the next flip
        unsigned char m_frameWait[2]; // 0xA: each frame's wait (the csvb row's columns 0/1)
    };  // 0x10 bytes
    // a 4bpp sprite file's head (decode_4bpp_sprt)
    struct SprtData {
        unsigned char pad_0[0x2];
        unsigned short m_palSize;  // 0x2: palette bytes at m_data (none: the file has no palette)
        unsigned short m_width;    // 0x4: pixels per row (0: m_count whole tiles)
        unsigned short m_count;    // 0x6: rows (or tiles)
        unsigned char pad_8[0x8];
        unsigned char m_data[1];   // 0x10: the palette, then the pixels
    };
    // a treasure box (0x2A bytes; choice_tbox, item_move, item_draw). The names are not the original's.
    struct TBox {
        unsigned char m_type;  // 0x0: item_draw's sprite cell; item_move: 2 gives m_items[0].m_id as points
        unsigned char pad_1;
        struct {
            unsigned short m_id;    // what the box may hold (0: nothing)
            unsigned short m_cond;  // a game condition it needs (0: none; choice_tbox)
        } m_items[10];  // 0x2
    };
    // the totals of SaveData (0xA0 bytes)
    struct Record {
        unsigned long long m_score;  // 0x00: enemy_damage adds the points
        unsigned char pad_8[0x14];
        unsigned int m_kills[0x21];  // 0x1C: enemies beaten per enemy type (enemy_damage)
    };
    // the block finalize saves into the game data (0xD0 bytes)
    struct SaveData {
        unsigned char pad_0[0x8];
        RankEntry m_rank[5];        // 0x08: getResult takes the best
        Record m_record;            // 0x30
    };

    // inline: 3.0.1 has no out-of-line copy (MinigameUpdatableObject::myinit holds its stores)
    minigame() : m_screen(nullptr), m_res(nullptr), m_task(nullptr) {}
    virtual ~minigame();  // slot 0

    void initialize();
    // a frame: draws into buffer (pitch bytes a row, height rows) from the resource's asset data
    void update(unsigned char* buffer, int pitch, int height, void* asset, void* sound);

    void finalize();
    void getResult(_sResult* result);
    unsigned char check_map(_sTask* task);
    void tora_cell_anime_setup(int no);
    void tora_cell_anime();
    void enemy_damage(_sTask* task, int kind);
    unsigned int decode_4bpp_sprt(unsigned int no, const unsigned char* data);

    void update_pad();
    void draw_obj(int sprt, int cell, const _sTask* task, unsigned char prio);

    unsigned char pad_8[0x4];
    unsigned int m_rand;      // 0xC: the random seed (x * 0x41C64E6D + 12345, enemy_damage)
    PadBits m_padHold;        // 0x10: the buttons and stick directions held
    PadBits m_padTrig;        // 0x14: those pressed this frame
    Screen* m_screen;         // 0x18
    // 0x20: the game's resource file: [0] the header size (the data starts 16-aligned after it), [7]/[8] the csvb
    // table's start/end offsets in the data, [8 + n] cell animation n's (tora_cell_anime_setup)
    unsigned int* m_res;
    fw::SoundResource* m_sound;  // 0x28: none, no sound effects
    SprtSet m_sprt[65];       // 0x30
    unsigned char pad_648[0x4];
    // 0x64C: the game's phase; past 10 the game is over (MinigameUpdatableObject::update then takes the result)
    unsigned int m_phase;
    unsigned char pad_650[0xC];
    unsigned char m_pal[16][0x30];  // 0x65C: 16 palettes of 16 RGB colours (decode_4bpp_sprt's argument >> 12)
    unsigned char pad_95C[0x904];
    const MapData* m_map;     // 0x1260: none, check_map hits nothing
    unsigned char pad_1268[0x420];
    TBox m_tbox[16];          // 0x1688: a treasure box item task picks one (item_draw)
    unsigned char pad_1928[0x1AB8];
    unsigned char m_resultSub;    // 0x33E0: getResult reports it (| 0x100) with id 0xFFFE when m_resultFlag is set
    unsigned char pad_33E1[0x28];
    unsigned char m_scoreShow;    // 0x3409: enemy_damage sets 30 (frames)
    unsigned char pad_340A;
    unsigned char m_killCount;    // 0x340B: enemy_damage counts the enemies beaten
    unsigned short m_resultFlag;  // 0x340C
    unsigned char pad_340E[0x2];
    unsigned int m_stageScore;    // 0x3410: enemy_damage adds the points
    unsigned char pad_3414[0x4];
    unsigned short m_resultNum;   // 0x3418: getResult reports it with id 0xFFFF
    unsigned char pad_341A[0x130];
    unsigned short m_itemRate[2];  // 0x354A: an item drop's chance per 10000, of kind 0 and kind 1 (enemy_damage)
    unsigned char pad_354E[0xA];
    int m_scrollSpd;          // 0x3558: 24.8 fixed point; effects drift down by it
    unsigned char pad_355C[0x81C];
    CellAnime m_cellAnime;    // 0x3D78
    unsigned char pad_3D88[0x58];
    ResultItem m_resultItems[0x80];  // 0x3DE0: getResult reports those with a count
    SaveData m_save;          // 0x3FE0: finalize copies it into the game data
    unsigned char m_oamNum;   // 0x40B0: sprites queued in m_screen->m_oam
    unsigned char pad_40B1[0x7];
    mytask* m_task;           // 0x40B8
    unsigned char pad_40C0[0x8];  // MinigameUpdatableObject::myinit news 0x40C8 bytes
};

void effect_move(void* task);
void effect_draw(void* task);
void enemy_draw(void* task);
void item_draw(void* task);
}}  // namespace minigame::tora

#endif
