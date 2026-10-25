#ifndef CLASSES_EVENT_SCRIPTUTIL_H
#define CLASSES_EVENT_SCRIPTUTIL_H

namespace event {
class Object;

// helpers of the event script commands (no table)
class ScriptUtil {
public:
    // the object's kind (Object::m_type); the evt_chara commands test 2 before treating it as an ObjectChara
    static int getObjType(Object* obj);
};
}  // namespace event

#endif
