#ifndef MM_MTL_RESERVEDBITFLAG_H
#define MM_MTL_RESERVEDBITFLAG_H

namespace mm { namespace mtl {

class IAllocator;

// a run of bit flags in words taken from an allocator
class ReservedBitflag {
public:
    ReservedBitflag();
    ~ReservedBitflag();
    void setLocal(unsigned int index, bool flag);
    bool getLocal(unsigned int index) const;
    void clrLocal(unsigned int index);
    void clrLocal();
    void destroy();
    void initialize(IAllocator* allocator, unsigned int size);
    void set(unsigned int start, unsigned int last, bool flag);

    unsigned int* m_element;
    unsigned int m_size;  // flags
    unsigned int m_elementNum;  // words in m_element
    IAllocator* m_allocator;
};

}}  // namespace mm::mtl

#endif
