#ifndef WND_ARRAY_H
#define WND_ARRAY_H

#include "mm/MMStdBase.h"

namespace wnd {
// wndlib's view of elements kept elsewhere (wnd_array-inl.h asserts `m_pElements` and `index < m_size` as it
// indexes one); empty as constructed (DynamicWindResource's constructor clears its resource's)
template <typename T>
class Array {
public:
    Array() : m_pElements(nullptr), m_size(0) {}
    const T& operator[](unsigned int index) const {
#line 231 "../../src\\wndlib/base/wnd_array-inl.h"
        MM_ASSERT(m_pElements);
#line 232 "../../src\\wndlib/base/wnd_array-inl.h"
        MM_ASSERT(index < m_size);
        return m_pElements[index];
    }

    T* m_pElements;
    unsigned int m_size;
};
}  // namespace wnd

#endif
