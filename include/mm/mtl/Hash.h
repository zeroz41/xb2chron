#ifndef MM_MTL_HASH_H
#define MM_MTL_HASH_H

namespace mm { namespace mtl {

// a string's CRC-32 (the module's CRC table), 0 for none or an empty one
unsigned int hashStrCrc(const char* str);

}}  // namespace mm::mtl

#endif
