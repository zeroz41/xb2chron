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
    virtual ~CharaTarPlayerMot();  // slot 0
    // 0x71000D2ECC: keeps the object and its weight player, clears the vectors and resets both curves to 0..1
    void create(gf::GF_OBJ_HANDLE*, CharaWeightPlayer*);
    gf::GF_OBJ_HANDLE* m_handle;  // 0x8
    CharaWeightPlayer* m_weightPlayer;  // 0x10
    unsigned char pad_18[0x18];
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
