#ifndef ML_DRENVIRONMENTMAN_H
#define ML_DRENVIRONMENTMAN_H

#include "classes/ml/DrEnvironmentObj.h"

namespace ml {
class DrEnvColiMan;
class DrEnvironmentObj;
class DrFogMan;
class DrLightMan;
class DrMan;

// one per view; DrMan's constructor makes it (0x70 bytes) from the view's DrLightMan and DrFogMan
class DrEnvironmentMan {
public:
    // news a DrEnvironmentObjLgt
    DrEnvironmentMan(DrMan* drMan, DrLightMan* lightMan, DrFogMan* fogMan, int);
    ~DrEnvironmentMan();
    DrEnvironmentObj* createObj(const void* resource);
    void update();

    // a head/tail list of environment objects (the destructor deletes each through its table, walking m_next)
    struct ObjList {
        // deletes every object through its table, walking m_next, and empties the list (inline: no symbol; the
        // name is not the original's)
        void deleteAll() {
            DrEnvironmentObj* obj = m_head;
            while (obj != nullptr) {
                DrEnvironmentObj* next = obj->m_next;
                delete obj;
                obj = next;
            }
            m_head = nullptr;
            m_tail = nullptr;
        }
        DrEnvironmentObj* m_head;
        DrEnvironmentObj* m_tail;
    };

    // the constructor's arguments (the names are not the original's)
    DrMan* m_drMan;              // 0x0
    DrLightMan* m_lightMan;      // 0x8
    DrFogMan* m_fogMan;          // 0x10
    DrEnvColiMan* m_envColiMan;  // 0x18, ScnRenderDrEnvColi's (the name is not the original's)
    int m_lgtArg;                // 0x20, the constructor's last argument; createObj hands it to each light object
    // 0x28: objects by DrMan::s_nDblStockIdx (createObj appends there), then two more lists (names not the original's)
    ObjList m_objList[2];        // 0x28
    ObjList m_subList[2];        // 0x48
    void* m_extra;               // 0x68, when set the destructor releases DrIniSys::m_camLight
};
}  // namespace ml

#endif
