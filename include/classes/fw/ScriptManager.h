#ifndef CLASSES_FW_SCRIPTMANAGER_H
#define CLASSES_FW_SCRIPTMANAGER_H

#include "classes/fw/ManagerObject.h"
#include "classes/ml/IWorkEvent.h"

namespace fw { class UpdateInfo; }

namespace fw {
// a base of fw::ScriptManager no evidence names yet
class TUnk_B42C20 {
public:
    virtual ~TUnk_B42C20();
};
// table 0x7100B42BC8; base at 0x10 unknown (TUnk_B42C20)
class ScriptManager : public ::fw::ManagerObject, public TUnk_B42C20, public ::ml::IWorkEvent {
public:
    virtual ~ScriptManager();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update(fw::UpdateInfo const&);  // slot 8
};
}  // namespace fw

#endif
