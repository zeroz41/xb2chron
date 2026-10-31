#include "classes/fw/ManagerObject.h"
#include "classes/fw/ManagerRegister.h"

namespace fw {

ManagerObject::ManagerObject() : m_flags(0) {
    mm::mtl::PtrSingleton<ManagerRegister>::sys()->regist(this);
}

ManagerObject::~ManagerObject() {
    mm::mtl::PtrSingleton<ManagerRegister>::sys()->remove(this);
}

}  // namespace fw
