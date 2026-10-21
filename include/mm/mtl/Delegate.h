#ifndef MM_MTL_DELEGATE_H
#define MM_MTL_DELEGATE_H

namespace mm { namespace mtl {

// mm_lib's delegate: an object, the invoker its member function's class instantiates, and that member function
template <typename Signature>
class Delegate;

template <typename R, typename... Args>
class Delegate<R(Args...)> {
public:
    typedef R (*Invoker)(const Delegate*, Args...);

    Delegate() : m_invoker(nullptr) {}

    template <typename T>
    void set(T* object, R (T::*func)(Args...)) {
        m_func = reinterpret_cast<R (Delegate::*)(Args...)>(func);
        m_object = object;
        m_invoker = &memberFuncInvoker<T>;
    }
    bool isValid() const {
        return m_invoker != nullptr;
    }
    R operator()(Args... args) const {
        return m_invoker(this, args...);
    }

    template <typename T>
    static R memberFuncInvoker(const Delegate* delegate, Args... args) {
        T* object = static_cast<T*>(delegate->m_object);
        return (object->*reinterpret_cast<R (T::*)(Args...)>(delegate->m_func))(args...);
    }

    void* m_object;
    Invoker m_invoker;
    R (Delegate::*m_func)(Args...);  // the member function, of the object's class
};

}}  // namespace mm::mtl

#endif
