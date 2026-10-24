#ifndef CLASSES_FW_ASSETMANAGER_H
#define CLASSES_FW_ASSETMANAGER_H

#include "classes/fw/ManagerObject.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/Vector.h"
#include "mtl/AllocHandle.h"

namespace fw { class UpdateInfo; class AssetData; class AssetCsvb; class AssetLoader; }
namespace mm { namespace mtl { class IAllocator; } }

namespace fw {
// table 0x7100B40EA8; PtrSingleton<AssetManager>'s table 0x7100B40F20 at 0x10 (the constructor installs it)
class AssetManager : public ::fw::ManagerObject, public ::mm::mtl::PtrSingleton< ::fw::AssetManager> {
public:
    // room for count of each kind in allocator's memory
    AssetManager(mm::mtl::IAllocator* allocator, unsigned int count);
    virtual ~AssetManager();  // slot 0
    virtual const char* getName() const;  // slot 5
    virtual void update(fw::UpdateInfo const&);  // slot 8

    // the memory assets are made in (Framework::getMemHandle's), and a name's hash (the assets' m_hash)
    static mtl::ALLOC_HANDLE getMemSYS();
    static unsigned int getHash(const char* name);
    void addAsset(AssetData* asset);
    void removeAsset(AssetData* asset);
    // the next asset after `after` (the first when null) whose name is name's normalized path
    AssetData* searchAsset(const char* name, AssetData* after);
    void addLoader(AssetLoader* loader);
    void removeLoader(AssetLoader* loader);
    // the loader reading name into the handle's (the allocator's) memory
    AssetLoader* searchLoader(mtl::ALLOC_HANDLE handle, const char* name);
    AssetLoader* searchLoader(mm::mtl::IAllocator* allocator, const char* name);

    // the names are not the original's
    mm::mtl::Vector<AssetData*> m_assets;  // addAsset's
    mm::mtl::Vector<AssetCsvb*> m_csvbs;
    mm::mtl::Vector<AssetLoader*> m_loaders;  // addLoader's
};
}  // namespace fw

#endif
