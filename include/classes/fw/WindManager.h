#ifndef CLASSES_FW_WINDMANAGER_H
#define CLASSES_FW_WINDMANAGER_H

#include "classes/fw/ManagerObject.h"

namespace fw { class UpdateInfo; }
namespace fw { class WindProbe; }

namespace fw {
// a base of fw::WindManager no evidence names yet
class TUnk_B434F8 {
public:
    virtual ~TUnk_B434F8();
};
// table 0x7100B434A0; base at 0x10 unknown (TUnk_B434F8)
class WindManager : public ::fw::ManagerObject, public TUnk_B434F8 {
public:
    virtual ~WindManager();  // slot 0
    virtual void initialize();  // slot 2
    virtual void getName() const;  // slot 5
    virtual void update(fw::UpdateInfo const&);  // slot 8
    void addProbe(WindProbe* pProbe);
    void removeProbe(WindProbe* pProbe);
};
}  // namespace fw

#endif
