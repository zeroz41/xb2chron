#ifndef CLASSES_FW_SCRIPTMANAGER_H
#define CLASSES_FW_SCRIPTMANAGER_H

#include "classes/fw/ManagerObject.h"
#include "classes/fw/ScriptInfo.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "classes/ml/IWorkEvent.h"
#include "mm/mtl/Array.h"
#include "mm/mtl/FixStr.h"

namespace fw { class UpdateInfo; }
namespace fw { class ScriptManager; }
namespace ml { enum FILE_PRIO : int; }
namespace mm { namespace mtl { class IAllocator; } }

namespace fw {
// what ScriptManager::notifyEvent hands its listeners: a script's id and what happened to it (ScriptInfo passes
// 0 when its read failed, 1 when it read, 2 when it started, 3 when it finished; the names are not the original's)
struct ScriptEventParam {
    enum State : int {};

    int id;
    State state;
};

// table 0x7100B42BC8; the base at 0x10 is mm::mtl::PtrSingleton<fw::ScriptManager> (1.0.0's constructor installs
// its table there and stores this in its s_instance)
class ScriptManager : public ::fw::ManagerObject,
                      public ::mm::mtl::PtrSingleton< ::fw::ScriptManager>,
                      public ::ml::IWorkEvent {
public:
    virtual ~ScriptManager();  // slot 0
    virtual bool initialize();  // slot 2
    virtual bool finalize();  // slot 3
    virtual void update(fw::UpdateInfo const&);  // slot 8
    void createScript(int id, mm::mtl::IAllocator* allocator, unsigned long size);
    void destroyScript(int id, bool);
    bool isScriptLoaded(int id) const;
    void loadScript(int id, const char* name, ml::FILE_PRIO prio);
    // tells the listeners about a script (ScriptInfo's reads, starts and ends)
    void notifyEvent(int id, ScriptEventParam::State state);
    // the script under an id (inline: gf::GfScriptManager's accessors; the name is not the original's)
    ScriptInfo& getScript(int id) { return m_scripts[id]; }
    const ScriptInfo& getScript(int id) const { return m_scripts[id]; }

    mm::mtl::Array<ScriptInfo> m_scripts;  // reserve(size) in the constructor; createScript initializes one
    static mm::mtl::FixStr<256> m_rootPath;  // setScriptPath stores it, makeFullPath reads it
};
}  // namespace fw

#endif
