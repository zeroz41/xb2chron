#include "classes/fw/ResourceManager.h"
#include "classes/ml/fixed_size_alloc_inside.h"
#include "classes/gf/GfPause.h"
#include "gf/GfStaticRes.h"
#include "gf/GfSetupParam.h"
#include "classes/fw/CommonResource.h"
#include "mtl/MemManager.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfInfo.h"
#include "classes/gf/IGfEvent.h"
#include "ml/MlMem.h"
#include "gf/GfSoundSource.h"

namespace _gfstr {

const char* szCameraXB2 = "/camera/params.gca";

const char* szCameraIRA = "/camera/params_dlc.gca";

}  // namespace _gfstr

namespace gf {

mtl::ALLOC_HANDLE GfStaticRes::s_hMem;

::mm::mtl::FixedList<GfStaticRes::ResourceInfo, 64> GfStaticRes::s_aResource;

void GfStaticRes::initialize(const GfSetupParam& param) {
    s_hMem = mtl::MemManager::create(ml::MlMem::getProductMem(), 0x200000, "GfStatic", false, "no name", 0);
    loadRequest(param.m_dlcCameraParam);
    while (!::mm::mtl::PtrSingleton<fw::ResourceManager>::get()->isLoaded()) {
        GfSleep(1);
    }
}

void GfStaticRes::loadRequest(bool dlcCamera) {
    loadStaticRes("/param/common.prm");
    loadStaticRes("/param/pc.prm");
    loadStaticRes("/param/camera.prm");
    loadStaticRes("/param/menu.prm");
    loadStaticRes("/param/event.prm");
    loadStaticRes("/param/effect.prm");
    loadStaticRes("/param/pad.pdp");
    unsigned int count = getSoundSourceCount();
    for (unsigned int i = 0; i != count; ++i) {
        loadStaticRes(getSoundSourceFileName(i));
    }
    loadStaticRes(dlcCamera ? _gfstr::szCameraIRA : _gfstr::szCameraXB2);
}

void GfStaticRes::loadStaticRes(const char* path) {
    if (fw::CommonResource* resource = fw::CommonResource::request(s_hMem, path, 10, false)) {
        ResourceInfo info;
        info.m_resource = resource;
        info.m_path = path;
        s_aResource.push_back(info);
    }
}

fw::CommonResource* GfStaticRes::search(const char* path) {
    return fw::CommonResource::search(s_hMem, path);
}

void GfStaticRes::setupGameType(bool dlcCamera) {
    if (dlcCamera) {
        replaceLoad(_gfstr::szCameraXB2, _gfstr::szCameraIRA);
    } else {
        replaceLoad(_gfstr::szCameraIRA, _gfstr::szCameraXB2);
    }
}

}  // namespace gf
