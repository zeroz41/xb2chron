#ifndef CLASSES_NAVI_NVMSHMANAGER_H
#define CLASSES_NAVI_NVMSHMANAGER_H

#include "classes/ml/IWorkEvent.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/Vec3.h"
#include "mtl/AllocHandle.h"

namespace ml { class Scn; }
namespace navi { class NvmshAcMan; }
namespace navi { class NvmshAcObj; }
namespace navi { class NvmshManager; }
namespace navi { class NvmshResMan; }

namespace navi {
// table 0x7100B7F630
class NvmshManager : public ::mm::mtl::PtrSingleton< ::navi::NvmshManager>, public ::ml::IWorkEvent {
public:
    NvmshManager(ml::Scn* scn, mtl::ALLOC_HANDLE handle);
    virtual ~NvmshManager();  // slot 0
    void setupResource(const void* resource, const char* name);
    void releaseResource();
    NvmshAcObj* createObj();
    void releaseObj(NvmshAcObj* object);
    void tail();
    // fw::NaviManager::update's store, inline (the name is not the original's)
    void setPos(const mm::Vec3& pos) { m_pos[m_posBank] = pos; }

    unsigned char pad_10[0x10];
    // two positions, m_posBank's the one written (fw::NaviManager::update gives it the camera's); tail hands the
    // other to NvmshResMan::updateMemMove and flips m_posBank (the names are not the original's)
    mm::Vec3 m_pos[2];
    unsigned char pad_40[0x10];
    // setupResource/releaseResource forward to the first, createObj/releaseObj to the second, createObj passes
    // the handle (the names are not the original's)
    NvmshResMan* m_pResMan;  // 0x50
    NvmshAcMan* m_pAcMan;  // 0x58
    mtl::ALLOC_HANDLE m_hAlloc;  // 0x60
    int m_posBank;
    unsigned char pad_68[0x18];  // fields: size from fw::NaviManager::initialize's allocation (0x80)
};
}  // namespace navi

#endif
