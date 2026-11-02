#ifndef MTL_MEMORYINFO1_H
#define MTL_MEMORYINFO1_H

namespace mtl {

// one allocation as getMemInfo1 reports it, written into an array of the caller's (the struct name is the
// original's, from the slot's signature; the field names are inferred)
struct MemoryInfo1 {
    void* m_addr;
    unsigned long m_size;
    const char* m_file;  // the allocating file ("" or "noname" when unknown)
    unsigned int m_line;
};

}  // namespace mtl

#endif
