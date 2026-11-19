#ifndef MM_MTL_FIXEDARRAY_H
#define MM_MTL_FIXEDARRAY_H

namespace mm { namespace mtl {

// mm_lib's array of a fixed length N. assign stores a value to every element (FixedArray<Vec3, 20>::assign is
// out of line in ptlib; WindNode's constructor inlines FixedArray<Vec3, 12>'s). It walks a pointer: the loop
// unrolls fully for 20 elements, which keeps the 20-element one out of line; an index loop does not unroll and
// gets inlined into EmitterManager::KizunaWork's constructor. The index operator does not
// check the index (WindBlender::update inlines it without an assertion).
template <typename T, unsigned long N>
class FixedArray {
public:
    void assign(const T& value) {
        for (T* it = begin(); it != end(); ++it) {
            *it = value;
        }
    }
    T& operator[](unsigned long i) { return m_data[i]; }
    const T& operator[](unsigned long i) const { return m_data[i]; }
    // the elements first to last (GfMenuObjPartyForm3's destructor walks its numbers by pointer)
    T* begin() { return m_data; }
    T* end() { return m_data + N; }
    const T* begin() const { return m_data; }
    const T* end() const { return m_data + N; }
    // N (gf::setupItemLists sizes an item type's list by its two arrays' lengths)
    unsigned long size() const { return N; }

    T m_data[N];
};

}}  // namespace mm::mtl

#endif
