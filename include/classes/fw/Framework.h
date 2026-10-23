#ifndef CLASSES_FW_FRAMEWORK_H
#define CLASSES_FW_FRAMEWORK_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "mtl/AllocHandle.h"

namespace fw { class IPauseTrigger; }
namespace fw { class UpdateInfo; }
namespace fw { class Framework; }
namespace ml { class Scn; }
namespace mm { namespace mtl { class IAllocator; } }

namespace fw {
// table 0x7100B41668
class Framework : public ::mm::mtl::PtrSingleton< ::fw::Framework> {
public:
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member: its code is in the framework's unit and
    // GfManager::fn_710032A1FC calls it on PtrSingleton<fw::Framework>'s instance. What it does: stores its bool at 0x459
    void fn_71001836D0(bool flag);
    static void addPauseCallback(IPauseTrigger* trigger);
    static void removePauseCallback(IPauseTrigger* trigger);
    // Placeholder name: nothing in 1.0.0 names it (its GfManager::postUpdate calls neither). A member: this is the
    // framework (GfManager::postUpdate passes PtrSingleton<fw::Framework>'s instance). What it does: signals the event
    // wait at 0x3F8 of the framework (EventWait::setSignal(true)); GfManager::postUpdate passes the update info, unused
    void fn_710018369C(const fw::UpdateInfo& info);
    // Placeholder name: as fn_710018369C. What it does: waits while the event wait at 0x3F8 is signalled (loops on
    // EventWait::isSignal); GfManager::postUpdate calls it after the menus' postUpdate
    void fn_71001836A8();
    virtual ~Framework();  // slot 0
    static mm::mtl::IAllocator* getAllocator();
    static mtl::ALLOC_HANDLE getMemHandle();  // the memory resources are made in (ResourceManager::getMemSYS)
    static unsigned int getFrameCount();
    unsigned char pad_8[0x50];
    ml::Scn* m_scn;  // what LayerSetManager gives layer::LayerManager; the name is not the original's
};
}  // namespace fw

#endif
