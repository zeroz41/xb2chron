#ifndef CLASSES_EVENT_CHARATARPLAYER_H
#define CLASSES_EVENT_CHARATARPLAYER_H

#include "classes/event/AnmF32.h"

namespace gf { class GF_OBJ_HANDLE; }
namespace event { class CharaIKUpdater; }

namespace event {
// table 0x7100B3CA10
class CharaTarPlayer {
public:
    CharaTarPlayer() : m_handle(reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)), m_ik(nullptr), pad_18(0) {}
    virtual ~CharaTarPlayer();  // slot 0
    void update(float);
    // a 16-byte entry of m_items (update reads the first one's +0x4, +0x8 byte and +0xC float); the name is not the
    // original's
    struct Item {
        unsigned int pad_0[4];
    };
    // the handle and IK updater 1.0.0's create(GF_OBJ_HANDLE*, CharaIKUpdater*) stores; the names are not the
    // original's
    gf::GF_OBJ_HANDLE* m_handle;  // 0x8
    CharaIKUpdater* m_ik;  // 0x10
    int pad_18;
    unsigned char pad_1c[0x4];
    // update erases the first entry once its time runs out, setEnable empties it; the name is not the original's
    mm::mtl::FixedVector<Item, 6> m_items;  // 0x20, count at 0x80
    unsigned char pad_88[0x38];
    // the curve the destructor tears down; the name is not the original's
    AnmF32 m_anm;  // 0xc0
};
}  // namespace event

#endif
