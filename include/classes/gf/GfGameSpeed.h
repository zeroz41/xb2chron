#ifndef CLASSES_GF_GFGAMESPEED_H
#define CLASSES_GF_GFGAMESPEED_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfGameSpeed; class GfSetupParam; }
namespace fw { class UpdateInfo; }
namespace gf { enum GEV : int; class MapjumpCallbackInfo; class QuestCompleteParam; class QuestCompleteChildParam; }

namespace gf {
// table 0x7100B54818; 0xC0 bytes (build allocates them). The game's update speeds: a requested speed per group of
// framework layers, applied to the framework by updateFrameSpeed when it changed (the field names are not the
// original's)
class GfGameSpeed : public ::mm::mtl::PtrSingleton< ::gf::GfGameSpeed> {
public:
    // one requested speed: updateFrameSpeed applies it while it is dirty and keeps what it applied
    struct Speed {
        Speed() : m_speed(1.0f), m_applied(1.0f), m_dirty(true) {}
        // a negative speed asks for 1
        void set(float speed) {
            speed = speed < 0.0f ? 1.0f : speed;
            if (m_speed != speed) {
                m_speed = speed;
                m_dirty = true;
            }
        }
        float m_speed;
        float m_applied;
        bool m_dirty;
    };
    // m_speeds' entries: setLayerSpeed's layers 0, 4, 1, 7 and 10 lead the framework layer groups 0, 4-6, 1-3,
    // 7-9 and 10-12; the factors scale them (the names are not the original's)
    enum {
        SPEED_GLOBAL = 0,  // setGlobalSpeed: the framework's update speed
        SPEED_PLAY = 1,    // setPlaySpeed: scales layers 0-6
        SPEED_LAYER0 = 2,
        SPEED_LAYER4 = 3,
        SPEED_LAYER1 = 4,
        SPEED_LAYER7 = 5,
        SPEED_LAYER10 = 6,
        SPEED_FACTOR1 = 8,          // scales layers 1-3
        SPEED_FACTOR0 = 9,          // scales layer 0 alone
        SPEED_SALVAGE = 10,         // setSalvageSpeed: scales layers 0 and 4-6
        SPEED_FACTOR1B = 11,        // scales layers 1-3
        SPEED_SALVAGE_CHARA = 12,   // setSalvageCharacterSpeed: scales layers 7-9
        SPEED_FACTOR10 = 13,        // scales layers 10-12
        SPEED_NUM = 14
    };

    GfGameSpeed(const GfSetupParam& param);
    virtual ~GfGameSpeed();  // slot 0
    // 2.0.0 symbol: sets m_valid; only the constructor calls it (inlined, gone from 3.0.1's symbols)
    void initialize(const GfSetupParam& param);
    static void build(const GfSetupParam& param);
    static void destroy();
    static void update(const fw::UpdateInfo& info);
    void updateFrameSpeed(const fw::UpdateInfo& info);
    static void clear();
    static float getLayerSpeed(unsigned int layer);
    static void setLayerSpeed(unsigned int layer, float speed);
    static void setGlobalSpeed(float speed);
    static void setPlaySpeed(float speed);
    static float getPlaySpeed();  // 0 without the singleton
    static void setSalvageSpeed(float speed);
    static void setSalvageCharacterSpeed(float speed);

    bool m_valid;          // 0x8: the constructor sets it last, destroy clears it
    float m_timedSpeed;    // 0xC: layers 0-6 run at it while m_timer runs (clear sets 1)
    float m_timer;         // 0x10: counts down by the frame time; at 0 m_timedSpeed falls back to layer 4's speed
    Speed m_speeds[SPEED_NUM];  // 0x14
};
}  // namespace gf

#endif
