#ifndef CLASSES_FW_MOVIEMANAGER_H
#define CLASSES_FW_MOVIEMANAGER_H

#include "classes/fw/ManagerObject.h"
#include "classes/ml/IWorkBackground.h"

namespace fw {
// a base of fw::MovieManager no evidence names yet
class TUnk_B42318 {
public:
    virtual ~TUnk_B42318();
};
// table 0x7100B422C0; base at 0x10 unknown (TUnk_B42318)
class MovieManager : public ::fw::ManagerObject, public TUnk_B42318, public ::ml::IWorkBackground {
public:
    virtual ~MovieManager();  // slot 0
    virtual void getName() const;  // slot 5
    virtual void bkgHomeMenu(bool);  // slot 8
};
}  // namespace fw

#endif
