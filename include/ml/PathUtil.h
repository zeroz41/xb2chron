#ifndef ML_PATHUTIL_H
#define ML_PATHUTIL_H

#include <string.h>

#include "mm/mtl/FixStr.h"

namespace ml {
// file path helpers
class PathUtil {
public:
    // `path` as the file system takes it: its drive (up to the last ':') dropped and '\' made '/'
    template <typename STR>
    static bool getFsaPath(STR& out, const char* path) {
        out = path;
        int colon = out.findLast(':');
        if (colon != -1 && out.m_nLen > colon) {
            int next = colon + 1 < out.m_nLen ? colon + 1 : out.m_nLen;
            strcpy(&out.m_str[colon], &out.m_str[next]);
            out.m_nLen = strlen(out.m_str);
        }
        for (int i = 0; i < out.m_nLen; i++) {
            if (out.m_str[i] == '\\') {
                out.m_str[i] = '/';
            }
        }
        return true;
    }
    // path's file name without its folders and extension (fw::SoundPack's constructor keeps it)
    static mm::mtl::FixStr<64> getNoPathExtName(const char* path);
};
}  // namespace ml

#endif
