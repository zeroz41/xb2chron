#ifndef CLASSES_MM_MTL_SINGLETON_H
#define CLASSES_MM_MTL_SINGLETON_H

namespace mm { namespace mtl {
// a template: the class deriving from it is the instance getPtr keeps as a function-local static
// (_ZZN2mm3mtl9SingletonIN2ai9AiManagerEE6getPtrEvE10s_instance and its guard; btl::BattleManager::Initialize
// constructs ai::AiManager's there); its destructor is inline and stores no table
template <typename T0>
class Singleton {
public:
    virtual ~Singleton() {}  // slot 0
    static T0* getPtr() {
        static T0 s_instance;
        return &s_instance;
    }
};
}}  // namespace mm::mtl

#endif
