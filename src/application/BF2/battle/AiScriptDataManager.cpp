#include "classes/ai/AiScriptDataManager.h"
#include "classes/gf/GfDataBdat.h"
#include "plugin/Bdat.h"

namespace ai {

void AiScriptDataManager::init() {
    getPtr()->_init();
}

void AiScriptDataManager::_init() {
    unsigned char* fp = gf::GfDataBdat::getFP(0);
    int top = Bdat::getIdTop(fp);
    int count = Bdat::getIdCount(fp);
    int num = count;
    if (num > 511) {
        num = 512;
    }
    for (int i = 0; i < num; i++) {
        const char* name = reinterpret_cast<const char*>(Bdat::getValCheck(fp, "Script", top + i, 7));
        if (name != nullptr && *name != '\0') {
            ScriptData data;
            data.m_id = top + i;
            data.m_name = name;
            m_list.push_back(data);
        }
    }
}

void AiScriptDataManager::destroy() {
    getPtr()->m_list.clear();
}

void AiScriptDataManager::update(const fw::UpdateInfo& info) {}

const char* AiScriptDataManager::getScriptName(int id) {
    AiScriptDataManager* manager = getPtr();
    for (ScriptList::iterator it = manager->m_list.begin(); it != manager->m_list.end(); ++it) {
        ScriptData& data = *it;
        if (data.m_id == id) {
            return data.m_name;
        }
    }
    return nullptr;
}

AiScriptDataManager::~AiScriptDataManager() {}

}  // namespace ai
