#ifndef CLASSES_EVENT_MDLSTMMANAGER_H
#define CLASSES_EVENT_MDLSTMMANAGER_H
#include "classes/event/IManager.h"
#include "classes/mm/mtl/Singleton.h"
#include "classes/event/MdlstmObj.h"
#include "mm/mtl/FixedVector.h"

namespace event { enum MSG_TYPE : int; }

namespace event {
// table 0x7100B3C510; base at 0x0 event::IManager, base at 0x8 mm::mtl::Singleton<event::MdlstmManager>
class MdlstmManager : public IManager, public mm::mtl::Singleton<MdlstmManager> {
public:
    // inline: D2/D0 sit in CharaObj's tail, so OnEventProc is the key function
    // inline: Singleton<MdlstmManager>::getPtr constructs the instance (ModelManager::createModel)
    MdlstmManager() : pad_10(0), pad_14(0), pad_3c018(0) {}
    virtual ~MdlstmManager() {}  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
    void update();
    void clear();

    // layout from the destructor: the list is cleared, then the objects are destroyed; names are not the original's
    unsigned int pad_10;
    // bit 0: ModelManager's createModel overloads first look for a model to share (searchModel)
    unsigned int pad_14;
    MdlstmObj m_objs[1024];  // @0x18
    unsigned int pad_3c018;
    mm::mtl::FixedVector<MdlstmObj*, 1024> m_active;  // @0x3C020, count @0x3E020
    unsigned int pad_3e028;
    unsigned int pad_3e02c;
    unsigned int pad_3e030;
};
}  // namespace event

#endif
