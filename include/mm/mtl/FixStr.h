#ifndef MM_MTL_FIXSTR_H
#define MM_MTL_FIXSTR_H

#include <string.h>
#include "mm/MMStdBase.h"

// mm_mtl/fixstr.h as its includer's project named it: mm_lib's own (MM_LIB_PROJECT) or the game's
#ifdef MM_LIB_PROJECT
#define MM_MTL_FIXSTR_H_FILE "C:/MonolithSoft/BF2/prog/libs/mcl/mm_lib/project/win/../../source\\mm_mtl/fixstr.h"
#else
#define MM_MTL_FIXSTR_H_FILE "D:/Monolithsoft/BF2/prog/application/BF2//../../libs/mcl/mm_lib/source\\mm_mtl/fixstr.h"
#endif

namespace mm { namespace mtl {

// a string in a fixed buffer of LEN characters (the original's mm_mtl/fixstr.h)
template <int LEN>
class FixStr {
public:
    FixStr() {
        m_str[0] = '\0';
        m_nLen = 0;
    }
    FixStr& operator=(const char* pszName) {
#line 219 MM_MTL_FIXSTR_H_FILE
        MM_ASSERT(pszName != 0);
        m_nLen = strlen(pszName);
        MM_ASSERT(m_nLen < LEN);
        strcpy(m_str, pszName);
        return *this;
    }
    FixStr& format(const char* format, ...);

    char m_str[LEN];  // the text: format() copies what it formats here
    int m_nLen;  // fixstr.h asserts `m_nLen < LEN` as it stores a new text's length
};

}}  // namespace mm::mtl

#endif
