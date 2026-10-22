#ifndef WND_ARRAY_H
#define WND_ARRAY_H

namespace wnd {
// wndlib's view of elements kept elsewhere (wnd_array-inl.h asserts `m_pElements` and `index < m_size` as it
// indexes one); empty as constructed (DynamicWindResource's constructor clears its resource's)
template <typename T>
class Array {
public:
    Array() : m_pElements(nullptr), m_size(0) {}

    T* m_pElements;
    unsigned int m_size;
};
}  // namespace wnd

#endif
