#ifndef IDCOLI_IDCOLITREETOP_H
#define IDCOLI_IDCOLITREETOP_H

namespace idcoli {

// only the members other files call are declared so far (its owners' destructors call the destructor; its body is
// empty). Fields are not declared yet.
class IDColiTreeTop {
public:
    IDColiTreeTop();
    ~IDColiTreeTop();
    void begin();
    void end();

    unsigned char pad_0[0x2C10];  // IDColiManager's constructor allocates it so
};

}  // namespace idcoli

#endif
