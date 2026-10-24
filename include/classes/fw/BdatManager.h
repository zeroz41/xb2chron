#ifndef CLASSES_FW_BDATMANAGER_H
#define CLASSES_FW_BDATMANAGER_H

#include "classes/fw/ManagerObject.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "mtl/AllocHandle.h"

namespace fw { class UpdateInfo; }
namespace mm { namespace mtl { class IAllocator; } }

namespace fw {
// table 0x7100B40F40; PtrSingleton<BdatManager>'s table 0x7100B40FB8 at 0x10 (the constructor installs it)
class BdatManager : public ::fw::ManagerObject, public ::mm::mtl::PtrSingleton< ::fw::BdatManager> {
public:
    // the loaded files and their tables (AssetManager.cpp defines it; the constructor makes it in allocator's memory)
    class Impl;

    explicit BdatManager(mm::mtl::IAllocator* allocator);
    virtual ~BdatManager();  // slot 0
    virtual bool initialize();  // slot 2
    virtual bool finalize();  // slot 3
    virtual const char* getName() const;  // slot 5
    virtual void update(fw::UpdateInfo const&);  // slot 8
    // the BDAT files, by the slot each is loaded into: loading one from the named file into the handle's memory (true
    // when the load started), reading a slot's file again, registering one already in memory, whether a slot holds a
    // file and whether it is loaded, a slot's release, and a loaded table by name
    static bool loadBdat(int slot, mtl::ALLOC_HANDLE handle, const char* name);
    static bool reloadBdat(int slot);
    static void loadBdatFromMemory(int slot, void* data);
    static bool isExistBdat(int slot);
    static bool isEnableBdat(int slot);
    static void unregistBdat(int slot);
    static unsigned char* getFp(const char* name);

    // the names are not the original's
    Impl* m_impl;
    mm::mtl::IAllocator* m_allocator;  // the constructor's (Impl's nodes come from it)
};
}  // namespace fw

#endif
