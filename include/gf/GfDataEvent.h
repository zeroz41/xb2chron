#ifndef GF_GFDATAEVENT_H
#define GF_GFDATAEVENT_H

namespace gf { class SDataGame; }
namespace mm { class Vec3; }

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
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it lives in GfDataBlade's
    // unit among GfDataEvent's functions and takes an event. What it does: the first GfBdatChrBl row (getChrBlStart to
    // getChrBlEnd) whose getChrBlCreateEventID is the event, 0 for none. Caller: tl::TitleStatePlayEvent::enter.
    static unsigned int fn_710024F7CC(unsigned int event);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because fn_710024F430 passes
    // it the game data and an event. What it does: tests the GameFlag bit fn_710024F2DC sets for the event.
    static bool fn_710024F454(const SDataGame& game, unsigned int event);
    // whether game's saved events (SDataGame::m_savedEvents) hold event (GfGameUtil::setWatchedEvent calls it)
    static bool isSavedEvent(unsigned int event, const SDataGame& game);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it lives in GfDataBlade's
    // unit among GfDataEvent's functions (after isBladeCreateEvent) and takes an event. What it does: true for events
    // 20707..21210; else the MNU_EventTheater row (GfBdatShop, getMNU_EventTheaterStart to End) whose event_id is the
    // event and whether its category is 2 (false for none). Callers: tl::TitleStatePlayEvent::enter,
    // GfGameUtil::setWatchedEvent.
    static bool fn_710024F1B4(unsigned int event);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it lives in GfDataBlade's
    // unit among GfDataEvent's functions (after getBladeQuestDriver) and takes an event. What it does: for the first
    // MNU_EventTheater row whose event_id is the event, its blade_id when above 1000, else a blade id (1007..1109)
    // picked by the row's maincast (1..35, 0 for others); 0 when no row has the event.
    // Caller: tl::TitleStatePlayEvent::enter.
    static unsigned int fn_710024F720(unsigned int event);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it lives in GfDataBlade's
    // unit among GfDataEvent's functions and reads the event table fn_710024EBD8 picks, like getEventType. What it
    // does: the event row's float columns zoneX/Y/Z into pos and zoneR (degrees) as radians into angle; false when
    // there is no table. Caller: GfManager::startEventTheater.
    static bool fn_710024F844(mm::Vec3& pos, float& angle, unsigned int event);
};
}  // namespace gf

#endif
