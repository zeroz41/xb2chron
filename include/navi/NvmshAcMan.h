#ifndef NAVI_NVMSHACMAN_H
#define NAVI_NVMSHACMAN_H

#include "mtl/AllocHandle.h"

#include "classes/navi/NvmshAcObjBase.h"

namespace navi { class NvmshAcObjBaseDef; }
namespace navi { class NvmshAcObjBaseGbl; }
namespace navi { class NvmshManager; }
namespace navi { class NvmshResMan; }

namespace navi {

// the navigation mesh's access objects (no table; NvmshManager holds one at 0x58 and forwards to it)
class NvmshAcMan {
public:
    // a list of access objects linked through their m_prev/m_next; the names are not the original's
    struct ObjList {
        NvmshAcObjBase* m_head;
        NvmshAcObjBase* m_tail;

        void pushBack(NvmshAcObjBase* obj) {
            if (m_tail != nullptr) {
                m_tail->m_next = obj;
                obj->m_prev = m_tail;
                m_tail = obj;
            } else {
                m_head = obj;
                m_tail = obj;
                obj->m_prev = nullptr;
            }
            obj->m_next = nullptr;
        }
        // unlinks obj (objectUpdate; the name is not the original's)
        void remove(NvmshAcObjBase* obj) {
            if (obj->m_prev != nullptr) {
                if (obj->m_next != nullptr) {
                    obj->m_prev->m_next = obj->m_next;
                    obj->m_next->m_prev = obj->m_prev;
                } else {
                    m_tail = obj->m_prev;
                    m_tail->m_next = nullptr;
                }
            } else if (obj->m_next != nullptr) {
                m_head = obj->m_next;
                m_head->m_prev = nullptr;
            } else {
                m_head = nullptr;
                m_tail = nullptr;
            }
            obj->m_prev = nullptr;
            obj->m_next = nullptr;
        }
        void clear() {
            m_tail = nullptr;
            m_head = nullptr;
        }
    };

    NvmshAcMan(NvmshManager* manager, NvmshResMan* resMan, mtl::ALLOC_HANDLE handle);
    ~NvmshAcMan();
    // switches the list createObj adds to (the other one is moved to the active list by the next update)
    void tail();
    void objectUpdate(NvmshResMan* resMan);
    // NvmshManager::jobUpdate's per-frame step, after NvmshResMan::update
    void update(NvmshResMan* resMan);
    NvmshAcObjBase* createObj(mtl::ALLOC_HANDLE handle, NvmshResMan* resMan);
    void releaseObj(NvmshAcObjBase* object);

    NvmshManager* m_manager;
    NvmshAcObjBaseDef* m_objs[256];
    ObjList m_activeList;
    ObjList m_entryLists[2];
    void* m_objBuf;  // the 256 objects m_objs points to
    short m_updateList;  // the entry list update moves to the active list
    short m_entryList;  // the entry list createObj adds to
    NvmshAcObjBaseGbl* m_gbl;
};

}  // namespace navi

#endif
