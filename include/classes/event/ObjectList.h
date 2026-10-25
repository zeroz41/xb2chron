#ifndef CLASSES_EVENT_OBJECTLIST_H
#define CLASSES_EVENT_OBJECTLIST_H

namespace event { class Object; }

namespace event {
// table 0x7100B3E0F8
class ObjectList {
public:
    virtual ~ObjectList();  // slot 0
    unsigned char pad_8[0x70];
    // the object the script commands act on (ScriptSetActive's doit sets it); the name is not the original's
    Object* m_active;  // 0x78
};
}  // namespace event

#endif
