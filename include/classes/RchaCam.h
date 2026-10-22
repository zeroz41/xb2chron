#ifndef CLASSES_RCHACAM_H
#define CLASSES_RCHACAM_H

#include "classes/RchaNode.h"

namespace mtl { class ALLOC_HANDLE; }

// table 0x7100B71B58
class RchaCam : public ::RchaNode {
public:
    virtual ~RchaCam();  // slot 0
    virtual bool setup(mtl::ALLOC_HANDLE, void const*);  // slot 2
};

#endif
