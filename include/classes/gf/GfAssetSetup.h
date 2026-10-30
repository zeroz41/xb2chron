#ifndef CLASSES_GF_GFASSETSETUP_H
#define CLASSES_GF_GFASSETSETUP_H

#include "mm/mtl/RTTI.h"
#include "mm/mtl/FixedVector.h"
#include "mm/mtl/FixStr.h"
#include "classes/gf/GfAssetManager.h"
namespace gf { class GF_ASSET_HANDLE; }
namespace gf { class GfAssetPack; }
namespace gf { class GfInitParam; }

namespace gf {
// table 0x7100B43688
class GfAssetSetup {
public:
    // inline: the symbols name no constructor of its own; the derived constructors show its stores (the handle
    // starts as -1)
    GfAssetSetup()
        : m_objId(0), m_handle(reinterpret_cast<GF_ASSET_HANDLE*>(-1)), m_paramCopy(nullptr), m_param(nullptr),
          pad_f0(0) {}
    // a file given to the setup ahead of loading: setupReference reads its data (0x88), size (0x90) and file
    // index (0x94) (the names are not the original's)
    struct RefResource {
        mm::mtl::FixStr<128> m_name;  // the file's name: the file getters return it when it is not empty
        unsigned char pad_84[0x88 - 0x84];
        void* m_data;
        unsigned int m_size;
        GfFileIdx m_fileIdx;
    };

    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfAssetSetup();  // slot 1
    virtual const char* getAssetCategoryName() const;  // slot 3
    virtual const char* getMdlFile(gf::GfAssetType type);  // slot 4
    virtual const char* getArcFile(gf::GfAssetType type);  // slot 5
    virtual const char* getMotFile(gf::GfAssetType type);  // slot 6
    virtual const char* getRetargetMotFile(gf::GfAssetType type);  // slot 7
    virtual const char* getEvtMotFile(gf::GfAssetType type);  // slot 8
    virtual const char* getSalvageMotFile(gf::GfAssetType type);  // slot 9
    virtual const char* getUiMotFile(gf::GfAssetType type);  // slot 10
    virtual const char* getEfpFile(gf::GfAssetType type);  // slot 11
    virtual const char* getEabFile(gf::GfAssetType type);  // slot 12
    virtual const char* getEfbFile(gf::GfAssetType type);  // slot 13
    virtual const char* getEfTailFile(gf::GfAssetType type);  // slot 14
    virtual const char* getStpFile(gf::GfAssetType type);  // slot 15
    virtual const char* getEvtStpFile(gf::GfAssetType type);  // slot 16
    virtual const char* getUiStpFile(gf::GfAssetType type);  // slot 17
    virtual const char* getSalvageStpFile(gf::GfAssetType type);  // slot 18
    virtual int getMdlSlot() const;  // slot 19
    virtual int getArcSlot() const;  // slot 20
    virtual int getMotSlot() const;  // slot 21
    virtual int getRetargetMotSlot() const;  // slot 22
    virtual int getEvtMotSlot() const;  // slot 23
    virtual int getSalvageMotSlot() const;  // slot 24
    virtual int getUiMotSlot() const;  // slot 25
    virtual int getEfpSlot() const;  // slot 26
    virtual int getEabSlot() const;  // slot 27
    virtual int getEfbSlot() const;  // slot 28
    virtual int getStpSlot() const;  // slot 29
    virtual int getEvtStpSlot() const;  // slot 30
    virtual int getUiStpSlot() const;  // slot 31
    virtual int getSalvageStpSlot() const;  // slot 32
    virtual const char* getPath() const;  // slot 33
    virtual const char* getEvtPath() const;  // slot 34
    virtual const char* getEffPath() const;  // slot 35
    virtual const char* getStpPath() const;  // slot 36
    virtual const char* getSePackPath() const;  // slot 37
    virtual void requestCoreResource(gf::GfAssetPack*, gf::GF_ASSET_HANDLE*);  // slot 38
    virtual GfAssetType getAssetType() const;  // slot 39
    static mm::mtl::RTTI m_rtti;

    // the file given for a file index, none when none was or its name is empty: the file getters' common start
    // (inline; the names are not the original's)
    RefResource* findRefResource(int fileIdx) const {
        for (RefResource* resource : m_refResources) {
            if (resource->m_fileIdx == fileIdx) {
                return resource;
            }
        }
        return nullptr;
    }
    const char* getRefFile(int fileIdx) const {
        RefResource* resource = findRefResource(fileIdx);
        if (resource != nullptr && resource->m_name.m_nLen != 0) {
            return resource->m_name.m_str;
        }
        return nullptr;
    }
    // keeps the handle, the parameter, its object id and a copy of its BDAT table pointer
    void setupParam(GF_ASSET_HANDLE* handle, const GfInitParam& param);
    // gives the setup a file already in memory (event::ModelObj::setupModel passes its DESC's files 0 and 1)
    void setRefResource(unsigned int index, const char* name, void* data, unsigned int size);

    // a name, none when it is empty (inline; the name is not the original's)
    static const char* validName(const char* name) {
        if (name == nullptr) {
            return nullptr;
        }
        return *name == '\0' ? nullptr : name;
    }

    // the object's id: setupParam copies GfInitParam::m_objId (the name is not the original's)
    unsigned int m_objId;
    unsigned char pad_c[0x10 - 0xC];
    // the handle being set up: setupParam stores the one it is given, the destructor hands it to
    // GfAssetManager::lockEnterRersource (the name is not the original's)
    GF_ASSET_HANDLE* m_handle;
    // setupParam's copy of the BDAT table pointer its parameter's 0x18 points at (the file getters read their
    // names from that table), when it points anywhere; the destructor
    // frees it (the name is not the original's)
    unsigned char** m_paramCopy;
    // the files setRefResource gives the setup: setupReference finds one by its file index and makes a
    // GfAssetResource of its data; the destructor frees each (the name is not the original's)
    mm::mtl::FixedVector<RefResource*, 24> m_refResources;
    // the parameter setupParam was given (the name is not the original's)
    const GfInitParam* m_param;
    unsigned char pad_f0;
    // two texts the constructor empties; what they hold is not known yet
    mm::mtl::FixStr<128> pad_f4;
    mm::mtl::FixStr<128> pad_178;
    // the derived classes' first fields go in the tail (0x1FC)
};
}  // namespace gf

#endif
