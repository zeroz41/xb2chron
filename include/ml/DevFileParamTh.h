#ifndef ML_DEVFILEPARAMTH_H
#define ML_DEVFILEPARAMTH_H

namespace ml { class IWorkEvent; }
namespace ml { enum FILE_PRIO : int; }

namespace ml {

// what DevFileTh::readFile reads (no table; 0x70 bytes: fw::ScriptInfo::load and gf::GfGameLoad build one on the
// stack with the same defaults). FileHandleTh::setup takes the path, buffer, size and listener from it. The field
// names are not the original's.
class DevFileParamTh {
public:
    DevFileParamTh()
        : pad_8(0), pad_10(nullptr), pad_38(nullptr), m_buffer(nullptr), m_size(0), pad_4c(0), pad_50(0), pad_54(0),
          pad_58(1), pad_5c(0), m_listener(nullptr), pad_6c(true), pad_6d(false), pad_6e(false), pad_6f(false) {}
    // clears the pointer at 0x38 (what it holds is not known)
    ~DevFileParamTh() {
        if (pad_38 != nullptr) {
            pad_38 = nullptr;
        }
    }

    const char* m_path;  // the file (FileHandleTh::setup asserts it)
    int pad_8;
    void* pad_10;
    unsigned char pad_18[0x20];
    void* pad_38;
    void* m_buffer;  // where the file is read to
    unsigned int m_size;  // the buffer's size
    int pad_4c;
    int pad_50;
    int pad_54;
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
