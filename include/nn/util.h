#ifndef NN_UTIL_H
#define NN_UTIL_H

// NintendoSDK 3.5.0's nn::util character conversion, zlib and ReferSymbol, as far as the module imports them.
namespace nn { namespace util {

// keeps the symbol (a middleware info string) from being discarded by the linker
void ReferSymbol(const void* pSymbol);

enum CharacterEncodingResult {
    CharacterEncodingResult_Success,
    CharacterEncodingResult_InsufficientLength,
    CharacterEncodingResult_InvalidFormat,
};

CharacterEncodingResult ConvertStringUtf8ToUtf16Native(unsigned short* pOutDst, int dstLength, const char* pSrc);
CharacterEncodingResult ConvertStringUtf16NativeToUtf8(char* pOutDst, int dstLength, const unsigned short* pSrc);
CharacterEncodingResult GetLengthOfConvertedStringUtf8ToUtf16Native(int* pOutLength, const char* pSrc,
                                                                    int srcLength);
CharacterEncodingResult GetLengthOfConvertedStringUtf16NativeToUtf8(int* pOutLength, const unsigned short* pSrc,
                                                                    int srcLength);

// zlib streams: CompressZlib writes at most outCapacity bytes and their count; both use the caller's work memory
bool CompressZlib(unsigned long* pOutSize, void* pOut, unsigned long outCapacity, const void* pSrc,
                  unsigned long srcSize, void* pWork, unsigned long workSize);
bool DecompressZlib(void* pOut, unsigned long outSize, const void* pSrc, unsigned long srcSize, void* pWork,
                    unsigned long workSize);

}}  // namespace nn::util

#endif
