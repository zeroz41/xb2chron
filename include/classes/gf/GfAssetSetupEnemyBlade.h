#ifndef CLASSES_GF_GFASSETSETUPENEMYBLADE_H
#define CLASSES_GF_GFASSETSETUPENEMYBLADE_H

#include "mm/mtl/RTTI.h"
#include "classes/gf/GfAssetSetupEnemy.h"

namespace gf { enum GfAssetType : int; }

namespace gf {
// table 0x7100B43C18
class GfAssetSetupEnemyBlade : public ::gf::GfAssetSetupEnemy {
public:
    GfAssetSetupEnemyBlade();
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfAssetSetupEnemyBlade() {}  // slot 1
    virtual const char* getMdlFile(gf::GfAssetType type);  // slot 4
    virtual const char* getMotFile(gf::GfAssetType type);  // slot 6
    virtual const char* getRetargetMotFile(gf::GfAssetType type);  // slot 7
    virtual const char* getPath() const;  // slot 33
    static mm::mtl::RTTI m_rtti;
};
}  // namespace gf

#endif
