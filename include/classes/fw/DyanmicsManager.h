#ifndef CLASSES_FW_DYANMICSMANAGER_H
#define CLASSES_FW_DYANMICSMANAGER_H

#include "classes/fw/ManagerObject.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace fw { class DynamicsColObjUpdaterInterface; }
namespace fw { class DynamicsUpdaterInterface; }
namespace fw { class UpdateInfo; }

namespace fw {
// table 0x7100B41230; its base at 0x10 is its singleton (1.0.0 names PtrSingleton<fw::DyanmicsManager>'s
// destructors)
class DyanmicsManager : public ::fw::ManagerObject, public ::mm::mtl::PtrSingleton< ::fw::DyanmicsManager> {
public:
    virtual ~DyanmicsManager();  // slot 0
    virtual const char* getName() const;  // slot 5
    virtual void update(fw::UpdateInfo const&);  // slot 8
    void addUpdater(unsigned int layer, DynamicsUpdaterInterface& updater);
    void removeUpdater(unsigned int layer, DynamicsUpdaterInterface& updater);
    void addColUpdater(unsigned int layer, DynamicsColObjUpdaterInterface& updater);
    void removeColUpdater(unsigned int layer, DynamicsColObjUpdaterInterface& updater);
};
}  // namespace fw

#endif
