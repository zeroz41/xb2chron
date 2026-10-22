#ifndef CLASSES_AI_AIMANAGER_H
#define CLASSES_AI_AIMANAGER_H

#include "classes/gf/IGfObjListener.h"
#include "classes/mm/mtl/Singleton.h"
#include "mm/mtl/FixedList.h"

namespace fw { class UpdateInfo; }
namespace ai { class AiData; }

namespace ai {
// table 0x7100B3A360; the AI of the objects in battle, one ai::AiData each (regist/unregist), told by
// gf::GfObjManager when an object goes (listenerGfObj)
class AiManager : public ::mm::mtl::Singleton< ::ai::AiManager>, public ::gf::IGfObjListener {
public:
    // the list type 1.0.0's FixedList<ai::AiData*, 128>::erase names (the typedef's name is not the original's)
    typedef mm::mtl::FixedList<AiData*, 128> DataList;

    // btl::BattleManager::Initialize constructs it inline in Singleton::getPtr's static
    AiManager() {}
    virtual ~AiManager();  // slot 0
    virtual void listenerGfObj(gf::IGfObjListener::OBJEVT evt, gf::GF_OBJ_HANDLE* handle, unsigned int);  // slot 2

    void init();
    void destroy();
    void update(const fw::UpdateInfo& info);
    void regist(gf::GF_OBJ_HANDLE* handle, int id);
    void unregist(gf::GF_OBJ_HANDLE* handle);
    AiData* getDataFromHandle(gf::GF_OBJ_HANDLE* handle);
    AiData* getDataFromId(int id, int index);  // the index-th of the data of that id
    int getNumFromId(int id);

private:
    void _clear();

public:
    DataList m_dataList;  // the name is not the original's
};
}  // namespace ai

#endif
