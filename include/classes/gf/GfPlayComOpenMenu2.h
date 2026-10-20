#ifndef CLASSES_GF_GFPLAYCOMOPENMENU2_H
#define CLASSES_GF_GFPLAYCOMOPENMENU2_H

namespace gf {
// table 0x7100B58558
class GfPlayComOpenMenu2 {
public:
    virtual void getRTTI() const;  // slot 0
    virtual ~GfPlayComOpenMenu2();  // slot 1
    virtual void getFuncName() const;  // slot 3
    virtual void start();  // slot 4
    virtual void end();  // slot 5
    virtual void vf6();  // slot 6
};
}  // namespace gf

#endif
