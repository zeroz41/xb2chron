#ifndef CLASSES_GF_GFMANAGER_H
#define CLASSES_GF_GFMANAGER_H

#include "classes/fw/IPauseTrigger.h"
#include "classes/gf/IGfEvent.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "gf/GfSetupParam.h"

namespace fw { class UpdateInfo; }
namespace gf { class GfManager; }
namespace gf { class SDataGame; }
namespace gf { struct EvtTheaterParam; }
namespace gf { class SDataGameIra; }
namespace gf { class SDataOption; }
namespace gf { class SDataSystem; }
namespace gf { enum EXEC_STATE : int; }
namespace gf { enum GF_STATE : int; }

namespace gf {
// table 0x7100B59268
class GfManager : public ::mm::mtl::PtrSingleton< ::gf::GfManager>, public ::fw::IPauseTrigger, public ::gf::IGfEvent {
public:
    // the game modes the setup functions store in m_gameMode (the names are not the original's): isNewGame tests 1,
    // isContinueGame 2
    enum GameMode { GAME_MODE_NONE = 0, GAME_MODE_NEW = 1, GAME_MODE_CONTINUE = 2 };

    // the execution state's flags (the 6-entry table setExec reads): isExecKillPartyCreate's, isExecModeScenarioGame's,
    // isExecModeAdvertize's (the names are not the original's)
    enum ExecFlag { EXEC_FLAG_KILL_PARTY_CREATE = 1 << 0, EXEC_FLAG_SCENARIO_GAME = 1 << 2, EXEC_FLAG_ADVERTIZE = 1 << 3 };

    static void setExec(EXEC_STATE state);
    void initialize();
    static void postUpdate(const fw::UpdateInfo& info);
    // 2.0.0's symbols name it. What it does: passes the update info to GfGameManager's updateAfterLayer when there is a
    // game manager. Its one caller is TitleApp's table slot 17 (TitleApplet::updateAfterLayer), between TitleApplet::update (slot 16,
    // which calls GfManager::update) and postUpdate
    static void updateAfterLayer(const fw::UpdateInfo& info);
    static void update(const fw::UpdateInfo& info);
    virtual ~GfManager();  // slot 0
    void finalize();
    // makes the game manager from the setup parameters (tl::TitleApplet::initialize)
    static void build(const GfSetupParam& param);
    static void destroy();
    static bool isDestroyNow();
    static bool isExecModeDebug();
    // the setup parameters the manager keeps (at 0x18 of its object)
    static GfSetupParam& getSetupParam();
    virtual void updatePauseCallback();  // slot 2
    virtual void gevGameState(gf::GF_STATE, gf::GF_STATE);  // slot 3
    virtual void activate();  // slot 4
    static bool isExecKillPartyCreate();
    static bool isExecModeScenarioGame();
    static bool isExecModeAdvertize();
    static bool isExecModeTool();
    static bool isExecModeThater();
    static void setupNewGame(const SDataSystem& system, const SDataGame& game, const SDataOption& option,
                             const SDataGameIra& ira);
    static void setupPowerNewGame(const SDataSystem& system, const SDataGame& game, const SDataOption& option,
                                  const SDataGameIra& ira);
    static void setupContinueGame(const SDataSystem& system, const SDataGame& game, const SDataOption& option,
                                  const SDataGameIra& ira);
    static void setupEventTheater(const SDataGame& game);
    static void setupReturnTitle();
    static void startGame(bool saveDataCreated, bool clearGameCheck);
    static void startEventTheater(const EvtTheaterParam& param);
    static void execToAdvertize();
    static void setupOptionData(const SDataOption& option);
    static bool isContinueGame();
    static bool isNewGame();
    // 2.0.0's symbols name it. What it does: returns GfGameManager::isGameTypeIra()'s answer (a tail call)
    static bool isGameTypeIra();
    // 1.0.0's names for the functions at 0x710032A270 and 0x710032A298 (same code, the flag moved from 0x58 to 0x60)
    // 2.0.0's symbols name it. What it does: stores its bool in m_stopUpdate when there is a manager (update and
    // postUpdate then skip the managers)
    static void setBusyForChangeGame(bool flag);
    // 2.0.0's symbols name it. What it does: passes its bool to the framework's, the effect manager's and the sound
    // manager's setupThreadPostUpdate / setIra / setupGameType (each when it exists), GfGameManager::resetGameType and
    // fw::RenderParam::setRenderTypeDlc
    static void resetGameType(bool flag);
    static bool isExistSaveData();
    static void setSaveDataCreated();

    static GfManager* s_pThis;

    GfSetupParam m_setupParam;  // getSetupParam's (build's copy)
    bool m_initialized;  // initialize sets it, finalize clears it
    bool m_destroyNow;  // finalize sets it (isDestroyNow)
    EXEC_STATE m_execState;  // setExec's; isExecModeTool tests 4, isExecModeDebug 0, isExecModeThater 3
    unsigned short m_execFlags;  // setExec's: the state's ExecFlags
    int m_gameMode;  // a GameMode: the setup functions'
    unsigned int m_frameCount;  // update counts its frames (the name is not the original's)
    float m_loadGameTime;  // gevGameState: the load's seconds (-1 at first; setupContinueGame clears it)
    bool m_saveDataCreated;  // setSaveDataCreated (isExistSaveData)
    // update and postUpdate run no manager while it is set (setBusyForChangeGame's; the name is not the original's)
    bool m_stopUpdate;
    unsigned char pad_62[0x6];
};

// the game's pad and sound resources, bound and unbound with the manager (GfManager::initialize, finalize)
void bindPadResources();
void unbindPadResource();
void bindGFSoundSource();
void unrbindGFSoundSource();
}  // namespace gf

#endif
