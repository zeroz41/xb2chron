#ifndef MM_MTL_RTTI_H
#define MM_MTL_RTTI_H

namespace mm { namespace mtl {

// a class's own runtime type: its name and the types it derives from (up to two). A class holds one as its
// static m_rtti, returned by its getRTTI(); isKindOf walks the bases.
class RTTI {
public:
    // The original's constructor is not one clang can evaluate while compiling (a loop), so every class's
    // m_rtti stays in .bss and its unit's static initializer stores it: name first, then the bases last to
    // first. A loop-free one is folded into initialized data instead.
    RTTI(const char* name, const RTTI* base, const RTTI* base2) : m_name(name) {
        for (int i = 0; i < 2; i++) {
            m_bases[i] = nullptr;
        }
        if (base != nullptr) {
            m_bases[0] = base;
        }
        if (base2 != nullptr) {
            m_bases[1] = base2;
        }
    }
    bool isKindOf(const RTTI* rtti) const;

    const char* m_name;
    const RTTI* m_bases[2];  // isKindOf follows each one that is set
};

// p as a T when its runtime type is T or derives from it, none otherwise (inline: the name is not the original's).
// It takes a pointer: a cast of a reference's address through it keeps the test of its result for none, which the
// field AI's tasks show (their blackboard casts test the cast pointer, not isKindOf's answer)
template <typename T, typename U>
inline T* rttiCast(U* p) {
    return p->getRTTI()->isKindOf(&T::m_rtti) ? static_cast<T*>(p) : nullptr;
}

}}  // namespace mm::mtl

#endif
