#ifndef ML_DEVFILEPARAMTH_H
#define ML_DEVFILEPARAMTH_H

#include "mtl/AllocHandle.h"

namespace ml { class IWorkEvent; }
namespace ml { enum FILE_PRIO : int; }  // 10 by default (cloud::CloudDataMan's reads keep it)

namespace ml {

// what DevFileTh::readFile reads (no table; 0x70 bytes: fw::ScriptInfo::load and gf::GfGameLoad build one on the
// stack with the same defaults). FileHandleTh::setup takes the path, buffer, size and listener from it. The field
// names are not the original's.
class DevFileParamTh {
public:
    DevFileParamTh()
        : m_path(nullptr), m_hMem(), pad_10(nullptr), pad_38(nullptr), m_buffer(nullptr), pad_4c(0), pad_50(0), m_align(0),
          pad_58(1), pad_5c(0), m_listener(nullptr), m_prio(FILE_PRIO(10)), pad_6c(true), pad_6d(false), pad_6e(false), pad_6f(false) {}
    // clears the pointer at 0x38 (what it holds is not known)
    ~DevFileParamTh() {
        if (pad_38 != nullptr) {
            pad_38 = nullptr;
        }
    }

    const char* m_path;  // the file (FileHandleTh::setup asserts it)
    mtl::ALLOC_HANDLE m_hMem;  // where the data is allocated (cloud::CloudDataMan passes CloudMan's data handle)
    void* pad_10;
    unsigned char pad_18[0x20];
    void* pad_38;
    void* m_buffer;  // where the file is read to
    unsigned int m_size;  // the buffer's size (the constructor leaves it: cloud::CloudDataMan's never stores it)
    int pad_4c;
    int pad_50;
    unsigned int m_align;  // the data's alignment (cloud::CloudDataMan passes 0x1000)
    int pad_58;
    int pad_5c;
    IWorkEvent* m_listener;  // OnFileEvent hears the read's end
    FILE_PRIO m_prio;
    bool pad_6c;
    bool pad_6d;
    bool pad_6e;
    bool pad_6f;
};

}  // namespace ml

#endif
