#ifndef CLASSES_FW_ASSETMANAGER_H
#define CLASSES_FW_ASSETMANAGER_H

#include "classes/fw/ManagerObject.h"

namespace fw { class UpdateInfo; }

namespace fw {
// a base of fw::AssetManager no evidence names yet
class TUnk_B40F00 {
public:
    virtual ~TUnk_B40F00();
};
// table 0x7100B40EA8; base at 0x10 unknown (TUnk_B40F00)
class AssetManager : public ::fw::ManagerObject, public TUnk_B40F00 {
public:
    virtual ~AssetManager();  // slot 0
    virtual const char* getName() const;  // slot 5
    virtual void update(fw::UpdateInfo const&);  // slot 8
};
}  // namespace fw

#endif
