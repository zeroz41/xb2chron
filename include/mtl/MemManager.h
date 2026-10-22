#ifndef MTL_MEMMANAGER_H
#define MTL_MEMMANAGER_H

namespace mtl {

// monolib's memory manager (its functions, by its symbols)
class MemManager {
public:
    static void deallocate(void* p, unsigned long size, bool flag);
};

}  // namespace mtl

#endif
