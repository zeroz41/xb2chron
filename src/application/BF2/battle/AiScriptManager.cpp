#include "classes/ai/AiScriptManager.h"
#include "classes/gf/GfScriptManager.h"

namespace ai {

void AiScriptManager::init() {}

void AiScriptManager::destroy() {
    AiScriptManager* manager = mm::mtl::Singleton<AiScriptManager>::getPtr();
    for (long i = 0; i < SCRIPT_COUNT; ++i) {
        if (gf::GfScriptManager::get() != nullptr) {
            manager->m_scripts[i] = {};
            gf::GfScriptManager::destroyScript(FIRST_SCRIPT_ID + i);
        }
    }
}

void AiScriptManager::update(const fw::UpdateInfo&) {
    mm::mtl::Singleton<AiScriptManager>::getPtr()->_update();
}

void AiScriptManager::_update() {
    for (int i = 0; i < SCRIPT_COUNT; ++i) {
        Script& script = m_scripts[i];
        switch (script.state) {
        case PendingLoad:
            if (gf::GfScriptManager::get() != nullptr) {
                script.state = Loading;
                gf::GfScriptManager::loadScript(FIRST_SCRIPT_ID + i, script.name);
            }
            break;
        case Loading:
            if (gf::GfScriptManager::get() != nullptr && gf::GfScriptManager::isScriptLoaded(FIRST_SCRIPT_ID + i)) {
                if (!gf::GfScriptManager::isScriptActive(FIRST_SCRIPT_ID + i)) {
                    gf::GfScriptManager::startScript(FIRST_SCRIPT_ID + i);
                }
                script.state = Active;
            }
            break;
        case PendingDestroy:
            if (gf::GfScriptManager::get() != nullptr) {
                script = {};
                gf::GfScriptManager::destroyScript(FIRST_SCRIPT_ID + i);
            }
            break;
        case PendingReload:
            if (gf::GfScriptManager::get() != nullptr && gf::GfScriptManager::isScriptLoaded(FIRST_SCRIPT_ID + i)) {
                gf::GfScriptManager::destroyScript(FIRST_SCRIPT_ID + i);
                script.state = PendingLoad;
            }
            break;
        default:
            break;
        }
    }
}

AiScriptManager::~AiScriptManager() {}

}  // namespace ai
