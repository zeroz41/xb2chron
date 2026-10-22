#ifndef CLASSES_FW_MESSAGEMANAGER_H
#define CLASSES_FW_MESSAGEMANAGER_H

#include "classes/fw/ManagerObject.h"

namespace fw { class UpdateInfo; }

namespace fw {
// a base of fw::MessageManager no evidence names yet
class TUnk_B42128 {
public:
    virtual ~TUnk_B42128();
};
// table 0x7100B420C8; base at 0x10 unknown (TUnk_B42128)
class MessageManager : public ::fw::ManagerObject, public TUnk_B42128 {
public:
    class Impl;
    virtual ~MessageManager();  // slot 0
    virtual bool initialize();  // slot 2
    virtual bool finalize();  // slot 3
    virtual const char* getName() const;  // slot 5
    virtual void update(fw::UpdateInfo const&);  // slot 8
    virtual void tail(fw::UpdateInfo const&);  // slot 9
};
}  // namespace fw

#endif
