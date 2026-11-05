#ifndef CLASSES_GF_GFASSETPACK_H
#define CLASSES_GF_GFASSETPACK_H

#include "classes/mm/mtl/ReferenceObject.h"
#include "mm/mtl/FixStr.h"
#include "mm/mtl/FixedVector.h"
#include "mm/mtl/FixedQueue.h"
#include "classes/gf/GfAssetManager.h"
#include "classes/gf/GfSound.h"

namespace mm { namespace mtl { class IAllocator; } }
namespace gf { enum GfAssetType : int; }
namespace gf { enum GfFileIdx : int; }
namespace gf { class GfAssetResource; }
namespace gf { class GF_SLOT_HANDLE; }
namespace gf { class GF_ASSET_HANDLE; }
namespace fw { class SoundPack; }

namespace gf {
// what a pack is made from: GfAssetPack's constructor and GfAssetFiles::setInitializeParam read it (1.0.0's symbols
// name the class; the field names are not the original's; the size is not proven)
class GfAssetFilesInfo {
public:
    // the setups build it on the stack with these values (GfAssetSetupDriverForUi::setup)
    GfAssetFilesInfo() : m_type(GfAssetType(0)), m_name(nullptr), pad_38(0), pad_3c(1), pad_40(0) {}

    GF_ASSET_HANDLE* m_handle;  // the setup's handle (the name is not the original's)
    GfAssetType m_type;  // the pack's asset type
    unsigned char pad_c[0x10 - 0xC];
    // the asset types the pack falls back to: GfAssetSetup::requestWpnSePackFile and requestFootStepSePackFile
    // clear it and push type 18 (inline FixedQueue clear/push_back stores at +0x10/+0x20/+0x28; the name is not
    // the original's)
    mm::mtl::FixedQueue<GfAssetType, 4> m_backupTypes;
    const char* m_name;  // the pack's name (its CRC is the pack's key)
    unsigned int pad_38;
    unsigned int pad_3c;
    unsigned int pad_40;  // the setups copy GfInitParam::pad_44 here
    unsigned char pad_44[0x48 - 0x44];
};

// an asset's name split from its path: the file name, the folder before it (set), and a third name the constructor
// clears (1.0.0's symbols name the class and its methods; the field names are not the original's)
class GfAssetName {
public:
    GfAssetName(const char* path);
    void set(const char* path);

    mm::mtl::FixStr<16> m_name;  // the path's file name
    mm::mtl::FixStr<32> m_dir;  // the path before the file name
    mm::mtl::FixStr<64> m_extra;  // only the constructor clears it here
};

// a pack's key: its type and its name's CRC (1.0.0's AssetPackInfo::isExistAssetPack(AssetPackValue) names the type;
// the field names are not the original's)
struct AssetPackValue {
    bool operator==(const AssetPackValue& other) const { return m_key == other.m_key; }

    union {
        struct {
            GfAssetType m_type;
            unsigned int m_hash;
        };
        unsigned long m_key;
    };
};

// the files of one asset pack (1.0.0's symbols name the class and its methods; the field names are not the
// original's)
class GfAssetFiles {
public:
    // one file: its index, the key its preloaded size is kept under, its path and size (-2 until known)
    class AssetFile {
    public:
        AssetFile(GfFileIdx idx, const char* path);

        GfFileIdx m_idx;
        unsigned char pad_4[0x4];
        unsigned long m_sizeHandle;  // GfFileSizePool::getFileSize's key (applyPreFileSize)
        mm::mtl::FixStr<128> m_path;  // getFileName returns it
        int m_fileSize;  // -2 until applyPreFileSize reads it, -1 for a file that does not exist
        bool m_isWimdo;  // the path ends in ".wimdo"
    };

