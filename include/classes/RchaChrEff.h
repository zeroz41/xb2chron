#ifndef CLASSES_RCHACHREFF_H
#define CLASSES_RCHACHREFF_H

namespace mtl { class ALLOC_HANDLE; }

// table 0x7100B71CC8
class RchaChrEff {
public:
    virtual ~RchaChrEff();  // slot 0
    virtual void setup(mtl::ALLOC_HANDLE, void const*);  // slot 2
    virtual void clear();  // slot 3
};

#endif
