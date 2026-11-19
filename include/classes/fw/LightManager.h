#ifndef CLASSES_FW_LIGHTMANAGER_H
#define CLASSES_FW_LIGHTMANAGER_H

#include "classes/fw/ManagerObject.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/FixedArray.h"
#include "mm/mtl/IntrusiveList.h"

namespace fw { class UpdateInfo; }

namespace fw {
// table 0x7100B417E0; its base at 0x10 is its singleton (the destructor stores PtrSingleton<fw::LightManager>'s
// table 0x7100B41858 there and clears its instance)
class LightManager : public ::fw::ManagerObject, public ::mm::mtl::PtrSingleton< ::fw::LightManager> {
public:
    virtual ~LightManager();  // slot 0
    virtual void update(fw::UpdateInfo const&, unsigned int) {}  // slot 8
    // one list per layer (the symbols name mm::mtl::FixedArray<fw::LightManager::Group, 32>; Framework::createManager's
    // value-initialized new calls its out-of-line constructor, 0x18 bytes each, each an IntrusiveListBase). What the
    // lists hold is unknown: nothing in the module walks them
    class Group : public ::mm::mtl::IntrusiveListBase {};
    mm::mtl::FixedArray<Group, 32> m_groups;  // 0x18 (the object is 0x318 bytes: createManager's new)
};
}  // namespace fw

#endif