    // the files are the pack's (GfAssetPack's destructor deletes them)
    ~GfAssetFiles() {
        for (AssetFile** it = m_files.begin(); it != m_files.end(); ++it) {
            if (*it != nullptr) {
                delete *it;
                *it = nullptr;
            }
        }
    }
    bool isExistSameAsset(const GfAssetFiles& other) const;
    // the type and name from info, the files deleted and the lists emptied (1.0.0's symbols name it)
    void setInitializeParam(const GfAssetFilesInfo& info);
    // the file's path, an empty name for a file the pack does not have (1.0.0's symbols name it)
    const mm::mtl::FixStr<128>& getFileName(GfFileIdx idx) const;
    // the file path under the index (1.0.0's symbols name it; the return type is not known)
    // false when it adds no file (GfAssetSetup::requestCoreResource logs the pack then)
    bool addResource(GfFileIdx idx, const char* path);
    // the replacement index the file map gives a file, -1 for none (1.0.0's symbols name it; inline: this build has
    // no copy of it)
    int getCommonResource(GfFileIdx idx) const {
        for (unsigned int map : m_fileMap) {
            if ((map & 0xFFFF) == static_cast<unsigned int>(idx)) {
                return map >> 16;
            }
        }
        return -1;
    }
    // whether the file (or the one the file map replaces it with) is one the pack has but that does not exist (its
    // size -1) (1.0.0's symbols name it; inline: this build has no copy of it)
    bool isNoFile(GfFileIdx idx) const {
        int common = getCommonResource(idx);
        if (common == -1) {
            common = idx;
        }
        for (AssetFile* file : m_files) {
            if (file->m_idx == common) {
                return file->m_fileSize == -1;
            }
        }
        return false;
    }
    // whether the pack has the file, or the one the file map replaces it with (1.0.0's symbols name it; inline: this
    // build has no copy of it)
    bool isExistFile(GfFileIdx idx) const {
        int common = getCommonResource(idx);
        if (common == -1) {
            common = idx;
        }
        for (AssetFile* file : m_files) {
            if (file->m_idx == common) {
                return true;
            }
        }
        return false;
    }

    GfAssetType m_type;
    unsigned int m_nameHash;  // m_name's CRC (setInitializeParam)
    mm::mtl::FixStr<64> m_name;
    unsigned char pad_4c[0x4];
    mm::mtl::FixedVector<AssetFile*, 16> m_files;
    // (file index & 0xFFFF) | (replacement index << 16): getFileName looks a file up through them
    mm::mtl::FixedVector<unsigned int, 8> m_fileMap;
};

// table 0x7100B43648; counted: releaseResource and AssetPackInfo's destructor release their references
class GfAssetPack : public mm::mtl::ReferenceObject {
public:
    GfAssetPack(const GfAssetFilesInfo& info);
    virtual ~GfAssetPack();  // slot 0
    static GfAssetPack* create(const GfAssetFilesInfo& info);
    static AssetPackValue calcAssetPackValue(const char* name, GfAssetType type);
    void loadStart(mm::mtl::IAllocator* allocator);
    void releaseResource();
    // the pack's sound pack dropped once its last user releases it (1.0.0's symbols name it; inline: this build has
    // no copy of it)
    void destroySoundPack() {
        if (m_sePackId != -1 && m_sePackRef > 0 && m_sePackRef-- == 1) {
            if (GfSound* sound = GfSound::sys()) {
                sound->destroyObjSePack(m_sePack);
            }
        }
    }
    // the slot handed back to GfAssetManager (1.0.0's symbols name it; inline: this build has no copy of it)
    void releaseSlotHandle() {
        if (m_slotHandle != reinterpret_cast<GF_SLOT_HANDLE*>(-1)) {
            GfAssetManager::releaseSlotHandle(m_slotHandle);
            m_slotHandle = reinterpret_cast<GF_SLOT_HANDLE*>(-1);
        }
    }
    GfAssetType getAssetType() const;
    void dispAssetLogForDebug();
    bool isCached() const;
    const mm::mtl::FixStr<64>* getAssetName() const;
    void applyPreFileSize();
    bool isPreSizeSizeValid() const;
    // the bytes the pack's files still need, in blocks of `blockSize` (GfSlotMapping::setupFreeSlot)
    unsigned long getNeedLoadFileSize(unsigned long blockSize, bool);
    // false when the pack has no backup asset type to change to, or already holds a resource
    // (GfSlotMapping::updateSlotRequest); else the files take the next backup type
    bool changeBackupAssetType();
    // whether one of the pack's resources is reference memory, resource type 3
    // (GfAssetManager::updateCheckCacheReload)
    bool isExistReferenceMemory() const;
    // whether the pack has no slot yet or a file that exists has no resource (GfAssetManager::createAssetFiles)
    bool isNeedLoad() const;
    void updateCacheCount();
    void setTimeout();
    bool isExistSameAsset(const GfAssetPack& other) const;
    // drops the pack's reference to a resource; true when the pack held it (GfAssetManager::releaseRefResource stops
    // at the first such pack)
    bool releaseRefResource(void* resource);
    // the resource loaded for a file, looked up by its index, else through the file map's replacement index
    // (1.0.0's symbols name it)
    GfAssetResource* getResource(GfFileIdx file) const;
    // the resource whose asset name is `name` (the name is not the original's; defined inline in
    // gf_asset_pack.cpp: this build has no copy of it; AssetPackInfo::getResource asks each pack)
    GfAssetResource* getResource(const char* name) const;
    bool isLoaded(mm::mtl::FixStr<128>* name) const;
    // each wimdo file's resource sets up its stream object (1.0.0's symbols name it; defined inline in
    // gf_asset_pack.cpp: this build has no copy of it)
    void setupStreamObject();
    // the pack's sound pack when the file's resource holds valid data (1.0.0's symbols name it; defined inline in
    // gf_asset_pack.cpp: this build has no copy of it)
    fw::SoundPack* getSePackByFileIdx(GfFileIdx file);
    void releaseEmptySlot();
    // the pack's sound pack made from its first loaded file's resource, or one more use of the one it has (1.0.0's
    // symbols name it)
    void createSoundPack();
    // the resource held for the file, its reference added (1.0.0's symbols name it)
    void setResource(GfFileIdx file, GfAssetResource* resource);

