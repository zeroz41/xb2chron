#ifndef CLASSES_EVENT_EXTEND_H
#define CLASSES_EVENT_EXTEND_H

#include "mm/mtl/FixStr.h"

namespace event {
// builds file paths: a name with an extension appended, a path's directory or file part
// table 0x7100B3FC68
class Extend {
public:
    virtual ~Extend();  // slot 0

    // the name with the extension the function is named after appended (".wav" appends ".nop")
    const char* mdo(const char* pszName);
    const char* arc(const char* pszName);
    const char* anm(const char* pszName);
    const char* eva(const char* pszName);
    const char* lgt(const char* pszName);
    const char* wav(const char* pszName);
    const char* evpa(const char* pszName);
    const char* webm(const char* pszName);
    // the text before the last '\\' (else '/'), in a static buffer; the path itself when it has neither
    const char* dirname(const char* pszPath);
    // the text after the last '\\' (else '/'); the path itself when it has neither
    const char* filename(const char* pszPath);

private:
    // the path the extension functions build and return; the name is not the original's
    mm::mtl::FixStr<256> m_path;  // 0x8
};
}  // namespace event

#endif
