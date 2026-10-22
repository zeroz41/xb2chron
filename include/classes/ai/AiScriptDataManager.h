#ifndef CLASSES_AI_AISCRIPTDATAMANAGER_H
#define CLASSES_AI_AISCRIPTDATAMANAGER_H

#include "classes/mm/mtl/Singleton.h"
#include "mm/mtl/FixedList.h"

namespace fw { class UpdateInfo; }

namespace ai {
// table 0x7100B3A3A0; the AI scripts' names by id, from BDAT table 0's Script column
class AiScriptDataManager : public ::mm::mtl::Singleton< ::ai::AiScriptDataManager> {
public:
    // a row with a script (the name is not the original's)
    struct ScriptData {
        int m_id;            // its row id
        const char* m_name;  // its Script column
    };

    typedef mm::mtl::FixedList<ScriptData, 512> ScriptList;  // the name is not the original's

    AiScriptDataManager() {}
    virtual ~AiScriptDataManager();  // slot 0

    static void init();
    static void destroy();
    static void update(const fw::UpdateInfo& info);
    static const char* getScriptName(int id);  // null for an id without a script

    void _init();

    ScriptList m_list;  // the name is not the original's
};
}  // namespace ai

#endif
