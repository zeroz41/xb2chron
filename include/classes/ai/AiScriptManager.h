#ifndef CLASSES_AI_AISCRIPTMANAGER_H
#define CLASSES_AI_AISCRIPTMANAGER_H

#include "classes/mm/mtl/Singleton.h"
#include <string.h>

namespace fw { class UpdateInfo; }

namespace ai {
// table 0x7100B3A3C0; Singleton<AiScriptManager>::getPtr keeps 32 script slots.
class AiScriptManager {
public:
    enum { SCRIPT_COUNT = 32, FIRST_SCRIPT_ID = 36 };
    // State and field names describe the transitions; the original names are unknown.
    enum ScriptState { Empty, PendingLoad, Loading, Active, PendingDestroy, PendingReload };
    struct Script {
        const char* name;
        int users;
        ScriptState state;
    };

    AiScriptManager() { memset(m_scripts, 0, sizeof(m_scripts)); }
    virtual ~AiScriptManager();  // slot 0
    static void init();
    static void destroy();
    static void update(const fw::UpdateInfo& info);
    // the named script started for one more user, and ended for one fewer
    static bool start(const char* name);
    static bool end(const char* name);
    void _update();

private:
    Script m_scripts[SCRIPT_COUNT];
};
}
#endif
