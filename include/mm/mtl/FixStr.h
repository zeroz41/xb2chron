#ifndef MM_MTL_FIXSTR_H
#define MM_MTL_FIXSTR_H

#include <string.h>
#include "mm/MMStdBase.h"
#include "mm/mtl/Algorithm.h"

// mm_mtl/fixstr.h as its includer's project named it: mm_lib's own (MM_LIB_PROJECT), eflib's (MM_LIB_FROM_EFLIB:
// ptlib::HeapAllocator::create cites it so), a library under libs/ that
// reaches it from its own build folder (MM_LIB_FROM_LIBS), monolib_mm's own files from monolib_mm's build folder
// (MM_LIB_FROM_MONOLIB_MM: mtl::DlAllocator::create and NullAllocator::create cite it so), or the game's
#if defined(MM_LIB_PROJECT)
#define MM_MTL_FIXSTR_H_FILE "C:/MonolithSoft/BF2/prog/libs/mcl/mm_lib/project/win/../../source\\mm_mtl/fixstr.h"
#elif defined(MM_LIB_FROM_EFLIB)
#define MM_MTL_FIXSTR_H_FILE \
    "D:/Monolithsoft/BF2/prog/libs/eflib/proj/windows/../../../mcl/mm_lib/source\\mm_mtl/fixstr.h"
#elif defined(MM_LIB_FROM_MONOLIB_MM)
#define MM_MTL_FIXSTR_H_FILE \
    "D:/Monolithsoft/BF2/prog/libs/monolib_mm/proj/windows/../../../MCL/mm_lib/source\\mm_mtl/fixstr.h"
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
    // a copy copies the text and its length only (GfEvtBgm's EventBgmSetup copies run strlen and strcpy on the
    // name, then copy the fields after it)
    FixStr(const FixStr& s) { *this = s.m_str; }
    FixStr& operator=(const FixStr& s) { return *this = s.m_str; }
    FixStr& operator=(const char* pszName) {
#line 219 MM_MTL_FIXSTR_H_FILE
        MM_ASSERT(pszName != 0);
        m_nLen = strlen(pszName);
#line 221 MM_MTL_FIXSTR_H_FILE
        MM_ASSERT(m_nLen < LEN);
        strcpy(m_str, pszName);
        return *this;
    }
    // the first len characters of psz, terminated; the length is left as it was (event::Extend::dirname inlines
    // it; fixstr.h asserts `len<LEN` at line 227; the name is not the original's)
    void set(const char* psz, int len) {
#line 227 MM_MTL_FIXSTR_H_FILE
        MM_ASSERT(len<LEN);
        strncpy(m_str, psz, len);
        m_str[len] = '\0';
    }
    // ordered by strcmp (a Map keyed by it compares so: PadRelay's maps; the name is the operator's)
    bool operator<(const FixStr& s) const {
        return strcmp(m_str, s.m_str) < 0;
    }
    FixStr& format(const char* format, ...);
    // empties it: the text's end at the start, then the length (GfEvtSe::destroySe; the name is not the original's)
    void clear() {
        m_str[0] = '\0';
        m_nLen = 0;
    }
    // pszName appended (WaterInPlugin::onEvent inlines it; the name is not the original's)
    FixStr& operator+=(const char* pszBack) {
        // fixstr.h asserts `pszBack != 0` first (GfGameLoad::getGameFileNameBin appends a returned name)
#line 485 MM_MTL_FIXSTR_H_FILE
        MM_ASSERT(pszBack != 0);
        int nBackLen = strlen(pszBack);
#line 487 MM_MTL_FIXSTR_H_FILE
        MM_ASSERT(m_nLen + nBackLen < LEN);
        strcat(m_str, pszBack);
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

    // the len characters from s (all the rest for -1), none from an empty one (fw::LocalizeResource::
    // makeLocalizeFilePath; fixstr.h asserts `s < m_nLen && s+len <= m_nLen`; the name is not the original's)
    FixStr substr(int s, int len = -1) const {
        FixStr result;
        if (m_nLen != 0) {
            if (len == -1) {
                len = m_nLen - s;
            }
#line 462 MM_MTL_FIXSTR_H_FILE
            MM_ASSERT(s < m_nLen && s+len <= m_nLen);
            strncpy(result.m_str, m_str + s, len);
            result.m_str[len] = '\0';
            result.m_nLen = strlen(result.m_str);
        }
        return result;
    }
    // the last n characters dropped, at most all of them (fw::LocalizeResource::makeLocalizeFilePath; the name is
    // not the original's)
    void cutBack(int n) {
        if (m_nLen < n) {
            n = m_nLen;
        }
        if (n > 0) {
            m_nLen -= n;
            m_str[m_nLen] = '\0';
        }
    }

    // the most characters it holds (fixstr.h asserts `newSize < capacity()`; the name is the assertion's)
    int capacity() const { return LEN - 1; }
    // the text's length (the name is not the original's: SCOM_SCRIPT::exec reads it through the string, as a
    // 4-byte-aligned load the next field's load is not merged with)
    int length() const { return m_nLen; }
    // the index of the first `s`, -1 when there is none (gf::fn_71001C0EE0 inlines it; the name is not the
    // original's)
    int find(const char* s) const {
        for (long i = 0; i < m_nLen; ++i) {
            if (strncmp(m_str + i, s, strlen(s)) == 0) {
                return i;
            }
        }
        return -1;
    }
    // the first n characters dropped, at most all of them (gf::fn_71001C0EE0 inlines it; the name is not the
    // original's)
    void cutFront(int n) {
        n = n < m_nLen ? n : m_nLen;
        strcpy(m_str, m_str + n);
        m_nLen = strlen(m_str);
    }
    // n characters of pszStr inserted at index (fixstr.h asserts `pszStr`, `newSize < capacity()` and
    // `index <= nowSize`; the name is the symbol's)
    FixStr& insert(int index, const char* pszStr, int n);

    char m_str[LEN];  // the text: format() copies what it formats here
    int m_nLen;  // fixstr.h asserts `m_nLen < LEN` as it stores a new text's length
};

template <int LEN>
FixStr<LEN>& FixStr<LEN>::insert(int index, const char* pszStr, int n) {
#line 715 MM_MTL_FIXSTR_H_FILE
    MM_ASSERT(pszStr);
    int nowSize = m_nLen;
    int newSize = nowSize + n;
#line 725 MM_MTL_FIXSTR_H_FILE
    MM_ASSERT(newSize < capacity());
#line 726 MM_MTL_FIXSTR_H_FILE
    MM_ASSERT(index <= nowSize);
    char* p = m_str + index;
    move_n(p, nowSize - index, p + n);
    copy_n(pszStr, n, p);
    m_nLen = newSize;
    m_str[newSize] = '\0';
    return *this;
}

}}  // namespace mm::mtl

#endif
