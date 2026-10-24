#include "classes/fw/BdatManager.h"
#include "classes/fw/Camera.h"
#include "classes/ml/FileResTh.h"
#include "plugin/Bdat.h"
#include "classes/fw/AssetManager.h"
#include "classes/fw/AssetData.h"
#include "classes/fw/AssetLoader.h"
#include "classes/fw/BdatManager.h"
#include "classes/fw/Camera.h"
#include "classes/fw/Framework.h"
#include "classes/fw/FrameworkMemory.h"
#include "classes/ml/DevFileTh.h"
#include "classes/ml/FileResTh.h"
#include "classes/mm/mtl/IAllocator.h"
#include "fw/LangUtil.h"
#include "mm/mtl/FixedArray.h"
#include "mm/mtl/FixStr.h"
#include "mm/mtl/Hash.h"
#include "mm/mtl/Map.h"
#include "mtl/MemManager.h"
#include "plugin/Bdat.h"
#include "string.h"

namespace fw {

mtl::ALLOC_HANDLE AssetManager::getMemSYS() {
    return Framework::getMemHandle();
}

unsigned int AssetManager::getHash(const char* name) {
    return mm::mtl::hashStrCrc(name);
}

AssetManager::AssetManager(mm::mtl::IAllocator* allocator, unsigned int count)
    : m_assets(allocator), m_csvbs(allocator), m_loaders(allocator) {
    m_assets.reserve(count, 8);
    m_csvbs.reserve(count, 8);
    m_loaders.reserve(count, 8);
}

AssetManager::~AssetManager() {
    while (m_assets.size() != 0) {
        if (m_assets[m_assets.size() - 1] != nullptr) {
            m_assets[m_assets.size() - 1]->release();
            m_assets[m_assets.size() - 1] = nullptr;
        }
    }
    m_assets.clear();
    while (m_csvbs.size() != 0) {
        if (m_csvbs[m_csvbs.size() - 1] != nullptr) {
            m_csvbs[m_csvbs.size() - 1]->release();
            m_csvbs[m_csvbs.size() - 1] = nullptr;
        }
    }
    m_csvbs.clear();
    while (m_loaders.size() != 0) {
        if (m_loaders[m_loaders.size() - 1] != nullptr) {
            m_loaders[m_loaders.size() - 1]->release();
            m_loaders[m_loaders.size() - 1] = nullptr;
        }
    }
    m_loaders.clear();
}

void AssetManager::addAsset(AssetData* asset) {
    m_assets.push_back(asset);
}

void AssetManager::removeAsset(AssetData* asset) {
    AssetData** it = m_assets.begin();
    AssetData** last = m_assets.end();
    while (it != last && *it != asset) {
        ++it;
    }
    if (it != m_assets.end()) {
        m_assets.erase(it);
    }
}

AssetData* AssetManager::searchAsset(const char* name, AssetData* after) {
    if (m_assets.size() == 0) {
        return nullptr;
    }
    mm::mtl::FixStr<256> path;
    ml::DevFileTh::normalizeDvdFileName(path, name);
    unsigned int hash = mm::mtl::hashStrCrc(path.m_str);
    AssetData** it = m_assets.begin();
    if (after != nullptr) {
        AssetData** first = m_assets.begin();
        AssetData** last = m_assets.end();
        while (first != last && *first != after) {
            ++first;
        }
        it = first;
        if (it != m_assets.end()) {
            ++it;
        }
    }
    for (; it != m_assets.end(); ++it) {
        AssetData* asset = *it;
        if (asset != nullptr && asset->m_hash == hash && strcmp(asset->m_name.m_str, path.m_str) == 0) {
            return asset;
        }
    }
    return nullptr;
}

void AssetManager::addLoader(AssetLoader* loader) {
    m_loaders.push_back(loader);
}

void AssetManager::removeLoader(AssetLoader* loader) {
    AssetLoader** it = m_loaders.begin();
    AssetLoader** last = m_loaders.end();
    while (it != last && *it != loader) {
        ++it;
    }
    if (it != m_loaders.end()) {
        m_loaders.erase(it);
    }
}

AssetLoader* AssetManager::searchLoader(mtl::ALLOC_HANDLE handle, const char* name) {
    unsigned int hash = mm::mtl::hashStrCrc(name);
    for (unsigned int i = 0; i < m_loaders.size(); i++) {
        AssetLoader* loader = m_loaders[i];
        if (loader != nullptr && loader->m_allocHandle.m_handle == handle.m_handle && loader->m_hash == hash &&
            strcmp(loader->m_name.m_str, name) == 0) {
            return loader;
        }
    }
    return nullptr;
}

AssetLoader* AssetManager::searchLoader(mm::mtl::IAllocator* allocator, const char* name) {
    unsigned int hash = mm::mtl::hashStrCrc(name);
    for (unsigned int i = 0; i < m_loaders.size(); i++) {
        AssetLoader* loader = m_loaders[i];
        if (loader != nullptr && loader->m_allocator == allocator && loader->m_hash == hash &&
            strcmp(loader->m_name.m_str, name) == 0) {
            return loader;
        }
    }
    return nullptr;
}

const char* AssetManager::getName() const {
    return "AssetManager";
}

void AssetManager::update(fw::UpdateInfo const&) {}

// the loaded BDAT files, one per slot, and every table of the registered ones by its name's hash (the field names
// and the BdatInfo/SheetFpInfo member names are not the original's; the class and type names are its symbols')
class BdatManager::Impl {
public:
    // a slot's file: read through a FileResTh (m_file) or handed over in memory (m_mem, m_fromMemory)
    struct BdatInfo {
        BdatInfo() { clear(); }
        // a file is there to register or registered
        bool isExist() const { return m_file != nullptr || m_mem != nullptr; }
        // its data, once read
        void* getData() const {
            if (m_mem != nullptr) {
                return m_mem;
            }
            if (m_file != nullptr) {
                return m_file->m_data;
            }
            return nullptr;
        }
        void clear() {
            m_file = nullptr;
            m_mem = nullptr;
            m_state = 0;
            m_handle.m_handle = 0;
            m_hash = 0;
            m_fromMemory = false;
            m_path.clear();
            m_name.clear();
            m_lang.clear();
        }

