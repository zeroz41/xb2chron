#ifndef ML_MLUTF_H
#define ML_MLUTF_H

// monolib's C-linkage text conversions (WinView.cpp defines them; their symbols are unmangled). The header's name
// is not the original's. gf::util::debugUTF8ToSJIS calls both with a size of 0x200, which neither reads.
extern "C" bool mlUTF16toSJIS(char* dst, int size, const unsigned short* src);
extern "C" bool mlUTF8toUTF16(unsigned short* dst, int size, const char* src);

#endif
