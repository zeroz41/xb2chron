#ifndef CLASSES_FW_MODELMANAGER_H
#define CLASSES_FW_MODELMANAGER_H

#include "classes/fw/ManagerObject.h"

namespace fw { class UpdateInfo; }

namespace fw {
// a base of fw::ModelManager no evidence names yet
class TUnk_B42250 {
public:
    virtual ~TUnk_B42250();
};
// table 0x7100B421F8; base at 0x10 unknown (TUnk_B42250)
class ModelManager : public ::fw::ManagerObject, public TUnk_B42250 {
public:
    virtual ~ModelManager();  // slot 0
    virtual void update(fw::UpdateInfo const&, unsigned int);  // slot 8
};
}  // namespace fw

#endif
