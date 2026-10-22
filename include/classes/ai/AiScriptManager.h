#ifndef CLASSES_AI_AISCRIPTMANAGER_H
#define CLASSES_AI_AISCRIPTMANAGER_H

namespace fw { class UpdateInfo; }

namespace ai {
// table 0x7100B3A3C0; a mm::mtl::Singleton (_ZZN2mm3mtl9SingletonIN2ai15AiScriptManagerEE6getPtrEvE10s_instance)
class AiScriptManager {
public:
    virtual ~AiScriptManager();  // slot 0
    static void init();
    static void destroy();
    static void update(const fw::UpdateInfo& info);
    // the named script started for one more user, and ended for one fewer
    static bool start(const char* name);
    static bool end(const char* name);
};
}  // namespace ai

#endif
