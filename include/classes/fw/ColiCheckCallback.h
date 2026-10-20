#ifndef CLASSES_FW_COLICHECKCALLBACK_H
#define CLASSES_FW_COLICHECKCALLBACK_H

namespace idcoli { class IDColiCallArg; }

namespace fw {
// table 0x7100B41050
class ColiCheckCallback {
public:
    virtual void coli_callback(void*);  // slot 0
    virtual void coli_param_callback(void*, idcoli::IDColiCallArg const&);  // slot 1
};
}  // namespace fw

#endif
