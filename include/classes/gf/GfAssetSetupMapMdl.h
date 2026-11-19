#ifndef CLASSES_GF_GFASSETSETUPMAPMDL_H
#define CLASSES_GF_GFASSETSETUPMAPMDL_H

#include "mm/mtl/RTTI.h"
#include "classes/gf/GfAssetSetup.h"

namespace gf {
// 3.0.1 keeps only its m_rtti (gf_asset_setup.cpp's static initializer stores it); 1.0.0 also has its constructor
// (the GfAssetSetup base's stores) and getters, which 3.0.1's linker dropped with its table
class GfAssetSetupMapMdl : public ::gf::GfAssetSetup {
public:
    static mm::mtl::RTTI m_rtti;
};
}  // namespace gf

#endif
