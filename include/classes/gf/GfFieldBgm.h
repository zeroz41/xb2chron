#ifndef CLASSES_GF_GFFIELDBGM_H
#define CLASSES_GF_GFFIELDBGM_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/FixStr.h"

namespace gf { class GfFieldBgm; }

namespace gf {
// table 0x7100B511B8
class GfFieldBgm : public ::mm::mtl::PtrSingleton< ::gf::GfFieldBgm> {
public:
    virtual ~GfFieldBgm();  // slot 0
    void stopBgmForDebug(bool stop);
    void setGimmickBgmID(unsigned int id);
    void setRscBattleBgmID(unsigned int id);
    void gevBattleEnd();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member: GfPlayComEvent::gevPlayEvent calls
    // it on GfFieldBgm's instance (it then ignores this). What it does: hands the name to gf::BgmField's instance
    // (fn_7100262E70) when there is one; its only caller passes GfPlayComEvent's BGM name on GEV 14.
    void fn_7100262E58(const mm::mtl::FixStr<64>& name);
    bool isBossBgmCopied() const;  // 1.0.0's symbol at the same place, with the same caller (GfFieldSound::gevBattleEnd)
    // 1.0.0's out-of-line getters (3.0.1 inlines them)
    unsigned int getRscFieldBgmID() const;
    unsigned int getRscGimmickBgmID() const { return m_rscGimmickBgmID; }
    unsigned int getRscBossBattleBgmID() const { return m_rscBossBattleBgmID; }
    unsigned int getRscBattleBgmID() const { return m_rscBattleBgmID; }
    bool isDisableFieldBgmChange() const { return m_disableFieldBgmChange; }

    unsigned char pad_8[0x88];
    unsigned int m_rscBossBattleBgmID;  // 1.0.0's getRscBossBattleBgmID reads it
    unsigned char pad_94[0x4];
    unsigned int m_rscBattleBgmID;  // 1.0.0's getRscBattleBgmID reads it
    unsigned int m_rscGimmickBgmID;  // 1.0.0's getRscGimmickBgmID reads it
    unsigned int m_gimmickBgmID;  // setGimmickBgmID stores it
    // set to 30 when setGimmickBgmID clears a set gimmick BGM (the name is not the original's)
    unsigned int m_gimmickBgmClearWait;
    bool m_disableFieldBgmChange;  // 1.0.0's isDisableFieldBgmChange reads it
    // bgmvolFadeDeadSequence fades out while it is set (the name is not the original's)
    bool m_deadSequence;
};
}  // namespace gf

#endif
