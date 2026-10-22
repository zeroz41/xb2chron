#ifndef CLASSES_FW_BDATMANAGER_H
#define CLASSES_FW_BDATMANAGER_H

#include "classes/fw/ManagerObject.h"

namespace fw { class UpdateInfo; }

namespace fw {
// a base of fw::BdatManager no evidence names yet
class TUnk_B40F98 {
public:
    virtual ~TUnk_B40F98();
};
// table 0x7100B40F40; base at 0x10 unknown (TUnk_B40F98)
class BdatManager : public ::fw::ManagerObject, public TUnk_B40F98 {
public:
    virtual ~BdatManager();  // slot 0
    virtual bool initialize();  // slot 2
    virtual bool finalize();  // slot 3
    virtual void getName() const;  // slot 5
    virtual void update(fw::UpdateInfo const&);  // slot 8
};
}  // namespace fw

#endif
