#ifndef GF_GFSELECTBLADE_H
#define GF_GFSELECTBLADE_H

namespace gf {
// the blades chosen for the party's drivers (functions, by 1.0.0's symbols); GfGameParty holds the one instance
// (0x20 bytes at +0x104) and its constructor and destructor inline this class's
class GfSelectBlade {
public:
    GfSelectBlade() {
        s_pThis = this;
        for (int i = 0; i < 6; ++i) {
            m_bladeOrder[i][0] = 0;
            m_bladeOrder[i][1] = 1;
            m_bladeOrder[i][2] = 2;
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

    static GfSelectBlade* s_pThis;  // the instance (GfGameParty's), null when there is none

    // six orders of three blade indices, each 0, 1, 2 when made (the name is not the original's)
    unsigned char m_bladeOrder[6][3];
    unsigned char pad_12[0x2];
    int m_startBattleSetId[3];  // by driver slot; resetStartBattleSetId sets -1
};
}  // namespace gf

#endif
