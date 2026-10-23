#ifndef IDCOLI_IDCOLIGRANDOBJ_H
#define IDCOLI_IDCOLIGRANDOBJ_H

namespace idcoli {

// only the destructor is declared so far (its owners' destructors call it; its body is empty). Fields and other
// members are not declared yet.
class IDColiGrandObj {
public:
    ~IDColiGrandObj();
};

}  // namespace idcoli

#endif
