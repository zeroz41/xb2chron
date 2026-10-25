#ifndef CLASSES_IDCOLI_IDCOLIOBJGRDCHAR_H
#define CLASSES_IDCOLI_IDCOLIOBJGRDCHAR_H

#include "classes/idcoli/IDColiObj.h"

namespace idcoli {
// table 0x7100B7F5E8
class IDColiObjGrdChar : public ::idcoli::IDColiObj {
public:
    IDColiObjGrdChar();
    virtual ~IDColiObjGrdChar();  // slot 0
    virtual void update();  // slot 4
    unsigned char pad_50[0x40];  // 0x90 bytes: IDColiManager::createColiGrdChar allocates it so
};
}  // namespace idcoli

#endif