        int m_state;  // 0: empty, 1: reading, 2: read, 3: registered
        mm::mtl::FixStr<256> m_path;  // the normalized path read
        mm::mtl::FixStr<32> m_name;  // loadBdat's name
        mm::mtl::FixStr<16> m_lang;  // the language folder at load time (a load of the same name and language is kept)
        unsigned int m_hash;  // of m_name
        void* m_mem;
        mtl::ALLOC_HANDLE m_handle;
        ml::FileResTh* m_file;
        bool m_fromMemory;  // m_mem is the caller's: not freed on release
    };
    // a registered table: the file it is in, its name, its data and the file's slot
    struct SheetFpInfo {
        mm::mtl::FixStr<32> m_bdatName;
        mm::mtl::FixStr<64> m_sheetName;
        unsigned char* m_fp;
        int m_slot;
    };

    explicit Impl(mm::mtl::IAllocator* allocator)
        : m_allocator(allocator), m_root("bdat/"), m_sheets(allocator), m_infos() {}
    ~Impl();

    // root + the name, in the language's folder when the name has "_ms." (a message file)
    void makePath(mm::mtl::FixStr<256>& path, const char* name);
    void unregistBdat(int slot);
    bool loadBdat(int slot, mtl::ALLOC_HANDLE handle, const char* name);
    bool reloadBdat(int slot);
    // a slot's file moves on as its read completes: read, then registered with its tables indexed
    void updateLayer(int slot, BdatInfo& info);
    void loadBdatFromMemory(int slot, void* data);
    void update(const UpdateInfo& info);

    mm::mtl::IAllocator* m_allocator;
    mm::mtl::FixStr<256> m_root;  // "bdat/"
    mm::mtl::Map<unsigned int, SheetFpInfo> m_sheets;  // by the table name's hash
    mm::mtl::FixedArray<BdatInfo, 16> m_infos;  // by slot
};

void BdatManager::Impl::makePath(mm::mtl::FixStr<256>& path, const char* name) {
    if (strstr(name, "_ms.") != nullptr) {
        path += LangUtil::getLangFolder().m_str;
        path += "/";
        path += name;
    } else {
        path += name;
    }
}

BdatManager::Impl::~Impl() {
    for (int i = 0; i < 16; i++) {
        unregistBdat(i);
    }
}

void BdatManager::Impl::loadBdatFromMemory(int slot, void* data) {
    BdatInfo& info = m_infos[slot];
    info.m_path.clear();
    info.m_name.clear();
    info.m_state = 2;
    info.m_hash = 0;
    info.m_mem = data;
    info.m_handle.m_handle = 0;
    info.m_file = nullptr;
    info.m_lang = LangUtil::getLangFolder();
    info.m_fromMemory = true;
    updateLayer(slot, info);
}

void BdatManager::Impl::update(const UpdateInfo&) {
    for (int i = 0; i < 16; i++) {
        updateLayer(i, m_infos[i]);
    }
}

BdatManager::BdatManager(mm::mtl::IAllocator* allocator) : m_impl(nullptr), m_allocator(allocator) {
    m_impl = new (m_allocator->allocate(sizeof(Impl), 8)) Impl(m_allocator);
}

bool BdatManager::initialize() {
    return true;
}

bool BdatManager::finalize() {
    if (m_impl != nullptr) {
        delete m_impl;
        m_impl = nullptr;
    }
    return true;
}

void BdatManager::update(fw::UpdateInfo const& info) {
    if (isFinalized()) {
        return;
    }
    m_impl->update(info);
}

bool BdatManager::loadBdat(int slot, mtl::ALLOC_HANDLE handle, const char* name) {
    return get()->m_impl->loadBdat(slot, handle, name);
}

bool BdatManager::reloadBdat(int slot) {
    return get()->m_impl->reloadBdat(slot);
}

void BdatManager::loadBdatFromMemory(int slot, void* data) {
    get()->m_impl->loadBdatFromMemory(slot, data);
}

void BdatManager::unregistBdat(int slot) {
    get()->m_impl->unregistBdat(slot);
}

bool BdatManager::isExistBdat(int slot) {
    return get()->m_impl->m_infos[slot].isExist();
}

bool BdatManager::isEnableBdat(int slot) {
    Impl::BdatInfo& info = get()->m_impl->m_infos[slot];
    if (!info.isExist()) {
        return false;
    }
    return info.m_state == 3;
}

unsigned char* BdatManager::getFp(const char* name) {
    Impl* impl = get()->m_impl;
    mm::mtl::Map<unsigned int, Impl::SheetFpInfo>::node* n = impl->m_sheets.find(mm::mtl::hashStrCrc(name));
    if (n == nullptr) {
        return nullptr;
    }
    return n->value.second.m_fp;
}

BdatManager::~BdatManager() {}

const char* BdatManager::getName() const {
    return "BdatManager";
}

mm::mtl::RTTI Camera::m_rtti("Camera", nullptr, nullptr);

}  // namespace fw
