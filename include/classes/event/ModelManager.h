#ifndef CLASSES_EVENT_MODELMANAGER_H
#define CLASSES_EVENT_MODELMANAGER_H

#include "mm/mtl/FixedVector.h"
#include "classes/event/ModelObj.h"
#include "classes/gf/GfEvtModel.h"
#include "classes/event/IManager.h"
#include "classes/mm/mtl/Singleton.h"

namespace event { enum MSG_TYPE : int; }

namespace event {
// table 0x7100B3C1D8; base at 0x0 event::IManager, base at 0x8 mm::mtl::Singleton<event::ModelManager>
class ModelManager : public IManager, public mm::mtl::Singleton<ModelManager> {
public:
    virtual ~ModelManager();  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
    // 1.0.0's ModelManager::update (0x710009CD78); 3.0.1 inlines it into OnEventProc
    void update() {
        for (unsigned int i = 0; i < m_objs.size(); i++) {
            ModelObj* obj = *m_objs.at(i);
            if (obj->m_model != 0) {
                if (obj->m_busyWait >= 0) {
                    obj->m_busyWait--;
                }
                if (obj->m_model->isBusy(0)) {
                    obj->m_busyWait = 2;
                }
            }
        }
    }

    ModelObj* createModel(const char* name, bool flag, unsigned int arg, int user);
    // the model user does not hold yet that was made so; nullptr when there is none (searchModel's callers)
    ModelObj* searchModel(unsigned int user, const char* name, bool flag, unsigned int arg);
    ModelObj* createModel(const char* name, const ModelObj::DESC& desc, bool flag, unsigned int arg, int user);
    ModelObj* searchModel(unsigned int user, const char* name, const ModelObj::DESC& desc, bool flag,
                          unsigned int arg);
    ModelObj* createModel(MODEL_TYPE type, unsigned int id, const ModelObj::OPTION& option, bool flag,
                          unsigned int arg, int user);
    ModelObj* searchModel(unsigned int user, MODEL_TYPE type, unsigned int id, const ModelObj::OPTION& option,
                          bool flag, unsigned int arg);
    ModelObj* searchModel(unsigned int user);
    ModelObj* createModel(int user);
    // drops user's hold; deletes the model when nobody holds it (or the stream manager's bit 0 is clear)
    void destroyModel(ModelObj* obj, int user);

    // the models createModel made (1024: the count sits at 0x2010); the name is not the original's
    mm::mtl::FixedVector<ModelObj*, 1024> m_objs;  // 0x10
};
}  // namespace event

#endif
