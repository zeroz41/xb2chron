#ifndef CLASSES_TL_TITLEMAIN_H
#define CLASSES_TL_TITLEMAIN_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "ai/Fsm.h"
#include "fw/UpdateInfo.h"
#include "gf/SoundHandle.h"
#include "classes/tl/TitleMenu.h"
#include "mm/mtl/FixStr.h"

namespace gf { class SDataOption; }
namespace gf { class SDataSave; }
namespace gf { class GF_SE_CATEGORY_HANDLE; }
namespace gf { enum SAVESLOT : int; }

template <typename T> class MicroUpdater;

namespace tl {
// table 0x7100B40138; the title screen: its state machine (12 state IDs) stepped on a micro thread of its own
// (0x220 bytes, TitleMain::create)
class TitleMain : public ::mm::mtl::PtrSingleton< ::tl::TitleMain> {
public:
    TitleMain();
    virtual ~TitleMain();  // slot 0
    static TitleMain* create();
    void initialize();
    // finalizes the title and deletes it
    static void destroy();
    // steps the title's instance, if there is one, with the frame's update info (tl::TitleApplet::update calls it)
    static void update(const fw::UpdateInfo& info);
    void finalize();
    void createSaveBuffer();
    // the micro thread's function: steps the state machine until it reaches state 9 (TitleStateDestroy)
    static void fnUpdate(TitleMain* self);
    static void sleep(unsigned int frames);
    // whether the title's state is TitleStateToTitle (8); false while there is no title
    static bool isReturnTitle();
    static void returnTitle(gf::SAVESLOT slot);  // GfPlayComReturnTitle passes -1
    bool isStateReturnTitle() const;
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it (1.0.0 has getSaveBuffer, getOptionBuffer,
    // clearSaveBuffer there). A member because it reads this+0x130 like getSaveBuffer, right before it. What it
    // does: returns the save buffer (createSaveBuffer's), exactly as getSaveBuffer does; 14 callers
    // (GfGameManager::isClearGame, GfGameUtilSaveData::setupGameSaveData, GfMenuObjTitle::initialize...).
    gf::SDataSave* fn_710014FB00();
    gf::SDataSave* getSaveBuffer();
    // returns a reference: GfGameUtilSaveData::getValidOptionData calls it without a tail call, which a pointer
    // return would give (the callee's nonnull/dereferenceable return attributes stop clang's tail call)
    gf::SDataOption& getOptionBuffer();
    void setupTitleOptionToGameOption();
    // the chapter of the save buffer's game: 0 for no save (wrong version) or no scenario, else the scenario
    // flag / 1000, 1 to 10
    unsigned int getChapterIdFromSaveData();
    // stops the title BGM (fading over the given time) when one plays
    void stopTitleBGM(float time);
    void playTitleBGM();
    void playTitleEvent(unsigned int eventID);
    unsigned int getPlayTitleEvent();
    // 2.0.0's symbols name it. What it does: makes the title's SE category handle (this+0x210) with
    // gf::GfSound::createCategoryHandle when it has none, then sets that category's volume
    // (gf::GfSound::setCategoryVolume) to the float for the sound categories 0xD, 0xE and 0.
    void setMaskVolumeGameSe(float volume);
    // 2.0.0's symbols name it. What it does: makes the title's sound category handle (this+0x208) with
    // gf::GfSound::createCategoryHandle when it has none, then gf::GfSound::setCategoryVolume(handle, category, volume,
    // time) for the categories 1, 0xD, 0xE, 5, 7, 6 and 8. gevPlayEvent passes (1.0, 0.0).
    void setMaskVolumeFade(float volume, float time);
    // 2.0.0's symbols name it. What it does: clears m_newGameAdv; when the save buffer's version is 0x3A15B and
    // GfDataBlade::fn_710023217C holds for its game, makes the game's clear count at least 1 and sets m_newGameAdv when
    // GfDataBlade::fn_7100231EB8 (local flag 1, type 16) is 10032 or more; then sets m_isClear when the clear count is
    // not 0 and clears m_newGameAdv again when GfDataBlade::fn_7100232244 holds.
    void getGameClearFlagFromSaveData();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because
    // TitleStateMainScreen::playTitleEvent calls it with the title and it reads the title's save buffer and
    // m_newGameAdv. What it does: true when the save buffer's version is 0x3A15B, GfDataBlade::fn_710023217C holds
    // for its game and m_newGameAdv is set.
    bool fn_710014FC5C();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because fn_7100400410 calls it
    // on TitleMain's instance and it reads the title's save buffer. What it does: the weather of the save buffer's
    // saved event row whose event is the given one (0 without a save buffer or such a row).
    unsigned short fn_710014FCB0(unsigned int event);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member for the same reason as
    // fn_710014FCB0. What it does: the hour of the save buffer's saved event row whose event is the given one (12
    // without a save buffer or such a row).
    unsigned int fn_710014FD10(unsigned int event);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because
    // GfMenuObjTitle::ListListener::reciveEvent calls it with TitleMain's instance and it reads the title's save
    // buffer. What it does: true when the save buffer's version is not 0x3A15B, else whether
    // GfDataBlade::fn_71002325AC does not hold for its game.
    bool fn_710014FD74();
    // 2.0.0's symbols name it. What it does: passes the bool to GfManager::resetGameType, then clears m_isClear and
    // m_newGameAdv.
    void resetGameType(bool flag);

    // an event to play from the title: 0x54 bytes (the constructor's stores; eventMenuResult copies the first 16 bytes
    // as two words and the string with FixStr's assignment). The type and member names are not the original's.
    struct EventRequest {
        unsigned short m_event;  // TitleStatePlayEvent::enter passes it to GfDataEvent::isBladeCreateEvent
        // two zeroed halfwords as made (the constructor's zero stores merge with the previous member's; one zeroed
        // 4-byte block does not): what they hold is not known
        unsigned short pad_2;
        unsigned short pad_4;
        unsigned char pad_6 = 0x15;  // 0x15 as made; what it holds is not known
        unsigned char pad_7[0x9];
        mm::mtl::FixStr<64> m_text;  // a 64-character string, empty as made; what it holds is not known
        EventRequest() : m_event(0), pad_2(0), pad_4(0), pad_7() {}
    };

    ai::Fsm m_fsm;
    MicroUpdater<TitleMain>* m_updater;  // initialize's; runs fnUpdate (the name is not the original's)
    fw::UpdateInfo m_updateInfo;  // what fnUpdate steps the states with (the name is not the original's)
    // set to have TitleStatePlayGame change to TitleStateDestroy (9) (the name is not the original's)
    bool m_reqDestroy;
    // set by returnTitle to have TitleStatePlayGame change to TitleStateToTitle (8) (the name is not the original's)
    bool m_reqReturnTitle;
    unsigned char pad_96[0x2];
    gf::SoundHandle m_titleBgm;  // the title BGM; stopTitleBGM stops and clears it (the name is not the original's)
    bool m_isTitleBgm;  // stopTitleBGM clears it (the name is not the original's)
    unsigned char pad_A1[0x3];
    // the slot returnTitle was given; TitleMain(), TitleStateLoad::update and TitleStateWarning's step set -1 (the name
    // is not the original's)
    gf::SAVESLOT m_returnSlot;
    // a 128-character string the constructor empties; nothing in this unit reads it (the type is the constructor's
    // stores: the first char and the length at 0x128; the name stays a placeholder)
    mm::mtl::FixStr<128> pad_A8;
    unsigned char pad_12C[0x4];
    gf::SDataSave* m_saveBuffer;  // createSaveBuffer's (getSaveBuffer; the name is not the original's)
    gf::SDataOption* m_optionBuffer;  // createSaveBuffer's (getOptionBuffer; the name is not the original's)
    // the event TitleStatePlayEvent::enter plays (it copies it and reads the event id): TitleStateMainScreen::update
    // changes to state 4 when it holds one, TitleStateSelectEvent::eventMenuResult fills it from m_eventTemplate with
    // the event theater's choice (the name is not the original's)
    EventRequest m_eventRequest;
    unsigned char pad_194[0x4];
    // the title's menus (TitleStateMainScreen::dispTitleMenu calls them on this+0x198; the name is not the original's)
    TitleMenu m_menu;
    // what eventMenuResult copies into m_eventRequest (all but the event id; the name is not the original's)
    EventRequest m_eventTemplate;
    unsigned char pad_1FC[0x4];
    unsigned int m_playTitleEvent;  // playTitleEvent's (the name is not the original's)
    unsigned char pad_204[0x4];
    // setMaskVolumeFade's sound category handle, made on first use; the constructor sets -1 (the name is not the original's)
    gf::GF_SE_CATEGORY_HANDLE* m_seCategory;
    // setMaskVolumeGameSe's sound category handle, made on first use (the name is not the original's)
    gf::GF_SE_CATEGORY_HANDLE* m_seCategorySub;
    bool m_isClear;  // GfMenuManager::isClearCheck returns it (the name is not the original's)
    // GfMenuObjTitle::isEnableNewGameAdv answers it when there is save data (the name is not the original's)
    bool m_newGameAdv;
    // TitleStateMainScreen::checkMenuResult takes and clears it as the title menu's result 6 (TitleStateChangeGameType)
    // (the name is not the original's)
    bool m_reqChangeGameType;
    bool m_flag21B;  // GfGameManager::isCompleteBothGame answers it (the name is not the original's)
    unsigned char pad_21C[0x4];
};
}  // namespace tl

#endif
