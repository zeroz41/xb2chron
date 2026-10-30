#ifndef CLASSES_SSD_DELEGATE_OBJECT_H
#define CLASSES_SSD_DELEGATE_OBJECT_H

#include "classes/ssd/Delegate/MultiCast.h"
#include "ssd/Debug.h"

namespace ssd { namespace Delegate {
// a template: 1 instances in the module. A Handle calling a member function of an object: the notification's two
// words become the function's two arguments after the handle itself. Its destructor is Node's (the table's slot 0)
// (the member names are not the original's)
template <typename T0, typename T1, typename T2>
class Object : public Handle {
public:
    typedef Result (T0::*Method)(Handle*, T1, T2);

    Object(T0* object, Method method) : object_(object), method_(method) {}

    virtual Result ExecuteDelegate(unsigned long long first, unsigned long long second) {  // slot 2
        return (object_->*method_)(this, (T1)first, (T2)second);
    }
    virtual bool operator==(const Handle* other) const {  // slot 3
        const Object* object = static_cast<const Object*>(other);
        return object->object_ == object_ && object->method_ == method_;
    }

    T0* object_;  // 0x18
    Method method_;  // 0x20
};
}}  // namespace ssd::Delegate

#endif
