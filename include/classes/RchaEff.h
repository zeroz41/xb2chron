#ifndef CLASSES_RCHAEFF_H
#define CLASSES_RCHAEFF_H

namespace mtl { class ALLOC_HANDLE; }

// table 0x7100B71D98
class RchaEff {
public:
    virtual ~RchaEff();  // slot 0
    virtual void setup(mtl::ALLOC_HANDLE, void const*);  // slot 2
    virtual void clear();  // slot 3
};

#endif
