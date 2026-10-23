#ifndef CLASSES_GF_GFGAMESALVAGE_H
#define CLASSES_GF_GFGAMESALVAGE_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "ai/Fsm.h"

namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class GfSetupParam; }
namespace fw { class UpdateInfo; }
namespace gf { class GfComBehaviorSalvage; }
namespace gf { class GfGameSalvage; }
namespace mm { class Mat44; }
namespace mm { class Vec3; }

namespace gf {
// table 0x7100B56ED8; the salvage mini-game: its states (StateSalvage*) drive it through these
class GfGameSalvage : public ::mm::mtl::PtrSingleton< ::gf::GfGameSalvage> {
public:
    // the salvager's animations, voices and sounds, by number (no value has a name yet)
    enum AnimationType : int {};
    enum VoiceType : int {};
    enum SEID : int {};
    // what execRaffle draws the treasures from (the names are not the original's: StateSalvageDiveFadeWait passes
    // the cylinder's grade, the button challenges' points and the skills' levels)
    struct RaffleInfo {
        unsigned int m_grade;
        float m_point;
        unsigned int m_skillLevel;
    };
    // what getRaffleResult reports (the names are not the original's: StateSalvageResultUi reads m_rank)
    struct RaffleRet {
        RaffleRet() {
            m_unk8 = 0;
            m_unk0 = 0;
            m_rank = 0;
        }
        unsigned int m_unk0;
        unsigned int m_rank;
        unsigned short m_unk8;
    };

    virtual ~GfGameSalvage();  // slot 0
    // registers the 21 salvage states (StateSalvage*) with its state machine and starts in StateSalvageWait
    void initialize(const GfSetupParam& param);
    // 1.0.0's: frees the machine's state buffers (inline in 3.0.1: destroy has it)
    void finalize() {
        m_fsm.cleanup();
        m_initialized = false;
    }
    static void destroy();
    static void update(const fw::UpdateInfo& info);
    // starts the salvage at the salvage point (from StateSalvageWait, in the field only)
    static void startSalvage(GF_OBJ_HANDLE* handle);
    static bool isStateWait();
    static void cancelSalvage();
    bool isTboxExist() const;
    unsigned char* getBindedBdatFp() const;
    unsigned int getBindedBdatId() const;
    bool getEventOrigin(mm::Mat44& mtx) const;
    bool getEventTbox(mm::Mat44& mtx) const;
    void createModel();
    void destroyModel();
    bool isValidModel();
    void setModelTransform(const mm::Vec3& pos, float rotY);
    void createCameraDiveStart(const mm::Vec3& pos, float rotY);
    void destroyCameraDiveStart();
    void playCameraDiveStart();
    void createCameraDive(AnimationType type, const mm::Vec3& pos, float rotY);
    void destroyCameraDive();
    void playCameraDive();
    bool isCameraDive();
    void createCameraClimb(AnimationType type, const mm::Vec3& pos, float rotY);
    void destroyCameraClimb();
    void playCameraClimb();
    bool isCameraClimbEnd();
    void createCameraCut01(const mm::Vec3& pos, float rotY);
    void destroyCameraCut01();
    void playCameraCut01();
    bool isCameraCut01End();
    void applyPartyForm() const;
    void setPartyDisp(bool disp);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it (1.0.0's StateSalvageSetupFadeIn::enter calls
    // setPartyDisp(false) where 3.0.1's calls this with false; StateSalvageResult::leave calls it with true). A member
    // because its address is in gf_game_salvage's range and the states pass it the salvage game.
    void fn_7100315A84(bool flag);
    void playAnimation(AnimationType type);
    bool isAnimationEnd() const;
    void playVoice(VoiceType type);
    bool isVoiceEnd();
    void playSE(SEID id);
    void playDiveVibration();
    void playClimbReady();
    void playClimb();
    bool isClimbEnd();
    void calcClimb();
    void playWireStart(float, float, float);
    AnimationType getClimbAnimationType() const;
    bool isChaseKikuInSupervia();
    int getButtonChallengeId(int index);
    GfComBehaviorSalvage* getGfComBehaviorSalvage() const;
    void execRaffle(const RaffleInfo& info);
    void getRaffleResult(RaffleRet& ret) const;
    void execPop();
    unsigned int getTBoxNum();
    void addSalvagerPoint(unsigned int point);
    void createLog();
    void setLogSkill(bool success, unsigned int level);
    void clearLogSkill();
    void setLogButtonChallenge(int id, int result);
    void clearLogButtonChallenge();
    void setLogButtonChallengeResult(int result);
    void setLogLapsedTime(int time);

    // the states' machine: the states get the game as their owner (the name is not the original's)
    ai::Fsm m_fsm;
    unsigned char pad_80[0x20];
    // set once initialize has set the machine up (the name is not the original's)
    bool m_initialized;
    unsigned char pad_A1[0x7];
    GF_OBJ_HANDLE* m_pHandle;  // the salvage point's (StateSalvageResultUi hands its gimmick to SCOM_QUEST_GIMMICK)
    // the names below are not the original's
    int m_challengePoint;  // the button challenges' points (StateSalvageDiveStart adds them)
    unsigned int m_skillLevel;      // the levels of the field skills that worked (StateSalvageSkillCheck)
    unsigned int m_item;            // the cylinder chosen (StateSalvageItemSelect)
};
}  // namespace gf

#endif
