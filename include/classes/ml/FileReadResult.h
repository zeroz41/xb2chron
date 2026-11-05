#ifndef CLASSES_ML_FILEREADRESULT_H
#define CLASSES_ML_FILEREADRESULT_H

namespace ml {
// what DevFileUtilNx::readFile reports (built on the stack by DevFileNxTh::thUpdate; 0x18 bytes as far as known).
// Named by the symbols; the field names are inferred, none is the original's
class FileReadResult {
public:
    FileReadResult() : m_size(-1), m_whole(false), pad_C(0), pad_10(0) {}

    long m_size;  // the bytes read (thUpdate adds them to its request's read size)
    bool m_whole;  // set when the read covers the whole file (thUpdate then sets the request's size too)
    int pad_C;
    int pad_10;
};
}  // namespace ml

#endif
