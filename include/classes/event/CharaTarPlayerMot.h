#ifndef CLASSES_EVENT_CHARATARPLAYERMOT_H
#define CLASSES_EVENT_CHARATARPLAYERMOT_H

#include "classes/event/AnmF32.h"
#include "mm/Vec3.h"

namespace gf { class GF_OBJ_HANDLE; }

namespace event {
class CharaWeightPlayer;

// table 0x7100B3CA30
class CharaTarPlayerMot {
public:
    CharaTarPlayerMot()
        : m_handle(reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)), m_weightPlayer(nullptr), pad_18(0), pad_20(0), pad_24(0),
          pad_280() {}
    virtual ~CharaTarPlayerMot();  // slot 0
    // 0x71000D2ECC: keeps the object and its weight player, clears the vectors and resets both curves to 0..1
    void create(gf::GF_OBJ_HANDLE*, CharaWeightPlayer*);
    void update(float);
    gf::GF_OBJ_HANDLE* m_handle;  // 0x8
    CharaWeightPlayer* m_weightPlayer;  // 0x10
    unsigned long pad_18;
    unsigned int pad_20;
    unsigned char pad_24;
    unsigned char pad_25[0xb];
    mm::Vec3 m_vec0;  // 0x30 (create zeroes the three vectors)
    mm::Vec3 m_vec1;  // 0x40
    mm::Vec3 m_vec2;  // 0x50
    // the two curves the destructor tears down (last first); the names are not the original's
    AnmF32 m_anm0;  // 0x60
    AnmF32 m_anm1;  // 0x170
    unsigned long pad_280[3];  // create zeroes them
};
}  // namespace event

#endif
