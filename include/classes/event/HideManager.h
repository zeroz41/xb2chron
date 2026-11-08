#ifndef CLASSES_EVENT_HIDEMANAGER_H
#define CLASSES_EVENT_HIDEMANAGER_H
#include "classes/event/IManager.h"
#include "classes/mm/mtl/Singleton.h"
#include "mm/mtl/FixedVector.h"
#include "mm/mtl/Bitflag.h"
#include "classes/gf/GfGameEvent.h"

namespace event { enum MSG_TYPE : int; }

namespace event {
// table 0x7100B3D178; base at 0x0 event::IManager, base at 0x8 mm::mtl::Singleton<event::HideManager>
class HideManager : public IManager, public mm::mtl::Singleton<HideManager> {
public:
    virtual ~HideManager();  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
    enum GRP_TYPE {};
    // 1.0.0's symbols name it (hideObj, searchObj, Obj::Obj take it); the values are Obj's types (1-7)
    enum OBJ_TYPE : int;
    void defineGroup(GRP_TYPE group);
    GRP_TYPE getGroup() const;
    // out of line (mm::mtl::Singleton<event::HideManager>::getPtr's static calls it)
    HideManager();
    void hideGroup(bool hide);
    // 1.0.0/3.0.1 symbols name it (event::HideManager::Obj::clear, ::exec); clear() runs Obj::clear and deletes each
    class Obj {
    public:
        // 1.0.0's Obj(OBJ_TYPE, unsigned int) (0x71000E1DF8; 3.0.1 inlines it in hideObj)
        Obj(OBJ_TYPE type, unsigned int id) : m_type(type), m_id(id), m_baseHide(false), m_hide(false) {
            switch (type) {
            case 1:
                m_baseHide = false;
                break;
            case 2:
                m_baseHide = false;
                break;
            case 3:
                m_baseHide = false;
                break;
            case 4:
                m_baseHide = false;
                break;
            case 5:
                m_baseHide = false;
                break;
            case 6:
                m_baseHide = !gf::GfGameEvent::isMapLodDisp(id);
                break;
            case 7:
                m_baseHide = false;
                break;
            }
            m_hide = m_baseHide;
        }
        void clear();
        void exec(bool hide);

        // the field names are not the original's: clear() shows the object again by the state in m_baseHide,
        // exec(hide) shows it unless hidden and records hide in m_hide
        int m_type;           // 0x0: which setGmk*Disp/setMapLodDisp call (1-7)
        unsigned int m_id;    // 0x4
        bool m_baseHide;      // 0x8
        bool m_hide;          // 0x9
    };
    void clear();
    // 1.0.0's hideList/resetHideObj/searchObj (3.0.1 inlines them; defined inline in CharaObj.cpp)
    void hideList(bool hide);
    void resetHideObj();
    Obj* searchObj(OBJ_TYPE type, unsigned int id);
    void defineList(mm::mtl::FixedVector<unsigned int, 256> first, mm::mtl::FixedVector<unsigned int, 256> second);
    void hideObj(OBJ_TYPE type, unsigned int id, bool hide);

    // one entry per group bit: the display kind's name and value; the type's name is not the original's
    struct DispEntry {
        const char* m_name;
        gf::EVTDISP m_disp;
    };
    static DispEntry s_tbl[18];

private:
    // bit 0: hideGroup(true) ran; bit 1: the lists are hidden (clear() shows them again); the name is not the
    // original's. A Bitflag word: hideGroup loads it apart from m_group (a raw int merges the two loads)
    mm::mtl::Bitflag<32> m_flags;  // 0x10
    // the group defineGroup sets and getGroup returns; hideGroup tests one bit per table entry; the name is not the
    // original's
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
