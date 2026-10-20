#ifndef CLASSES_GF_GFPLAYCOMRESETBLADE_H
#define CLASSES_GF_GFPLAYCOMRESETBLADE_H

namespace gf {
// table 0x7100B581D8
class GfPlayComResetBlade {
public:
    virtual void getRTTI() const;  // slot 0
    virtual void vf1();  // slot 1
    virtual void vf2();  // slot 2
    virtual void getFuncName() const;  // slot 3
    virtual void start();  // slot 4
    virtual void end();  // slot 5
    virtual void vf6();  // slot 6
};
}  // namespace gf

#endif
