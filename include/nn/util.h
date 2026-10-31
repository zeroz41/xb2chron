#ifndef NN_UTIL_H
#define NN_UTIL_H

// NintendoSDK 3.5.0's nn::util character conversion and ReferSymbol, as far as the module imports them.
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

}}  // namespace nn::util

#endif
