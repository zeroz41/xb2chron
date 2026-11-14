#ifndef MM_MTL_STRUTIL_H
#define MM_MTL_STRUTIL_H

#include <string.h>
#include "mm/MMStdBase.h"

// mm_lib's mm_mtl/str_util.h, as the game's include path named it (replacestr's assertions cite it so)
#define MM_MTL_STR_UTIL_PATH "D:/Monolithsoft/BF2/prog/application/BF2//../../libs/mcl/mm_lib/source\\mm_mtl/str_util.h"

namespace mm { namespace mtl {

// every srcPattern in str replaced with dstPattern, left to right, the search going on after each replacement
// (the name is the symbol's; its assertions name srcPattern and dstPattern)
template <typename S>
void replacestr(S& str, const char* srcPattern, const char* dstPattern) {
#line 64 MM_MTL_STR_UTIL_PATH
    MM_ASSERT(srcPattern);
#line 65 MM_MTL_STR_UTIL_PATH
    MM_ASSERT(dstPattern);
    S src(srcPattern);
    S dst(dstPattern);
    int pos = 0;
    while (str.m_nLen > pos) {
        int len = strlen(src.m_str);
        // the first srcPattern from start on, -1 when there is none (an inline search the original's codegen shows)
        int index = [&](int start) -> int {
            for (long i = start; i < str.m_nLen; ++i) {
                if (strncmp(str.m_str + i, src.m_str, len) == 0) {
                    return i;
                }
            }
            return -1;
        }(pos);
        if (index == -1) {
            break;
        }
        int n = src.m_nLen;
        if (n == -1) {
            if (str.m_nLen > index) {
                str.m_str[index] = '\0';
                str.m_nLen = index;
            }
        } else if (str.m_nLen > index) {
            int end = index + n < str.m_nLen ? index + n : str.m_nLen;
            strcpy(str.m_str + index, str.m_str + end);
            str.m_nLen = strlen(str.m_str);
        }
        str.insert(index, dst.m_str, dst.m_nLen);
        pos = index + dst.m_nLen;
    }
}

}}  // namespace mm::mtl

#endif
