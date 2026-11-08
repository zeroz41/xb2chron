#ifndef GF_GFSELECTBLADE_H
#define GF_GFSELECTBLADE_H

namespace gf { class GF_OBJ_HANDLE; }

namespace gf {
// the blades chosen for the party's drivers (functions, by 1.0.0's symbols); GfGameParty holds the one instance
// (0x20 bytes at +0x104) and its constructor and destructor inline this class's
class GfSelectBlade {
public:
    GfSelectBlade() {
        s_pThis = this;
        for (int i = 0; i < 3; ++i) {
            m_bladeOrder[i].m_default[0] = 0;
            m_bladeOrder[i].m_default[1] = 1;
            m_bladeOrder[i].m_default[2] = 2;
        }
        for (int i = 0; i < 3; ++i) {
            m_bladeOrder[i].m_current[0] = 0;
            m_bladeOrder[i].m_current[1] = 1;
            m_bladeOrder[i].m_current[2] = 2;
        }
        m_startBattleSetId[0] = -1;
        m_startBattleSetId[1] = -1;
        m_startBattleSetId[2] = -1;
    }
    ~GfSelectBlade() { s_pThis = nullptr; }

    // the blade set a driver slot (0-2) starts its battles with, -1 for none
    static int getStartBattleSetId(unsigned int slot);
    // forgets the blade set a driver slot starts its battles with (GfGameScene::gevChangeParty resets slots 0-2)
    static void resetStartBattleSetId(unsigned int slot);
    // the symbols name it. What it does: for a party member's driver, makes the default blade order of its slot
    // (m_bladeOrder's m_default) the one its blade set starts with and copies it to the current one
    static void resetDefaultBladeForDebug(gf::GF_OBJ_HANDLE* handle);

    static GfSelectBlade* s_pThis;  // the instance (GfGameParty's), null when there is none

    // a driver slot's blade orders: the current one and the default (resetDefaultBladeForDebug sets the default by
    // the driver's blade set and copies it to the current one); three blade indices each, 0, 1, 2 when made (the
    // names are not the original's)
    struct BladeOrder {
        unsigned char m_current[3];
        unsigned char m_default[3];
    };
    BladeOrder m_bladeOrder[3];  // by driver slot
    unsigned char pad_12[0x2];
    int m_startBattleSetId[3];  // by driver slot; resetStartBattleSetId sets -1
};
}  // namespace gf

#endif
