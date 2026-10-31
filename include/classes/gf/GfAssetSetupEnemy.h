#ifndef CLASSES_GF_GFASSETSETUPENEMY_H
#define CLASSES_GF_GFASSETSETUPENEMY_H

#include "mm/mtl/RTTI.h"
#include "classes/gf/GfAssetSetup.h"

namespace gf { class GF_ASSET_HANDLE; }
namespace gf { enum GfAssetType : int; }
namespace gf { class GfInitParamEnemy; }

namespace gf {
// table 0x7100B43AA8
class GfAssetSetupEnemy : public ::gf::GfAssetSetup {
public:
    GfAssetSetupEnemy();
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfAssetSetupEnemy() {}  // slot 1
    virtual const char* getMdlFile(gf::GfAssetType type);  // slot 4
    virtual const char* getArcFile(gf::GfAssetType type);  // slot 5
    virtual const char* getMotFile(gf::GfAssetType type);  // slot 6
    virtual const char* getRetargetMotFile(gf::GfAssetType type);  // slot 7
    virtual const char* getEfpFile(gf::GfAssetType type);  // slot 11
    virtual const char* getEabFile(gf::GfAssetType type);  // slot 12
    virtual const char* getEfbFile(gf::GfAssetType type);  // slot 13
    virtual const char* getStpFile(gf::GfAssetType type);  // slot 15
    virtual int getMdlSlot() const;  // slot 19
    virtual int getArcSlot() const;  // slot 20
    virtual int getMotSlot() const;  // slot 21
    virtual int getRetargetMotSlot() const;  // slot 22
    virtual int getEfpSlot() const;  // slot 26
    virtual int getEabSlot() const;  // slot 27
    virtual int getEfbSlot() const;  // slot 28
    virtual int getStpSlot() const;  // slot 29
    virtual const char* getPath() const;  // slot 33
    virtual GfAssetType getAssetType() const;  // slot 39
    virtual void setup(gf::GF_ASSET_HANDLE*, gf::GfInitParamEnemy const&);  // slot 40
    virtual int getAddMotSlot() const;  // slot 41
    virtual GfAssetType getAssetTypeMot() const;  // slot 42
    virtual GfAssetType getAssetTypeArc() const;  // slot 43
    // the enemy's attribute: its CHR_EnArrange row's BladeAtr, else (for a common blade model or a row with a
    // driver level) its blade's attribute, else for Hana her attribute or 5/1/5 for blades 1005..1007, else 0
    unsigned int getEnemyAttribute(const GfInitParamEnemy& param);
    static mm::mtl::RTTI m_rtti;

    // the parameter setup was given (setup stores it first; the model/motion getters read its m_createType and
    // m_bladeId); the constructor clears it (the name is not the original's)
    const GfInitParamEnemy* m_enemyParam;
};

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it (1.0.0's getMdlFile calls nothing like it).
// A free function next to GfAssetSetupEnemy because its only callers are GfAssetSetupEnemy::getMdlFile and
// GfAssetSetupEnemyBlade::getMdlFile and it takes no this. What it does: when the model name is a party driver's
// (drivers 1..6 for which GfDataDriver::fn_7100249170 holds, CHR_Dr model compared with strcmp) it returns
// fn_71002DF39C(driver, false, createType3); else when it is an attached party blade's CHR_Bl model it returns
// GfGameUtil::getBladeModel(blade, false); else the name itself. Callers pass m_enemyParam->m_createType == 3.
const char* fn_71001BD044(const char* name, bool createType3);
}  // namespace gf

#endif
