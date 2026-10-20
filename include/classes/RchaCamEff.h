#ifndef CLASSES_RCHACAMEFF_H
#define CLASSES_RCHACAMEFF_H

#include "classes/RchaNode.h"

namespace mtl { class ALLOC_HANDLE; }

// table 0x7100B71C78
class RchaCamEff : public ::RchaNode {
public:
    virtual ~RchaCamEff();  // slot 0
    virtual void setup(mtl::ALLOC_HANDLE, void const*);  // slot 2
};

#endif
