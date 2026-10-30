#include "classes/gf/IEventZone.h"
#include "mm/mtl/FixedQueue.h"
#include "classes/gf/GfFieldZone.h"
#include "classes/gf/GfFieldZoneSe.h"
#include "classes/gf/GfFieldZoneScript.h"
#include "classes/gf/GfAllocator.h"

namespace gf {

GfFieldZone::~GfFieldZone() {}

void GfFieldZone::initialize(const GfSetupParam& param) {
    GfFieldZoneSe::build(param);
    GfFieldZoneScript::build(param);
    m_initialized = true;
}

void GfFieldZone::build(const GfSetupParam& param) {
#line 40
    new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfFieldZone(param);
}

void GfFieldZone::destroy() {
    GfFieldZone* zone = get();
    zone->finalize();
    delete zone;
}

void GfFieldZone::finalize() {
    GfFieldZoneScript::destroy();
    GfFieldZoneSe::destroy();
    m_initialized = false;
}

void GfFieldZone::update(const fw::UpdateInfo& info) {}

void GfFieldZone::addEvent(IEventZone* event) {
    GfFieldZone* zone = get();
    if (mm::mtl::find(zone->m_events.begin(), zone->m_events.end(), event) == zone->m_events.end()) {
        zone->m_events.push_back(event);
    }
}

void GfFieldZone::removeEvent(IEventZone* event) {
    GfFieldZone* zone = get();
    mm::mtl::FixedQueue<IEventZone*, 16>::iterator it =
        mm::mtl::find(zone->m_events.begin(), zone->m_events.end(), event);
    if (it != zone->m_events.end()) {
        zone->m_events.erase(it);
    }
}

void GfFieldZone::gevMapjump(GEV gev, const MapjumpCallbackInfo& info) {
    if (gev == GEV(2)) {
        GfFieldZoneScript::destroyScript();
    }
}

}  // namespace gf
