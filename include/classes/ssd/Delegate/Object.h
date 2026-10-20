#ifndef CLASSES_SSD_DELEGATE_OBJECT_H
#define CLASSES_SSD_DELEGATE_OBJECT_H

namespace ssd { namespace Delegate { class Handle; }}

namespace ssd { namespace Delegate {
// a template: 1 instances in the module
template <typename T0, typename T1, typename T2>
class Object {
public:
    virtual ~Object();  // slot 0
    virtual void ExecuteDelegate(unsigned long long, unsigned long long);  // slot 2
    virtual void operator==(ssd::Delegate::Handle const*) const;  // slot 3
};
}}  // namespace ssd::Delegate

#endif
