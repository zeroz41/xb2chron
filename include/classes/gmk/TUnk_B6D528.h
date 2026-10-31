#ifndef CLASSES_GMK_TUNK_B6D528_H
#define CLASSES_GMK_TUNK_B6D528_H

#include "classes/gmk/AGmkBase.h"
#include "classes/gmk/GmkPhantom.h"
#include "classes/gmk/TUnk_B6D418.h"

namespace gmk {
// Placeholder name: the gimmick of kind 0x3B (table 0x7100B6D528), new in 3.0.1. Element (0x100 bytes) of the list
// TGmkList<TUnk_B6D528, ..., 'BTCL', ...> (table 0x7100B6F098) at 0x230 of GmkEnemyList's member at 0x470.
class TUnk_B6D528Gob;

class alignas(16) TUnk_B6D528 : public ::gmk::AGmkBase {
public:
    // weak (tail of the unit): emitted with the table, whose key function is create
    virtual ~TUnk_B6D528() { dispose(); }  // slot 0 (fn_71005BC0BC, dispose inlined; D0 fn_71005BC1C0)
    virtual gmk::GmkType getGmkType() const { return TYPE; }  // slot 2 (fn_71005BC2B4)
    virtual bool isValid() const { return m_list != nullptr && m_createInfo.m_data != nullptr; }  // slot 3 (fn_71005BC2BC)
    virtual void create(gmk::AGmkBase::CreateInfo const&);  // slot 4 (fn_71005B6F44, 0x234)
    virtual void dispose();  // slot 5 (fn_71005B726C, 0xD8)
    virtual void update(float);  // slot 6 (fn_71005B7374, 0x70)
    virtual void debugDraw() const;  // slot 7 (fn_71005B73E4, empty)
    class BdatInfo {};
    static const gmk::GmkType TYPE = gmk::GmkType(0x3b);
    // its data (m_createInfo.m_data): the range of waves (TUnk_B6D418, GmkEnemyList's m_waveList) it runs, by index
    // (the names are not the original's)
    struct Data {
        unsigned char pad_0[0x4];
        unsigned int m_waveBegin;  // 0x4
        unsigned int m_waveEnd;    // 0x8
    };
    // the challenge's progress the battle code reads (btl::TUnk_B3A9C8 loads 0x0/0x4 and the byte at 0x8); the
    // names are not the original's
    struct State {
        State() { clear(); }
        void clear() {
            m_result = 0;
            m_isEnd = false;
            m_waveNum = 0;
            m_waveIndex = 0;
        }
        unsigned int m_waveNum;    // 0x0: how many waves it has
        unsigned int m_waveIndex;  // 0x4: the wave it is at (from 1)
        bool m_isEnd;              // 0x8
        int m_result;              // 0xC: 1 or 2 when a wave ended (2 while time was left)
    };
    const Data* getData() const { return reinterpret_cast<const Data*>(m_createInfo.m_data); }
    // how many waves it runs: none while not valid (the name is not the original's)
    unsigned int getWaveNum() const { return isValid() ? getData()->m_waveEnd - getData()->m_waveBegin : 0; }
    // its index-th wave in the gimmick set's enemy list, none when the set has no enemy list or fewer waves (defined
    // in GmkElevator.cpp, which sees GmkEnemyList; the name is not the original's)
    TUnk_B6D418* getWave(unsigned int index) const;
    // Placeholder names (no symbols; members: they read and change this object or its statics)
    // fn_71005B73E8: the gimmick an access built from its first wave's GmkAcc create info points to, none when not valid
    AGmkBase* fn_71005B73E8();
    // fn_71005B7178, fn_71005B76B4: the steps create and the first step store in m_seq
    void fn_71005B7178(float dt);
    void fn_71005B76B4(float dt);
    // fn_71005B7344: clears s_current, s_battleId and s_state (GfAppendWire's fn_710028D1CC calls it)
    static void fn_71005B7344();
    // the running challenge, set by fn_71005B7178 (lbl_7100EB7DB0; the name is not the original's)
    static TUnk_B6D528* s_current;
    // set by GfAppendWire's fn_710028D1CC from its message (lbl_7100EB7DB8; the name is not the original's)
    static unsigned int s_battleId;
    // lbl_7100EB7DBC (the name is not the original's)
    static State s_state;
    unsigned char pad_48[0x8];
    GmkPhantom m_phantom;  // 0x50 (the name is not the original's)
    void (TUnk_B6D528::*m_seq)(float dt);  // 0xE0: create sets fn_71005B7178, dispose clears it (the name is not the original's)
    unsigned short m_waveCount;  // 0xF0: the waves done (the name is not the original's)
    unsigned char pad_f2[0x2];
    float m_timer;  // 0xF4: fn_71005B76B4 sets it from the wave's data (the name is not the original's)
    bool m_isAccCounted;  // 0xF8: create clears it, fn_71005B7178 sets it after counting the access (the name is not the original's)
    bool m_isPaused;  // 0xF9: update skips m_seq when set (the name is not the original's)
    unsigned char pad_fa[0x2];
    int m_result;  // 0xFC: copied to s_state.m_result (the name is not the original's)
};
}  // namespace gmk

#endif
