#ifndef CLASSES_EVENT_LODMANAGER_H
#define CLASSES_EVENT_LODMANAGER_H
#include "classes/event/IManager.h"
#include "classes/mm/mtl/Singleton.h"
#include "mm/mtl/FixedVector.h"

namespace event { enum MSG_TYPE : int; }

namespace event {
// table 0x7100B3D250; base at 0x0 event::IManager, base at 0x8 mm::mtl::Singleton<event::LodManager>
class LodManager : public IManager, public mm::mtl::Singleton<LodManager> {
public:
    virtual ~LodManager();  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2

    // 1.0.0's LodManager::Obj (Obj(unsigned int), clear, exec(bool, bool)); playAnm news 0x10-byte ones: flags at
    // 0x0, the map LOD id at 0x4, isMapLodAnimReverse at 0x8, a GfGameEvent value at 0xC
    class Obj;

    // playAnm finds an id's Obj here or appends a new one; OnEventProc deletes them (the name is not the original's)
    mm::mtl::FixedVector<Obj*, 8> m_objs;  // 0x10 (count at 0x50)
};
}  // namespace event

#endif
