#ifndef CLASSES_EVENT_OBJECTMANAGER_H
#define CLASSES_EVENT_OBJECTMANAGER_H

#include "classes/mm/mtl/Singleton.h"
#include "classes/event/Object.h"
#include "classes/event/ObjectList.h"
#include "mm/mtl/FixStr.h"
#include "mm/mtl/FixedVector.h"

namespace event { enum MSG_TYPE : int; }

namespace event {
// a base of event::ObjectManager no evidence names yet
class TUnk_B3E118 {
public:
    virtual ~TUnk_B3E118();
    virtual void OnEventProc(event::MSG_TYPE) = 0;
};
// a base of event::ObjectManager no evidence names yet
class TUnk_B3E140 {
public:
    virtual ~TUnk_B3E140();
};
// table 0x7100B3E118; base at 0x0 unknown (TUnk_B3E118), base at 0x8 unknown (TUnk_B3E140); the instance is
// mm::mtl::Singleton<event::ObjectManager>::getPtr's static
class ObjectManager : public TUnk_B3E118, public TUnk_B3E140 {
public:
    // 1.0.0 has it out of line (0x710011C8C0, same stores); 3.0.1 inlines it into getPtr's static
    ObjectManager() : m_flags(0), pad_14(0), m_sceneName("default") {}
    virtual ~ObjectManager();  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
    // the current scene's active object when it is of the given type (Object::m_type), else null; the current
    // scene is not updated first (the script commands' undo and redo inline it); the name is not the original's
    Object* getActive(int type) const {
        if (m_current != 0) {
            Object* obj = m_current->m_active;
            if (obj != 0 && obj->m_type == type) {
                return obj;
            }
        }
        return 0;
    }

    // bit 0 is passed to each new ObjectList (1.0.0's createScene); the name is not the original's
    unsigned int m_flags;  // 0x10
    // zeroed with m_flags (one 64-bit store with the second table pointer); no reader seen yet
    unsigned int pad_14;   // 0x14
    // the scenes 1.0.0's createScene adds and updateCurrent searches by name; the name is not the original's
    mm::mtl::FixedVector<ObjectList*, 16> m_scenes;  // 0x18 (size 0x98)
    // the scene updateCurrent makes current ("default" at first); the name is not the original's
    mm::mtl::FixStr<64> m_sceneName;               // 0xa0
    // the name of the current scene (updateCurrent copies m_sceneName here); the name is not the original's
    mm::mtl::FixStr<64> m_currentName;             // 0xe4
    ObjectList* m_current;                         // 0x128 (1.0.0's getCurrent returns it)
};
}  // namespace event

#endif
