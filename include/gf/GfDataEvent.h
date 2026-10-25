#ifndef GF_GFDATAEVENT_H
#define GF_GFDATAEVENT_H

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
};
}  // namespace gf

#endif
