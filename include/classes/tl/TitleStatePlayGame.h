#ifndef CLASSES_TL_TITLESTATEPLAYGAME_H
#define CLASSES_TL_TITLESTATEPLAYGAME_H

#include "classes/ai/State.h"
#include "classes/gf/IGfEvent.h"
#include <new>

namespace ai { class State; }
namespace fw { class UpdateInfo; }
namespace gf { enum GEV : int; }

namespace tl {
class TitleMain;

// table 0x7100B40610
class TitleStatePlayGame : public ::ai::State, public ::gf::IGfEvent {
public:
    // what TitleMain::initialize registers with its Fsm: the state made in a state buffer
    static ai::State* create(void* buffer) { return new (buffer) TitleStatePlayGame; }
    // inline: the deleting destructor only frees it
    virtual ~TitleStatePlayGame() {}  // slot 0
    inline virtual const char* getName() const;  // slot 2
    inline virtual void onEnter(void*, ai::State*);  // slot 3
    inline virtual void onLeave(void*, ai::State*);  // slot 4
    inline virtual void onStep(void*, void const*);  // slot 5
    void enter(TitleMain* title, ai::State* prev);
    virtual void gevPlayEvent(gf::GEV gev, unsigned int arg);  // slot 7

    int m_playEvent;  // gevPlayEvent sets 2 for GEV 0xE, 0 for GEV 0xD (the name is not the original's)
    unsigned char pad_24[0x4];
};
// Placeholder name: nothing names it (no symbol). A free function because it takes nothing and reaches the title
// through TitleMain::sys(); TitleStatePlayGame::enter calls it for menu result 5. What it does: clears the sound UI
// option flags A..C of the game's and the title's options unless fn_71002A9E68 or GfGameUtilSaveData::fn_71002EDC78
// holds, and resets their m_keyD above 1 to 0 unless the game is cleared (isClearGame / fn_71002EDCEC).
void fn_7100154638();
}  // namespace tl

#endif
