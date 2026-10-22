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

// addEvent (0x71002824F8) is not matched yet

// removeEvent (0x710028259C) is not matched yet

void GfFieldZone::gevMapjump(GEV gev, const MapjumpCallbackInfo& info) {
    if (gev == GEV(2)) {
        GfFieldZoneScript::destroyScript();
    }
}

}  // namespace gf
