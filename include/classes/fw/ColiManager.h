#ifndef CLASSES_FW_COLIMANAGER_H
#define CLASSES_FW_COLIMANAGER_H

#include "classes/fw/ManagerObject.h"

namespace fw { class ColiObject; }

namespace fw {
// a base of fw::ColiManager no evidence names yet
class TUnk_B410C0 {
public:
    virtual ~TUnk_B410C0();
};
// table 0x7100B41070; base at 0x10 unknown (TUnk_B410C0)
class ColiManager : public ::fw::ManagerObject, public TUnk_B410C0 {
public:
    class Impl;
    virtual ~ColiManager();  // slot 0
    virtual bool initialize();  // slot 2
    virtual bool finalize();  // slot 3
    void registObject(ColiObject* object);
    void removeObject(ColiObject* object);
    // what its Impl holds at 0x20; its type is not known yet: its one caller, ColiObject's destructor, discards it
    void* getInterface();
    // the framework's per-frame calls (Framework::update, postUpdate, tail)
    void update();
    void postUpdate();
    void tail();
};
}  // namespace fw

#endif
