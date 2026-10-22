#ifndef CLASSES_GF_GFASSETSETUPENEMYBLADE_H
#define CLASSES_GF_GFASSETSETUPENEMYBLADE_H

#include "mm/mtl/RTTI.h"
#include "classes/gf/GfAssetSetupEnemy.h"

namespace gf { class GfAssetType; }

namespace gf {
// table 0x7100B43C18
class GfAssetSetupEnemyBlade : public ::gf::GfAssetSetupEnemy {
public:
    GfAssetSetupEnemyBlade();
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfAssetSetupEnemyBlade() {}  // slot 1
    virtual void getMdlFile(gf::GfAssetType);  // slot 4
    virtual void getMotFile(gf::GfAssetType);  // slot 6
    virtual void getRetargetMotFile(gf::GfAssetType);  // slot 7
    virtual void getPath() const;  // slot 33
    static mm::mtl::RTTI m_rtti;
};
}  // namespace gf

#endif
