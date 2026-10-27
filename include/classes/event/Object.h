#ifndef CLASSES_EVENT_OBJECT_H
#define CLASSES_EVENT_OBJECT_H

#include "classes/event/IBouCallback.h"
#include "classes/event/IManiCallback.h"
#include "mm/mtl/FixStr.h"

namespace mm { class Col4; }

namespace event {
// table 0x7100B3DBF0
class Object : public ::event::IBouCallback, public ::event::IManiCallback {
public:
    virtual ~Object();  // slot 0
    // clear..tail are empty but out of line: CharaObj.cpp defines each right after ObjectChara's override
    virtual void clear();  // slot 4
    virtual void start();  // slot 5
    virtual void end();  // slot 6
    virtual void update();  // slot 7
    virtual void render(mm::Col4 const&);  // slot 8
    virtual void tail();  // slot 9
    virtual bool isLoading() const { return false; }  // slot 10
    // what kind of object it is: the script commands test 2 before treating it as an ObjectChara and 4 before an
    // ObjectEffect; the name is not the original's
    int m_type;  // 0x10
    // the object at path ("name/child/..." below this one), or null
    Object* searchByPath(const char* path);
    // the object's name (1.0.0's Object(OBJTYPE, const char*) copies it in; searchByPath compares paths with it);
    // the field names are not the original's
    mm::mtl::FixStr<64> m_name;  // 0x14
    Object* m_child;  // 0x58; the first child (~Object deletes the chain)
    Object* m_next;  // 0x60; the next sibling
};
}  // namespace event

#endif
