#ifndef CLASSES_FW_NAVIMANAGER_H
#define CLASSES_FW_NAVIMANAGER_H

#include "classes/fw/ManagerObject.h"

namespace fw {
// a base of fw::NaviManager no evidence names yet
class TUnk_B42460 {
public:
    virtual ~TUnk_B42460();
};
// table 0x7100B42410; base at 0x10 unknown (TUnk_B42460)
class NaviManager : public ::fw::ManagerObject, public TUnk_B42460 {
public:
    virtual ~NaviManager();  // slot 0
    virtual bool initialize();  // slot 2
    virtual bool finalize();  // slot 3
};
}  // namespace fw

#endif