    unsigned char pad_c[0x4];
    AssetPackValue m_value;  // calcAssetPackValue's for the pack's name and type
    // a resource the pack holds a reference to and the file it is for (setResource)
    struct Resource {
        GfAssetResource* m_resource;
        unsigned short m_fileIdx;
    };
    mm::mtl::FixedVector<Resource, 16> m_resources;  // releaseResource releases them
    GfAssetFiles m_files;
    // loadStart's: the files' resources are created from it (the name is not the original's)
    mm::mtl::IAllocator* m_allocator;
    bool m_enterLocked;  // AssetPackInfo::lockEnterRersource sets it (the name is not the original's)
    unsigned char pad_229[0x7];
    GF_SLOT_HANDLE* m_slotHandle;  // -1 while it has none
    // releaseRefResource sets it when one of the pack's resources holds the data it is given; the constructor clears
    // it (the name is not the original's)
    bool m_refReleased;
    // changeBackupAssetType sets it when it gives the files the next backup type (the name is not the original's)
    bool m_backupChanged;
    bool m_full;  // AssetPackInfo::isFullResource asks whether any pack has it (the name is not the original's)
    bool m_timeout;  // setTimeout sets it
    unsigned char pad_23c[0xc];
    // the slots the pack asks for: GfSlotMapping::setupFreeSlot passes it to GfSlotAll::getByteSizeBySlotNum (the
    // name is not the original's)
    unsigned int m_slotNum;
    // the slots its load needs: setupFreeSlot sets it from GfSlotAll::getSlotNumByByteSize (the name is not the
    // original's)
    unsigned int m_needSlotNum;
    // the pack's load priority: GfSlotMapping::BiggerPrio sorts slot requests by it, biggest first (the name is not
    // the original's)
    unsigned int m_prio;
    // the AssetPackInfos holding the pack (AssetPackInfo's destructor drops one); a used pack is not cached (the
    // name is not the original's)
    int m_useCount;
    unsigned char pad_258[0x24];
    // updateCacheCount counts the updates the pack goes unused, up to 99 (the name is not the original's)
    unsigned int m_cacheCount;
    // AssetPackInfo::updateReloadCount counts the updates the pack goes with no reference besides its users', up to
    // 99 (the name is not the original's)
    unsigned int m_refCacheCount;
    unsigned char pad_284[0x4];
    // the asset types the pack falls back to, first first: changeBackupAssetType takes them off one by one (the name
    // is not the original's)
    mm::mtl::FixedQueue<GfAssetType, 4> m_backupTypes;
    fw::SoundPack* m_sePack;  // createSoundPack's; GfSound::destroyObjSePack destroys it
    int m_sePackId;  // -1 for a pack with no sound pack
    int m_sePackRef;  // destroySoundPack drops one, the last destroys the sound pack
    // AssetPackInfo::lockEnterRersource sets it with m_enterLocked (the name is not the original's)
    bool m_resourceLocked;
    unsigned char pad_2b9[0x7];
};
}  // namespace gf

#endif
