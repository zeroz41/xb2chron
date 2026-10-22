#ifndef ANM_ARRAY_H
#define ANM_ARRAY_H

#include "mm/MMStdBase.h"

// anmlib's anm_array-inl.h, as the including file's include path named it
#define ANM_ARRAY_PATH "D:/Monolithsoft/BF2/prog/application/BF2//../../libs/anmlib/src\\anmlib/base/anm_array-inl.h"

namespace anm {
// anmlib's view of elements kept elsewhere (a resource's): indexing one asserts `m_pElements` and
// `index < m_size` (anm_array-inl.h lines 231 and 232)
template <typename T>
class Array {
public:
    unsigned int size() const { return m_size; }
    const T& operator[](unsigned int index) const {
#line 231 ANM_ARRAY_PATH
        MM_ASSERT(m_pElements);
#line 232 ANM_ARRAY_PATH
        MM_ASSERT(index < m_size);
        return m_pElements[index];
    }

    T* m_pElements;
    unsigned int m_size;
};
}  // namespace anm

#endif
