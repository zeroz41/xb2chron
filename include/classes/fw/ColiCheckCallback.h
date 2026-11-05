#ifndef CLASSES_FW_COLICHECKCALLBACK_H
#define CLASSES_FW_COLICHECKCALLBACK_H

namespace idcoli { class IDColiCallArg; }
namespace fw { template <unsigned int N> class TColiCheckResult; }

namespace fw {
// table 0x7100B41050
class ColiCheckCallback {
public:
    virtual void coli_callback(void*);  // slot 0
    virtual void coli_param_callback(void*, idcoli::IDColiCallArg const&);  // slot 1

    // fw::ColiCheck's tests build one on the stack over their result
    ColiCheckCallback(TColiCheckResult<256>* result) : m_result(result) {}

    // where the callbacks add their hits; the field names are not the original's
    TColiCheckResult<256>* m_result;
    bool m_param;  // ColiCheckConfig::m_callbackParam
};
}  // namespace fw

#endif
