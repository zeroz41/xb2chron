#ifndef CLASSES_ML_SCNPOOLOBJ_H
#define CLASSES_ML_SCNPOOLOBJ_H

#include "classes/ml/IScnRender.h"
#include "classes/ml/IWorkEvent.h"
#include "classes/ml/reslist.h"
#include "ml/CriticalSection.h"
#include "classes/ml/ScnObjCam.h"

namespace ml { class Scn; }
namespace ml { class ScnObj; }
namespace ml { class WinView; }

namespace ml {
// table 0x7100B78078
class ScnPoolObj : public ::ml::IWorkEvent, public ::ml::IScnRender {
public:
    virtual ~ScnPoolObj();  // slot 0
    void release(ScnObj* item);
    // ScnObjModelDrSysStandard::create asks it for room for one before it makes a model (the parameter name is not
    // the original's)
    bool isValidInsert(unsigned short num) const;
    void insert(ScnObj* item);
    // ScnObjLightDrSys's constructor releases the view's fast light when this is false
    bool isExistLgtEnv() const;
    // the camera numbered index: the cameras' list's, else a camera among all objects; none without one (1.0.0
    // keeps it out of line; 3.0.1's Scn::getCam inlines it)
    ScnObjCam* getCam(int index) {
        CS cs(m_cs);
        for (reslist<ScnObj*>::iterator it = m_cam.begin(); it != m_cam.end(); ++it) {
            ScnObjCam* cam = static_cast<ScnObjCam*>(*it);
            if (cam->m_index == index) {
                return cam;
            }
        }
        for (reslist<ScnObj*>::iterator it = m_all.begin(); it != m_all.end(); ++it) {
            ScnObj* obj = *it;
            if (obj->m_type == 2 && static_cast<ScnObjCam*>(obj)->m_index == index) {
                return static_cast<ScnObjCam*>(obj);
            }
        }
        return nullptr;
    }
    // the camera whose slot shows the view; none for no view
    ScnObjCam* getCam(const WinView* view);
    // the list of the objects of a type (ScnObj::m_type 1 to 6), none for another (1.0.0 keeps both out of line;
    // 3.0.1 inlines them)
    reslist<ScnObj*>* getList(unsigned short type) {
        switch (type) {
        case 1:
            return &m_mdl;
        case 2:
            return &m_cam;
        case 3:
            return &m_list3;
        case 4:
            return &m_lgt;
        case 5:
            return &m_ibl;
        case 6:
            return &m_list6;
        }
        return nullptr;
    }
    const reslist<ScnObj*>* getList(unsigned short type) const {
        switch (type) {
        case 1:
            return &m_mdl;
        case 2:
            return &m_cam;
        case 3:
            return &m_list3;
        case 4:
            return &m_lgt;
        case 5:
            return &m_ibl;
        case 6:
            return &m_list6;
        }
        return nullptr;
    }

    CriticalSection m_cs0;  // 0x10 (the name is not the original's)
    // 0x38 isValidInsert, isExistLgtEnv and getCam hold it (the name is not the original's)
    CriticalSection m_cs;
    Scn* m_scn;  // 0x60 the constructor's (the name is not the original's)
    // 0x68 one list per object type (getList's): cameras (2: Scn::getCam walks it), models (1), type 3, lights
    // (4: isExistLgtEnv walks it), image-based lights (5), type 6 (clip lists and environment collision); the
    // constructor gives them 10 to 0x200 nodes (the names are not the original's)
    reslist<ScnObj*> m_cam;
    reslist<ScnObj*> m_mdl;    // 0xA8
    reslist<ScnObj*> m_list3;  // 0xE8
    reslist<ScnObj*> m_lgt;    // 0x128
    reslist<ScnObj*> m_ibl;    // 0x168
    reslist<ScnObj*> m_list6;  // 0x1A8
    // 0x1E8 objects of any type: Scn::getCam looks for a camera here after m_cam (the name is not the original's)
    reslist<ScnObj*> m_all;
};
}  // namespace ml

#endif
