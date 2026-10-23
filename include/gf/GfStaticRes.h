#ifndef GF_GFSTATICRES_H
#define GF_GFSTATICRES_H

#include "mm/mtl/FixStr.h"
#include "mm/mtl/FixedList.h"
#include "mtl/AllocHandle.h"

namespace fw { class CommonResource; }
namespace gf { class GfSetupParam; }

namespace gf {
// the game's resident resources, loaded at start
class GfStaticRes {
public:
    // a loaded resource and its path (the field names are not the original's)
    struct ResourceInfo {
        fw::CommonResource* m_resource;
        ::mm::mtl::FixStr<64> m_path;
    };

    // makes the memory, requests the resources and waits for them (GfManager::build passes its setup parameters:
    // 1.0.0's took none)
    static void initialize(const GfSetupParam& param);
    // requests the resident resources (1.0.0's took none; dlcCamera picks the camera parameters' file)
    static void loadRequest(bool dlcCamera);
    static void finalize();
    static void loadStaticRes(const char* path);
    // the loaded resource of that path (fw::CommonResource::search in GfStaticRes's memory), none if not loaded
    static fw::CommonResource* search(const char* path);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it reloads GfStaticRes's
    // resources (s_hMem, s_aResource). What it does: fn_710032C088 with the camera parameters' files, the DLC's
    // ("/camera/params_dlc.gca") replacing "/camera/params.gca" when its argument is set, the other way round when
    // not. Its one caller is fn_7100156288.
    static void fn_710032C04C(bool dlcCamera);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it (1.0.0's reloadRequestForDebug(const char*)
    // differs). A member because it works on s_hMem and s_aResource. What it does: searches oldPath in GfStaticRes's
    // memory; none loaded, it block-requests newPath and keeps it in s_aResource; one loaded, it releases that entry's
    // resource and block-requests newPath into the same entry.
    static void fn_710032C088(const char* oldPath, const char* newPath);

    // the camera parameters' files, the DLC's second (new in 3.0.1: the names are not the original's)
    static const char* s_cameraParam;
    static const char* s_cameraParamDlc;
    static mtl::ALLOC_HANDLE s_hMem;
    static ::mm::mtl::FixedList<ResourceInfo, 64> s_aResource;
};
}  // namespace gf

#endif
