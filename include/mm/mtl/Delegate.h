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
        m_object = object;
        m_func = reinterpret_cast<R (Delegate::*)(Args...)>(func);
        m_invoker = &memberFuncInvoker<T>;
    }
    // a plain function in place of a member function (MicroUpdater's: tl::TitleMain::initialize stores
    // staticFuncInvoker and the function, the function in the member function's first word)
    void set(R (*func)(Args...)) {
        m_staticFunc = func;
        m_invoker = &staticFuncInvoker;
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

    // a plain function's invoker (1.0.0's symbol names it)
    static R staticFuncInvoker(const Delegate* delegate, Args... args) {
        return delegate->m_staticFunc(args...);
    }

    void* m_object;
    Invoker m_invoker;
    union {
        R (Delegate::*m_func)(Args...);  // the member function, of the object's class
        R (*m_staticFunc)(Args...);      // or a plain function (the name is not the original's)
    };
};

}}  // namespace mm::mtl

#endif
