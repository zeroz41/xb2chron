#ifndef GF_GFGAMESTUCKMETER_H
#define GF_GFGAMESTUCKMETER_H

namespace gf {
// no table: an object's stuck meter (gf_game_stuck_meter's unit); GfComBehaviorMob keeps one at 0x130, its
// GfGameDepopMeter next at 0x190 (0x60 bytes). The field names are not the original's
class GfGameStuckMeter {
public:
    // what create takes, kept at 0; dispose drops its reference-counted pointer at 8 (asserting m_RefCount > 0)
    struct CreateInfo {
        ~CreateInfo() { dispose(); }
        void dispose();

        void* pad_0;
        void* pad_8;
    };
    explicit GfGameStuckMeter(const CreateInfo* info);
    ~GfGameStuckMeter() { dispose(); }
    void dispose();

    CreateInfo m_info;
    unsigned char pad_10[0x50];
};
}  // namespace gf

#endif
