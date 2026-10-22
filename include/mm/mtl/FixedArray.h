#ifndef MM_MTL_FIXEDARRAY_H
#define MM_MTL_FIXEDARRAY_H

namespace mm { namespace mtl {

// mm_lib's array of a fixed length N. assign stores a value to every element (FixedArray<Vec3, 20>::assign is
// out of line in ptlib; WindNode's constructor inlines FixedArray<Vec3, 12>'s); the index operator does not
// check the index (WindBlender::update inlines it without an assertion).
template <typename T, unsigned long N>
class FixedArray {
public:
    void assign(const T& value) {
        for (unsigned long i = 0; i < N; ++i) {
            m_data[i] = value;
        }
    }
    T& operator[](unsigned long i) { return m_data[i]; }
    const T& operator[](unsigned long i) const { return m_data[i]; }

    T m_data[N];
};

}}  // namespace mm::mtl

#endif
