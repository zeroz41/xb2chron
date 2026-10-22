#ifndef CLASSES_FW_MANAGERREGISTER_H
#define CLASSES_FW_MANAGERREGISTER_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/FixedVector.h"

namespace fw { class ManagerObject; }
namespace fw { class ManagerRegister; }

namespace fw {
// table 0x7100B41E30
class ManagerRegister : public ::mm::mtl::PtrSingleton< ::fw::ManagerRegister> {
public:
    ManagerRegister();
    virtual ~ManagerRegister();  // slot 0
    void regist(ManagerObject* object);
    void remove(ManagerObject* object);
    bool initialize();  // initializes the objects not initialized yet, true when there were none
    bool finalize();  // finalizes them from the last, true when there was none to finalize
    void enterFinalizeApplet();

    mm::mtl::FixedVector<ManagerObject*, 256> m_objects;  // regist's; the name is not the original's
};
}  // namespace fw

#endif
