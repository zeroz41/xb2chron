#ifndef GF_GFDATAEVENT_H
#define GF_GFDATAEVENT_H

namespace gf {
// the events' data (functions, by its symbols; the code lives in the GfDataBlade unit)
class GfDataEvent {
public:
    // the event's type (GfFobjManager::gevPlayEvent tests it for 1)
    static int getEventType(unsigned int eventId);
};
}  // namespace gf

#endif
