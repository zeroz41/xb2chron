#include "classes/gf/IEventZone.h"
#include "mm/mtl/FixStr.h"
#include "classes/gf/GfFieldZone.h"
#include "classes/gf/GfFieldZoneScript.h"
#include "classes/gf/SCOM_SCRIPT.h"
#include "classes/gf/GfGameManager.h"
#include "gf/GfDataMap.h"
#include "classes/gf/GfScriptManager.h"
#include "classes/gf/GfAllocator.h"

namespace gf {

GfFieldZoneScript::~GfFieldZoneScript() {
    ;  // the original body has a statement the build compiles away; an empty one would drop the table store
}

void GfFieldZoneScript::build(const GfSetupParam& param) {
#line 42
    new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfFieldZoneScript(param);
}

void GfFieldZoneScript::destroy() {
    GfFieldZoneScript* script = get();
    script->finalize();
    delete script;
}

// execScript (0x7100282850) is not written yet: the original calls SCOM_SCRIPT::create in each path and keeps the
// map path's result in a register across its call; every plain form tried merges the two calls into one.

void GfFieldZoneScript::destroyScript() {
    SCOM_SCRIPT::create(1, nullptr, false);
}

bool GfFieldZoneScript::isExecScriptBusy() {
    if (GfScriptManager::isScriptLoadError(1)) {
        return false;
    }
    return !GfScriptManager::isScriptActive(1);
}

bool GfFieldZoneScript::isDestroyScriptBusy() {
    if (GfScriptManager::isScriptLoadError(1)) {
        return false;
    }
    return GfScriptManager::isScriptActive(1);
}

}  // namespace gf
