#ifndef CLASSES_EVENT_LODMANAGER_H
#define CLASSES_EVENT_LODMANAGER_H
#include "classes/event/IManager.h"
#include "classes/mm/mtl/Singleton.h"
#include "mm/mtl/FixedVector.h"
#include "classes/gf/GfGameEvent.h"

namespace event { enum MSG_TYPE : int; }

namespace event {
// table 0x7100B3D250; base at 0x0 event::IManager, base at 0x8 mm::mtl::Singleton<event::LodManager>
class LodManager : public IManager, public mm::mtl::Singleton<LodManager> {
public:
    virtual ~LodManager();  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2

    // 1.0.0's LodManager::Obj (Obj(unsigned int), clear, exec(bool, bool)); playAnm news 0x10-byte ones: flags at
    // 0x0, the map LOD id at 0x4, isMapLodAnimReverse at 0x8, a GfGameEvent value at 0xC
    class Obj {
    public:
        // 1.0.0's Obj(unsigned int) (0x71000E4314; 3.0.1 inlines it: playAnm, setSwitch)
        explicit Obj(unsigned int id) : m_flags(0), m_id(id) {
            m_reverse = gf::GfGameEvent::isMapLodAnimReverse(id);
            m_switch = gf::GfGameEvent::getMapLodSwitch(m_id);
        }
        // 1.0.0's clear (3.0.1 inlines it: OnEventProc): puts back the animation and the switch it changed
        void clear() {
            if (m_flags & 1) {
                gf::GfGameEvent::setMapLodAnim(m_id, m_reverse, true);
            }
            if (m_flags & 2) {
                if (m_switch != -1) {
                    gf::GfGameEvent::setMapLodSwitch(m_id, m_switch);
                }
            }
        }
        // 1.0.0's exec(bool, bool) (3.0.1 inlines it: playAnm)
        void exec(bool reverse, bool skip) {
            if (!skip) {
                gf::GfGameEvent::setMapLodAnim(m_id, !reverse, true);
            }
            gf::GfGameEvent::setMapLodAnim(m_id, reverse, skip);
            m_flags |= 1;
        }

        // the field names are not the original's
        unsigned int m_flags;  // 0x0: bit 0 exec ran (playAnm), bit 1 setSwitch ran
        unsigned int m_id;     // 0x4: the map LOD id
        bool m_reverse;        // 0x8: isMapLodAnimReverse when created
        int m_switch;          // 0xc: getMapLodSwitch when created
    };
    // 1.0.0's searchObj/clear/resetPlayAnm (3.0.1 inlines them; defined inline in CharaObj.cpp)
    Obj* searchObj(unsigned int id);
    void clear();
    void resetPlayAnm();
    void playAnm(unsigned int id, bool reverse, bool skip);
    void setSwitch(unsigned int id, unsigned int value);

    // playAnm finds an id's Obj here or appends a new one; OnEventProc deletes them (the name is not the original's)
    mm::mtl::FixedVector<Obj*, 8> m_objs;  // 0x10 (count at 0x50)
};
}  // namespace event

#endif
