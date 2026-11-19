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
    // the job its constructor enters into its job group (WorkCpu::entryJobThread): man is the manager
    static unsigned int jobUpdate(void* man, void* arg);
    // fw::NaviManager::update's store, inline (the name is not the original's)
    void setPos(const mm::Vec3& pos) { m_pos[m_posBank] = pos; }

    // the constructor's scene (the name is not the original's)
    ml::Scn* m_scn;  // 0x10
    unsigned char pad_18[8];
    // two positions, m_posBank's the one written (fw::NaviManager::update gives it the camera's); tail hands the
    // other to NvmshResMan::updateMemMove and flips m_posBank (the names are not the original's)
    mm::Vec3 m_pos[2];
    // tail hands it to NvmshResMan::updateMemMove as the second position (the name is not the original's)
    mm::Vec3 m_target;  // 0x40
    // setupResource/releaseResource forward to the first, createObj/releaseObj to the second, createObj passes
    // the handle (the names are not the original's)
    NvmshResMan* m_pResMan;  // 0x50
    NvmshAcMan* m_pAcMan;  // 0x58
    mtl::ALLOC_HANDLE m_hAlloc;  // 0x60
    int m_posBank;
    // jobUpdate sets 0x20000 while it runs and skips the update when the bit 0x4 selects (0x8 if set, else
    // 0x1) is set (the name is not the original's)
    unsigned int m_flags;  // 0x68
    int m_worldId;  // 0x6C, tail hands it to NvmshResMan::updateMemMove (the name is not the original's)
    int m_jobGroup;  // 0x70, the WorkCpu job group the constructor creates (the name is not the original's)
    unsigned char pad_74[0xC];  // fields: size from fw::NaviManager::initialize's allocation (0x80)
};
}  // namespace navi

#endif
