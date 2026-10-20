#ifndef CLASSES_FW_PADMANAGER_H
#define CLASSES_FW_PADMANAGER_H

#include "classes/fw/ManagerObject.h"
#include "classes/ml/DevGraphCB.h"

namespace fw { class UpdateInfo; }

namespace fw {
// a base of fw::PadManager no evidence names yet
class TUnk_B426E0 {
public:
    virtual ~TUnk_B426E0();
};
// table 0x7100B42678; base at 0x10 unknown (TUnk_B426E0)
class PadManager : public ::fw::ManagerObject, public TUnk_B426E0, public ::ml::DevGraphCB {
public:
    virtual ~PadManager();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void getName() const;  // slot 5
    virtual void isInitialized() const;  // slot 6
    virtual void debugDraw(int, int);  // slot 8
    virtual void update(fw::UpdateInfo const&);  // slot 9
    virtual void viBeginFrame();  // slot 10
};
}  // namespace fw

#endif
