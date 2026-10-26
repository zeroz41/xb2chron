#ifndef CLASSES_FW_COLIMANAGER_H
#define CLASSES_FW_COLIMANAGER_H

#include "classes/fw/ManagerObject.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/UniquePtr.h"

namespace fw { class ColiObject; }
namespace idcoli { class IDColiManager; }
namespace mm { namespace mtl { class IAllocator; } }

namespace fw {
// table 0x7100B41070; PtrSingleton<ColiManager>'s table 0x7100B41120 at 0x10 (the constructor installs it)
class ColiManager : public ::fw::ManagerObject, public ::mm::mtl::PtrSingleton< ::fw::ColiManager> {
public:
    // the registered objects, their contacts and the collision system (coli_manager.cpp defines it; the constructor
    // makes it in allocator's memory)
    class Impl;

    ColiManager(mm::mtl::IAllocator* allocator, unsigned int count);
    virtual ~ColiManager();  // slot 0
    virtual bool initialize();  // slot 2
    virtual bool finalize();  // slot 3
    void registObject(ColiObject* object);
    void removeObject(ColiObject* object);
    // its Impl's collision system (ColiObject's destructor discards it)
    idcoli::IDColiManager* getInterface();
    // the registered object a handle names, null for an unknown handle
    ColiObject* getObject(unsigned int handle) const;
    bool isGblId(unsigned int id);
    void setGblId(unsigned int id, bool clear);
    // the framework's per-frame calls (Framework::update, postUpdate, tail)
    void update();
    void postUpdate();
    void tail();

    // the name is not the original's
    mm::mtl::UniquePtr<Impl> m_impl;
};
}  // namespace fw

#endif
