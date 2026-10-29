#ifndef CLASSES_EVENT_HIDEMANAGER_H
#define CLASSES_EVENT_HIDEMANAGER_H
#include "classes/event/IManager.h"
#include "classes/mm/mtl/Singleton.h"
#include "mm/mtl/FixedVector.h"

namespace event { enum MSG_TYPE : int; }

namespace event {
// table 0x7100B3D178; base at 0x0 event::IManager, base at 0x8 mm::mtl::Singleton<event::HideManager>
class HideManager : public IManager, public mm::mtl::Singleton<HideManager> {
public:
    virtual ~HideManager();  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
    enum GRP_TYPE {};
    void defineGroup(GRP_TYPE group);
    GRP_TYPE getGroup() const;
    // out of line (mm::mtl::Singleton<event::HideManager>::getPtr's static calls it)
    HideManager();
    void hideGroup(bool hide);
    // 1.0.0/3.0.1 symbols name it (event::HideManager::Obj::clear, ::exec); clear() runs Obj::clear and deletes each
    class Obj;

private:
    unsigned int pad_10;
    // the group defineGroup sets and getGroup returns; the name is not the original's
    GRP_TYPE m_group;  // 0x14
    // fields the constructor initializes; what they hold is not known yet
    // the two lists defineList copies in; clear() passes them to gf::GfGameEvent::setDisp (with 6 and 5); the names
    // are not the original's
    mm::mtl::FixedVector<unsigned int, 1024> m_firstList;   // 0x18 (count at 0x1018)
    mm::mtl::FixedVector<unsigned int, 1024> m_secondList;  // 0x1020 (count at 0x2020)
    // the objects hideObj creates; the name is not the original's
    mm::mtl::FixedVector<Obj*, 64> m_objs;  // 0x2028 (count at 0x2228)
};
}  // namespace event

#endif
