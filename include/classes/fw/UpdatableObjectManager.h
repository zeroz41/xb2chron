#ifndef CLASSES_FW_UPDATABLEOBJECTMANAGER_H
#define CLASSES_FW_UPDATABLEOBJECTMANAGER_H

#include "classes/fw/ManagerObject.h"

namespace fw { class UpdateInfo; }

namespace fw {
// a base of fw::UpdatableObjectManager no evidence names yet
class TUnk_B42570 {
public:
    virtual ~TUnk_B42570();
};
// table 0x7100B42510; base at 0x10 unknown (TUnk_B42570)
class UpdatableObjectManager : public ::fw::ManagerObject, public TUnk_B42570 {
public:
    virtual ~UpdatableObjectManager();  // slot 0
    virtual bool initialize();  // slot 2
    virtual bool finalize();  // slot 3
    virtual void getName() const;  // slot 5
    virtual void update(fw::UpdateInfo const&, unsigned int);  // slot 8
    virtual void tail(fw::UpdateInfo const&);  // slot 9
};
}  // namespace fw

#endif
