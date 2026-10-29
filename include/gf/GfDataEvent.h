#ifndef GF_GFDATAEVENT_H
#define GF_GFDATAEVENT_H

namespace gf { class SDataGame; }

namespace gf {
// the events' data (functions, by its symbols; the code lives in the GfDataBlade unit)
class GfDataEvent {
public:
    // the event's type (GfFobjManager::gevPlayEvent tests it for 1)
    static int getEventType(unsigned int eventId);
    static bool isBladeCreateEvent(unsigned int event);
    // the script GfPlayComAfterEventScript runs after the event, and the start id it sets first
    static int getEventAfterScriptStartID(unsigned int event);
    static const char* getEventAfterScriptName(unsigned int event);
    static bool isSaveScenarioEvent(unsigned int event);  // one of 213 scenario events
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its callers are
    // getEventType, getEventAfterScriptStartID and getEventAfterScriptName, in this unit, and it takes their event.
    // What it does: the GfDataBdat table id of the event table whose id range holds the event (it walks GfDataBdat's
    // table ids from 0x7100C33A40 on, testing Bdat::getIdTop/getIdCount of each).
    static unsigned int fn_710024EBD8(unsigned int event);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it reads the event table
    // that fn_710024EBD8 picks for the event, like getEventType. What it does: the event row's 16-bit "scenarioFlag"
    // (tl::TitleStatePlayEvent::enter calls it).
    static unsigned int fn_710024ED1C(unsigned int event);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it reads the event table
    // that fn_710024EBD8 picks for the event, like getEventType. What it does: whether the event row's 8-bit
    // "noRetarget" is set (gf::fn_71002DF39C and fn_71002DF624 call it).
    static bool fn_710024F910(unsigned int event);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its address is in
    // GfDataBlade's unit among GfDataEvent's functions (after isSaveScenarioEvent). What it does: fn_710024F2DC on the
    // game data (GfGameUtil::setWatchedEvent calls it).
    static void fn_710024F2B8(unsigned int event);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because fn_710024F2B8 passes
    // it the game data and an event. What it does: when the event (0x5461 read as 0x5462) is an MNU_EventTheater row,
    // sets a GameFlag bit (row's flag_index + 0xB6C2 or 0xB78B) in the game data's local flags (+0xFBBC4).
    static void fn_710024F2DC(SDataGame& game, unsigned int event);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its address is in
    // GfDataBlade's unit among GfDataEvent's functions. What it does: fn_710024F454 on the game data (gf::isUnuseBlade calls it).
    static bool fn_710024F430(unsigned int event);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because fn_710024F430 passes
    // it the game data and an event. What it does: tests the GameFlag bit fn_710024F2DC sets for the event.
    static bool fn_710024F454(const SDataGame& game, unsigned int event);
};
}  // namespace gf

#endif
