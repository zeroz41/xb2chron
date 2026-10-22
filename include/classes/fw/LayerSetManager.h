#ifndef CLASSES_FW_LAYERSETMANAGER_H
#define CLASSES_FW_LAYERSETMANAGER_H

#include "classes/fw/ManagerObject.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace fw { class LayerSetManager; }
namespace layer { class LayerManager; }

namespace fw {
// table 0x7100B41D50; its PtrSingleton<LayerSetManager> at 0x10 (the constructor stores that table there and asserts
// singleton.h's get()==0)
class LayerSetManager : public ::fw::ManagerObject, public ::mm::mtl::PtrSingleton< ::fw::LayerSetManager> {
public:
    LayerSetManager();
    virtual ~LayerSetManager();  // slot 0
    virtual bool initialize();  // slot 2
    virtual bool finalize();  // slot 3
    void tail();

    layer::LayerManager* m_layerManager;  // initialize creates it, finalize deletes it; the name is not the original's
};
}  // namespace fw

#endif
