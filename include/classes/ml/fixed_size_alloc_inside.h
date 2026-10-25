#ifndef CLASSES_ML_FIXED_SIZE_ALLOC_INSIDE_H
#define CLASSES_ML_FIXED_SIZE_ALLOC_INSIDE_H

namespace ml {
// a template: 10 instances in the module. N elements in place and a bit per element for the ones in use, reached
// through the two pointers after them (GfPause's constructor and createPauseHandle; the field names are not the
// original's)
template <typename T0, int T1>
class fixed_size_alloc_inside {
public:
    fixed_size_alloc_inside() : m_data(), m_bits() {
        m_words = T1 / 32;
        m_pBits = m_bits;
        m_pData = reinterpret_cast<T0*>(m_data);
        m_count = 0;
    }
    virtual ~fixed_size_alloc_inside() {}  // slot 0

    // the first free element's index, marked in use (1.0.0's GfPause::createPauseHandle inlines it)
    unsigned int alloc() {
        unsigned int* bits = m_pBits;
        for (unsigned int i = 0;; ++i, ++bits) {
            unsigned int word = *bits;
            if (word != 0xFFFFFFFF) {
                unsigned int bit = (word & 0xFFFF) == 0xFFFF ? 16 : 0;
                for (unsigned int mask = 1u << bit; bit < 32; ++bit, mask <<= 1) {
                    if ((mask & word) == 0) {
                        ++m_count;
                        *bits |= mask;
                        return i * 32 + bit;
                    }
                }
            }
        }
    }
    // the element of index back (GfPause::destroyPauseHandle)
    void free(unsigned int index) {
        unsigned int mask = 1u << (index & 31);
        if (m_pBits[index >> 5] & mask) {
            m_pBits[index >> 5] &= ~mask;
            --m_count;
        }
    }
    T0& operator[](unsigned int index) { return m_pData[index]; }
    // a free element marked in use, null when all T1 are (DataParamAcc's setupObjHandle and setupObjId inline it;
    // the names are not the original's)
    T0* allocate() {
        if (static_cast<unsigned int>(m_count) >= T1) {
            return nullptr;
        }
        unsigned int* bits = m_pBits;
        for (unsigned int i = 0; i < m_words; ++i, ++bits) {
            unsigned int word = *bits;
            if (word != 0xFFFFFFFF) {
                unsigned int bit = (word & 0xFFFF) == 0xFFFF ? 16 : 0;
                for (unsigned int mask = 1u << bit; bit < 32; ++bit, mask <<= 1) {
                    if ((mask & word) == 0) {
                        ++m_count;
                        *bits |= mask;
                        return &m_pData[i * 32 + bit];
                    }
                }
            }
        }
        return nullptr;
    }
    // gives an element allocate returned back (~DataParamAcc)
    void deallocate(T0* p) {
        free(static_cast<unsigned long>(reinterpret_cast<char*>(p) - reinterpret_cast<char*>(m_pData)) / sizeof(T0));
    }

    // raw storage: the elements are not constructed (GfSound's constructor only zeroes its SeParams, whose
    // SoundHandle has a user-provided constructor)
    alignas(T0) unsigned char m_data[sizeof(T0) * T1];
    unsigned int m_bits[T1 / 32 + 1];
    unsigned int* m_pBits;
    T0* m_pData;
    int m_words;
    int m_count;
};
}  // namespace ml

#endif
