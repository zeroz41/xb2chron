#ifndef CLASSES_FW_NAVIMANAGER_H
#define CLASSES_FW_NAVIMANAGER_H

#include "classes/fw/ManagerObject.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace fw { class NaviManager; }
namespace navi { class NvmshAcObj; }
namespace navi { class NvmshManager; }

namespace fw {
// table 0x7100B42410; the base at 0x10 is mm::mtl::PtrSingleton<fw::NaviManager> (its constructor stores that
// table there and asserts singleton.h's get()==0)
class NaviManager : public ::fw::ManagerObject, public ::mm::mtl::PtrSingleton< ::fw::NaviManager> {
public:
    NaviManager();
    virtual ~NaviManager();  // slot 0
    virtual bool initialize();  // slot 2: creates the navigation mesh manager
    virtual bool finalize();  // slot 3
    // hands the mesh resource to the navigation mesh manager; false before initialize
    bool createNaviMesh(void* resource, const char* name);
    void releaseNaviMesh();
    navi::NvmshAcObj* createObject();
    void releaseObject(navi::NvmshAcObj* object);
    // gives the navigation mesh manager the current camera's position
    void update();
    void tail();

    void* m_resource;              // createNaviMesh's resource (the name is not the original's)
    navi::NvmshManager* m_nvmsh;  // initialize's (the name is not the original's)
};
}  // namespace fw

#endif
