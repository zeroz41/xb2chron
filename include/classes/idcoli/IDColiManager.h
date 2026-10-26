#ifndef CLASSES_IDCOLI_IDCOLIMANAGER_H
#define CLASSES_IDCOLI_IDCOLIMANAGER_H

#include "classes/idcoli/IDColiMemHandleAllocator.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "idcoli/ColiLinkList.h"
#include "mtl/AllocHandle.h"

namespace ml { class Scn; }
namespace idcoli { class IDColiManager; class IDColiObj; class IDColiTreeTop; }

namespace idcoli {
// table 0x7100B7F068
// the collision objects' owner. The field names are not the original's.
class IDColiManager : public ::mm::mtl::PtrSingleton< ::idcoli::IDColiManager> {
public:
    // the object kinds, the order of m_objList/m_addList (the names are not the original's)
    enum Kind { KIND_GRAND, KIND_CHARACTER, KIND_PHANTOM, KIND_GRDCHAR, KIND_NUM };

    IDColiManager(ml::Scn* scn, mtl::ALLOC_HANDLE parent, unsigned int size);
    virtual ~IDColiManager();  // slot 0
    void release();
    void update();
    void addDelUpdate();
    void consistentUpdate();
    void updateConsistentList(ColiLinkList<IDColiObj>& list);
    // a member: fw::ColiManager::tail hands it its collision system in x0
    void tail();
    IDColiObj* createColiGrand(const void* data);
    IDColiObj* createColiCharacter();
    IDColiObj* createColiPhantom();
    IDColiObj* createColiGrdChar();
    unsigned int isGblId(unsigned int id);
    void setGblId(unsigned int id, bool clear);

    // the frame's two halves (tail swaps them): objects mark requests in bits shifted by s_nStkIdx
    static int s_nStkIdx;
    static int s_nDebIdx;

    ColiLinkList<IDColiObj> m_objList[KIND_NUM];  // 0x8, update calls each object's update
    ColiLinkList<IDColiObj> m_addList[KIND_NUM][2];  // 0x48, the createColi* functions add to [kind][s_nStkIdx]
    unsigned char pad_c8[0x10];
    IDColiTreeTop* m_charTree;  // 0xD8, createColiCharacter's objects
    IDColiTreeTop* m_phantomTree;  // 0xE0, createColiPhantom's objects
    unsigned int* m_gblIdBits;  // 0xE8, isGblId/setGblId's bits (0x400 bytes)
    unsigned int m_subNum;  // 0xF0, IDColiAccMan::setSubNum
    mtl::ALLOC_HANDLE m_allocHandle;  // 0xF4, the "Collision" heap
    IDColiMemHandleAllocator m_allocator;  // 0xF8, allocates from m_allocHandle
};
}  // namespace idcoli

#endif
