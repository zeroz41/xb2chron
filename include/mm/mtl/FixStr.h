#ifndef MM_MTL_FIXSTR_H
#define MM_MTL_FIXSTR_H

#include <string.h>
#include "mm/MMStdBase.h"

// mm_mtl/fixstr.h as its includer's project named it: mm_lib's own (MM_LIB_PROJECT), a library under libs/ that
// reaches it from its own build folder (MM_LIB_FROM_LIBS), or the game's
#if defined(MM_LIB_PROJECT)
#define MM_MTL_FIXSTR_H_FILE "C:/MonolithSoft/BF2/prog/libs/mcl/mm_lib/project/win/../../source\\mm_mtl/fixstr.h"
#elif defined(MM_LIB_FROM_LIBS)
#define MM_MTL_FIXSTR_H_FILE "../../../mcl/mm_lib/source\\mm_mtl/fixstr.h"
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
    explicit FixStr(const char* pszName) { *this = pszName; }
    FixStr& operator=(const char* pszName) {
#line 219 MM_MTL_FIXSTR_H_FILE
        MM_ASSERT(pszName != 0);
        m_nLen = strlen(pszName);
#line 221 MM_MTL_FIXSTR_H_FILE
        MM_ASSERT(m_nLen < LEN);
        strcpy(m_str, pszName);
        return *this;
    }
    FixStr& format(const char* format, ...);
    // pszName appended (WaterInPlugin::onEvent inlines it; the name is not the original's)
    FixStr& operator+=(const char* pszName) {
        int nBackLen = strlen(pszName);
#line 487 MM_MTL_FIXSTR_H_FILE
        MM_ASSERT(m_nLen + nBackLen < LEN);
        strcat(m_str, pszName);
        m_nLen += nBackLen;
        return *this;
    }
    // the index of the last `c`, -1 when there is none (inline: ml::PathUtil::getFsaPath inlines it; the name is
    // not the original's)
    int findLast(char c) const {
        if (m_nLen != 0) {
            const char* p = m_str + m_nLen - 1;
            do {
                if (*p == c) {
                    return p - m_str;
                }
            } while (p-- != m_str);
        }
        return -1;
    }

    char m_str[LEN];  // the text: format() copies what it formats here
    int m_nLen;  // fixstr.h asserts `m_nLen < LEN` as it stores a new text's length
};

}}  // namespace mm::mtl

#endif
