#ifndef CLASSES_TL_TITLESTATEMAINSCREEN_H
#define CLASSES_TL_TITLESTATEMAINSCREEN_H

#include "classes/ai/State.h"
#include "classes/gf/IGfEvent.h"
#include <new>

namespace ai { class State; }
namespace fw { class UpdateInfo; }
namespace gf { enum GEV : int; }

namespace tl {
class TitleMain;

// table 0x7100B403B8
class TitleStateMainScreen : public ::ai::State, public ::gf::IGfEvent {
public:
    // what TitleMain::initialize registers with its Fsm: the state made in a state buffer
    static ai::State* create(void* buffer) { return new (buffer) TitleStateMainScreen; }
    // inline: the deleting destructor only frees it
    virtual ~TitleStateMainScreen() {}  // slot 0
    inline virtual const char* getName() const;  // slot 2
    inline virtual void onEnter(void*, ai::State*);  // slot 3
    inline virtual void onLeave(void*, ai::State*);  // slot 4
    inline virtual void onStep(void*, void const*);  // slot 5
    void update(TitleMain* title, const fw::UpdateInfo& info);
    // loads the save and option data for the title; true when the save buffer holds no current save (version not 0x3A15B)
    bool loadSaveDataForTitle(TitleMain* title);
    void playTitleEvent(TitleMain* title);
    // opens the title menu and waits for it; true when the title is to be destroyed meanwhile (state 9 requested)
    bool dispTitleMenu(TitleMain* title, bool flag);
    // waits for the title menu's result (into TitleMenu::m_request); true when a state change was requested instead
    bool checkMenuResult(TitleMain* title);
    // closes the title menu and requests the state its result names; always true
    bool waitTitleMenuDestroy(TitleMain* title);
    virtual void gevPlayEvent(gf::GEV gev, unsigned int arg);  // slot 7

    int m_playEvent;  // gevPlayEvent sets 1 for GEV 0xE (the name is not the original's)
    unsigned char pad_24[0x4];
};
}  // namespace tl

#endif
