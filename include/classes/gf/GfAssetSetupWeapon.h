#ifndef CLASSES_GF_GFASSETSETUPWEAPON_H
#define CLASSES_GF_GFASSETSETUPWEAPON_H

#include "mm/mtl/RTTI.h"
#include "classes/gf/GfAssetSetup.h"
#include "gf/GfAppend.h"
#include "mm/mtl/FixStr.h"

namespace gf { class GF_ASSET_HANDLE; }
namespace gf { enum GfAssetType : int; }
namespace gf { class GfInitParamWeapon; }

namespace gf {
// Placeholder name: nothing in 1.0.0's place names it (1.0.0's copy at 0x71001C762C is unnamed too). A free
// function in this unit's namespace: it takes no object, only GfAssetSetupWeapon's four file getters call it.
// What it does: empties out, then copies file into it when file is not empty, else name when name is not
// empty; when dbPath is set and the text holds "wp/", it drops the first three characters and inserts "db/" at
// the start (FixStr<128>::insert). Callers pass a static FixStr<128>, their RefResource's name (an empty one when
// none), GfAppend::getModelName/getMotionName and GfInitParam::pad_83.
void fn_71001C0EE0(mm::mtl::FixStr<128>& out, const mm::mtl::FixStr<128>& file, const char* name, bool dbPath);

// table 0x7100B442E8
class GfAssetSetupWeapon : public ::gf::GfAssetSetup {
public:
    GfAssetSetupWeapon();
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfAssetSetupWeapon() {}  // slot 1
    virtual const char* getMdlFile(gf::GfAssetType type);  // slot 4
    virtual const char* getArcFile(gf::GfAssetType type);  // slot 5
    virtual const char* getMotFile(gf::GfAssetType type);  // slot 6
    virtual const char* getEfpFile(gf::GfAssetType type);  // slot 11
    virtual const char* getStpFile(gf::GfAssetType type);  // slot 15
    virtual int getMdlSlot() const;  // slot 19
    virtual int getArcSlot() const;  // slot 20
    virtual int getMotSlot() const;  // slot 21
    virtual int getEfpSlot() const;  // slot 26
    virtual int getStpSlot() const;  // slot 29
    virtual const char* getPath() const;  // slot 33
    virtual GfAssetType getAssetType() const;  // slot 39
    void setup(GF_ASSET_HANDLE* handle, const GfInitParamWeapon& param);
    static mm::mtl::RTTI m_rtti;

    GfAppend m_append;  // the name is not the original's
};
}  // namespace gf

#endif
