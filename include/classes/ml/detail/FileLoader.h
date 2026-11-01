#ifndef CLASSES_ML_DETAIL_FILELOADER_H
#define CLASSES_ML_DETAIL_FILELOADER_H

#include "nn/fs.h"

namespace ml { namespace detail {
// named by the symbols: reads a whole opened file into memory (nnMain calls readFile). The field names are not the
// original's.
class FileLoader {
public:
    ~FileLoader();
    // reads the file m_handle names into a malloc'ed buffer one byte longer than the file; on a failed read the
    // buffer is released and the size cleared
    void readFile();

    nn::fs::FileHandle m_handle;  // 0x0
    bool m_isOpen;                // 0x8 (the destructor closes m_handle when set)
    void* m_buffer;               // 0x10
    long m_size;                  // 0x18
};
}}  // namespace ml::detail

#endif
