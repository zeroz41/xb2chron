#ifndef CLASSES_GF_GFGAMEPAD_H
#define CLASSES_GF_GFGAMEPAD_H

#include "classes/gf/GfEvent.h"
#include "classes/gf/IGfEvent.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "fw/PadData.h"
#include "fw/PadRelay.h"
#include "mm/mtl/FixedVector.h"

namespace gf { class GfGamePad; }
namespace gf { class GfSetupParam; }
namespace fw { class UpdateInfo; }
namespace gf { enum EXEC_STATE : int; }
namespace gf { enum GF_STATE : int; }

namespace gf {
// a debug pad input (1.0.0's GfGamePad::setInterruptPadOnForDebug takes one; its update maps each through a table to
// a fw::PadActKey)
enum DWPAD : unsigned int;

// table 0x7100B55158
class GfGamePad : public ::mm::mtl::PtrSingleton< ::gf::GfGamePad>, public ::gf::IGfEvent {
public:
    // inline: 3.0.1's symbols have no copy (1.0.0's build inlines it too: it registers the listener, then binds the
    // pad's actions)
    GfGamePad(const GfSetupParam& param) : m_initialized(false), m_eventPause(false), pad_1a0(0) {
        initialize(param);
    }
    virtual ~GfGamePad();  // slot 0
    // the player's pad data: the manager's at 0x50, else &fw::PadManager::getControlPadData(0) (a pointer: GfMenuMnagerPadRead::uiGetControlPad returns a reference to it without a tail call)
    static const fw::PadData* getPadPlayer();
    virtual void gevExecState(gf::EXEC_STATE);  // slot 2
    virtual void gevGameState(gf::GF_STATE, gf::GF_STATE);  // slot 3

    static void build(const GfSetupParam& param);
    static void destroy();
    static void update(const fw::UpdateInfo& info);
    static bool isEventPause();
    // rebinds the pad's actions for the current mode (debug or scenario game: event pause during an event or a
    // talk, else the menus; theater: event pause only)
    void changePadInputMode();
    // 1.0.0's (inline in 3.0.1)
    void initialize(const GfSetupParam&) {
        GfEvent::addEventCallback(this);
        m_initialized = true;
        changePadInputMode();
    }
    // 1.0.0's (inline in 3.0.1)
    void finalize() {
        m_padRelay.unbind();
        GfEvent::removeEventCallback(this);
        m_initialized = false;
    }
    // 1.0.0's (inline in 3.0.1)
    void clearUniqParams() {
        m_eventPause = false;
    }
    // 1.0.0's name (same code): the player held the escape buttons for 151 frames, so the party leader dies (and,
    // in 3.0.1, a landmark is set first in one place)
    void checkEmergencyEscape();
    void eventInGameEventPause();
    void eventInGameOpenMainMenu();
    void eventInGameOpenSystemMenu();
    void eventInGameOpenSkipTravelMenu();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because changePadInputMode binds
    // it to the "call_party" action with this object (when GfGameManager::fn_71002A9E68 holds). What it does: when
    // the main menu may open and GfMenuManager::fn_710035A6CC/fn_710035A6F8 hold, the controlled mover's alpha life
    // is at least 1 and at least two of party 0-2's first drivers are set, calls GfPlayFactory::fn_7100321258.
    void fn_71002B6440();

    bool m_initialized;  // isInitialized's (1.0.0): set while the listener is registered (the name is not the original's)
    bool m_eventPause;   // isEventPause's: the "pause_event" action came this frame (the name is not the original's)
    unsigned char pad_12[0x6];
    fw::PadRelay m_padRelay;  // the name is not the original's
    fw::PadData m_padData;    // the control pad's data copied each update; getPadPlayer's (the name is not the original's)
    // setInterruptPadOnForDebug's (1.0.0; nothing adds to it in 3.0.1): the name is not the original's
    mm::mtl::FixedVector<DWPAD, 64> m_interruptPads;
    unsigned int pad_1a0;  // new in 3.0.1: the constructor zeroes it
    unsigned char m_escapeCount;  // checkEmergencyEscape's frame count (the name is not the original's)
};
}  // namespace gf

#endif
