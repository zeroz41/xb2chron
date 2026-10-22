#include "classes/gf/IEventZone.h"
#include "mm/mtl/FixedQueue.h"
#include "classes/gf/GfFieldZone.h"
#include "classes/gf/GfFieldZoneSe.h"
#include "classes/gf/GfAllocator.h"

namespace gf {

GfFieldZoneSe::~GfFieldZoneSe() {
    ;  // the original body has a statement the build compiles away; an empty one would drop the table store
}

void GfFieldZoneSe::build(const GfSetupParam& param) {
#line 39
    new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfFieldZoneSe(param);
}

void GfFieldZoneSe::initialize(const GfSetupParam& param) {
    m_initialized = true;
    GfFieldZone::addEvent(this);
}

void GfFieldZoneSe::destroy() {
    GfFieldZoneSe* se = get();
    se->finalize();
    delete se;
}

void GfFieldZoneSe::finalize() {
    GfFieldZone::removeEvent(this);
    m_initialized = false;
}

}  // namespace gf
