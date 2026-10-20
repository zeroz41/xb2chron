#ifndef CLASSES_CRCHAEX_H
#define CLASSES_CRCHAEX_H

namespace mtl { class ALLOC_HANDLE; }

// table 0x7100B71E68
class CRchaEx {
public:
    virtual ~CRchaEx();  // slot 0
    virtual void setup(mtl::ALLOC_HANDLE, void const*);  // slot 2
    virtual void clear();  // slot 3
};

#endif
