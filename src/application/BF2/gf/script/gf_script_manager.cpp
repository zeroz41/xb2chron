#include "classes/fw/ScriptManager.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfScriptManager.h"

namespace gf {

void GfScriptManager::initialize(const GfSetupParam& param) {
    fw::ScriptManager* scripts = fw::ScriptManager::get();
    scripts->createScript(0, getAllocator(ALLOCATOR(2)), 0x2000);
    scripts->createScript(1, getAllocator(ALLOCATOR(2)), 0x2000);
    scripts->createScript(2, getAllocator(ALLOCATOR(2)), 0x100000);
    scripts->createScript(3, getAllocator(ALLOCATOR(2)), 0x2000);
    for (int id = 4; id < 36; id++) {
        scripts->createScript(id, getAllocator(ALLOCATOR(2)), 0x2000);
    }
    for (int id = 36; id < 68; id++) {
        scripts->createScript(id, getAllocator(ALLOCATOR(2)), 0x4000);
    }
    scripts->createScript(68, getAllocator(ALLOCATOR(2)), 0x2000);
    scripts->createScript(69, getAllocator(ALLOCATOR(2)), 0x2000);
    scripts->createScript(70, getAllocator(ALLOCATOR(2)), 0x2000);
    m_initialized = true;
}

GfScriptManager::~GfScriptManager() {}

void GfScriptManager::build(const GfSetupParam& param) {
#line 59
    new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfScriptManager(param);
}

void GfScriptManager::destroy() {
    GfScriptManager* manager = get();
    manager->finalize();
    delete manager;
}

void GfScriptManager::finalize() {
    fw::ScriptManager* scripts = fw::ScriptManager::get();
    scripts->destroyScript(68, true);
    for (int id = 36; id < 68; id++) {
        scripts->destroyScript(id, true);
    }
    for (int id = 4; id < 36; id++) {
        scripts->destroyScript(id, true);
    }
    scripts->destroyScript(3, true);
    scripts->destroyScript(2, true);
    scripts->destroyScript(1, true);
    scripts->destroyScript(0, true);
    scripts->destroyScript(69, true);
    scripts->destroyScript(70, true);
    m_initialized = false;
}

void GfScriptManager::loadScript(unsigned int id, const char* name) {
    fw::ScriptManager* scripts = fw::ScriptManager::get();
    scripts->destroyScript(id, false);
    scripts->loadScript(id, name, ml::FILE_PRIO(7));
}

bool GfScriptManager::isScriptLoadError(unsigned int id) {
    const fw::ScriptManager* scripts = fw::ScriptManager::get();
    return scripts->getScript(id).isLoadErr();
}

void GfScriptManager::startScript(unsigned int id) {
    fw::ScriptManager::get()->getScript(id).start();
}

void GfScriptManager::destroyScript(unsigned int id) {
    fw::ScriptManager::get()->destroyScript(id, false);
}

bool GfScriptManager::isScriptWaitStart(unsigned int id) {
    const fw::ScriptManager* scripts = fw::ScriptManager::get();
    if (scripts->getScript(id).isActive()) {
        return false;
    }
    return scripts->isScriptLoaded(id);
}

bool GfScriptManager::isScriptLoaded(unsigned int id) {
    return fw::ScriptManager::get()->isScriptLoaded(id);
}

bool GfScriptManager::isScriptActive(unsigned int id) {
    const fw::ScriptManager* scripts = fw::ScriptManager::get();
    return scripts->getScript(id).isActive();
}

bool GfScriptManager::isScriptFinish(unsigned int id) {
    const fw::ScriptManager* scripts = fw::ScriptManager::get();
    return scripts->getScript(id).isFinish();
}

}  // namespace gf
