#ifndef CLASSES_TL_TITLEMAIN_H
#define CLASSES_TL_TITLEMAIN_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "ai/Fsm.h"
#include "fw/UpdateInfo.h"
#include "gf/SoundHandle.h"

namespace gf { class SDataOption; }
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
    void finalize();
    void createSaveBuffer();
    // the micro thread's function: steps the state machine until it reaches state 9 (TitleStateDestroy)
    static void fnUpdate(TitleMain* self);
    static void sleep(unsigned int frames);
    // whether the title's state is TitleStateToTitle (8); false while there is no title
    static bool isReturnTitle();
    static void returnTitle(gf::SAVESLOT slot);  // GfPlayComReturnTitle passes -1
    bool isStateReturnTitle() const;
    gf::SDataOption* getOptionBuffer();
    void setupTitleOptionToGameOption();
    // stops the title BGM (fading over the given time) when one plays
    void stopTitleBGM(float time);
    void playTitleBGM();
    void playTitleEvent(unsigned int eventID);
    unsigned int getPlayTitleEvent();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because returnTitle and
    // TitleStateMainScreen::onEnter call it with the title (x0) and a float (s0). What it does: makes the title's
    // SE category handle (this+0x210) with gf::GfSound::createCategoryHandle when it has none, then sets that
    // category's volume (gf::GfSound::setCategoryVolume) to the float for the sound categories 0xD, 0xE and 0.
    void fn_710014F70C(float volume);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because returnTitle,
    // TitleStatePlayGame::enter, TitleStatePlayEvent::enter and TitleStatePlayEvent::gevPlayEvent call it with the
    // title (x0) and two floats (s0, s1). What it does: makes the title's sound category handle (this+0x208) with
    // gf::GfSound::createCategoryHandle when it has none, then gf::GfSound::setCategoryVolume(handle, category,
    // volume, time) for the categories 1, 0xD, 0xE, 5, 7, 6 and 8. gevPlayEvent passes (1.0, 0.0).
    void fn_710014F5FC(float volume, float time);

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
    unsigned char pad_A1[0x97];
    gf::SDataOption* m_optionBuffer;  // createSaveBuffer's (getOptionBuffer; the name is not the original's)
    unsigned char pad_140[0xC0];
    unsigned int m_playTitleEvent;  // playTitleEvent's (the name is not the original's)
    unsigned char pad_204[0x4];
    // fn_710014F5FC's sound category handle, made on first use; the constructor sets -1 (the name is not the original's)
    gf::GF_SE_CATEGORY_HANDLE* m_seCategory;
    // fn_710014F70C's sound category handle, made on first use (the name is not the original's)
    gf::GF_SE_CATEGORY_HANDLE* m_seCategorySub;
    unsigned char pad_218[0x8];
};
}  // namespace tl

#endif
