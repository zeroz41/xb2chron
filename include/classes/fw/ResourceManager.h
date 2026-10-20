#ifndef CLASSES_FW_RESOURCEMANAGER_H
#define CLASSES_FW_RESOURCEMANAGER_H

#include "classes/fw/ManagerObject.h"

namespace fw { class UpdateInfo; }

namespace fw {
// a base of fw::ResourceManager no evidence names yet
class TUnk_B42AD8 {
public:
    virtual ~TUnk_B42AD8();
};
// table 0x7100B42A80; base at 0x10 unknown (TUnk_B42AD8)
class ResourceManager : public ::fw::ManagerObject, public TUnk_B42AD8 {
public:
    virtual ~ResourceManager();  // slot 0
    virtual void enterFinalizeApplet();  // slot 4
    virtual void update(fw::UpdateInfo const&);  // slot 8
};
}  // namespace fw

#endif
