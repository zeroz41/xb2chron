#ifndef CLASSES_RCHANODE_H
#define CLASSES_RCHANODE_H

namespace mtl { class ALLOC_HANDLE; }

// table 0x7100B71F80
class RchaNode {
public:
    virtual ~RchaNode();  // slot 0
    virtual void setup(mtl::ALLOC_HANDLE, void const*);  // slot 2
    virtual void clear();  // slot 3
};

#endif
