#ifndef GF_GFGAMESTUCKMETER_H
#define GF_GFGAMESTUCKMETER_H

#include "mm/Vec3.h"

namespace fw { class ColiMoveObject; }

namespace gf {
// no table: an object's stuck meter (gf_game_stuck_meter's unit); GfComBehaviorMob keeps one at 0x130, its
// GfGameDepopMeter next at 0x190 (0x60 bytes). The field names are not the original's: while the object's collision
// does not move as fast as its move vector asks (checkStuck), it shrinks the collision shape (or scale) by 0.99 a
// frame down to 0.05; after 3 seconds free it grows it back by 1.1 up to the size create saw
class GfGameStuckMeter {
public:
    // what create takes, kept at 0; dispose drops its counted collision object at 8 (asserting m_RefCount > 0)
    struct CreateInfo {
        CreateInfo() : pad_0(1.0f), m_stuckDelay(0.5f), m_coli(nullptr), m_minSpeedSq(1.0f) {}
        ~CreateInfo() { dispose(); }
        void dispose();
        // holds coli instead, counted (the old one released first)
        void setColiObj(fw::ColiMoveObject* coli);
        float pad_0;
        float m_stuckDelay;          // seconds stuck before the shape shrinks
        fw::ColiMoveObject* m_coli;  // counted by hand (addRef/release), not an IntrusivePtr
        float m_minSpeedSq;          // checkStuck: moving slower (squared, per second) is stuck
        unsigned char pad_14[0x4];
    };
    explicit GfGameStuckMeter(const CreateInfo* info);
    ~GfGameStuckMeter() { dispose(); }
    void create(const CreateInfo& info);
    void dispose();
    void update(float deltaTime);
    bool checkStuck(float deltaTime);
    CreateInfo m_info;
    // the collision's character shape (height, radius) as create saw it, or its scale without one
    float m_height;
    float m_radius;
    float m_scale;
    unsigned char pad_24[0xC];
    mm::Vec3 m_pos;      // the collision's last position
    mm::Vec3 m_avgPos;   // the mean of its last two positions
    float m_freeTime;    // seconds not stuck
    float m_stuckTime;   // seconds stuck
    unsigned char pad_58[0x8];
};
}  // namespace gf

#endif
