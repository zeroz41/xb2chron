#ifndef CLASSES_FW_LAYERSETMANAGER_H
#define CLASSES_FW_LAYERSETMANAGER_H

#include "classes/fw/ManagerObject.h"

namespace fw {
// a base of fw::LayerSetManager no evidence names yet
class TUnk_B41DA0 {
public:
    virtual ~TUnk_B41DA0();
};
// table 0x7100B41D50; base at 0x10 unknown (TUnk_B41DA0)
class LayerSetManager : public ::fw::ManagerObject, public TUnk_B41DA0 {
public:
    virtual ~LayerSetManager();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
};
}  // namespace fw

#endif
