#ifndef CLASSES_GF_GFINITPARAMNPC_H
#define CLASSES_GF_GFINITPARAMNPC_H

#include "classes/gf/GfInitParam.h"

namespace gf {
// table 0x7100B3FB70
class GfInitParamNpc : public ::gf::GfInitParam {
public:
    // inline: no copy of it exists (GfObjFactory::createGmkNpc builds it on the stack)
    GfInitParamNpc() : GfInitParam(6), pad_98(nullptr), pad_a0() {
        m_assetSetup = nullptr;
        pad_90 = false;
        pad_82 = 1;
    }

    // GfObjFactory::createGmkNpc sets it when it fills pad_98 with its row's "name"
    bool pad_90;
    unsigned char pad_91[0x98 - 0x91];
    // createSetupParam copies it into the setup
    void* pad_98;
    // GfObjFactory::createGmkNpc stores its row's MountPoint, MountObject, MountPoint2, MountObject2 here;
    // createNpc passes them on to the unnamed file-local helper of gf_obj_factory.cpp that sets up the belongings
    unsigned short pad_a0[4];
};
}  // namespace gf

#endif
