#ifndef CLASSES_GF_GFINITPARAM_H
#define CLASSES_GF_GFINITPARAM_H

namespace gf {
// table none (its derived classes')
class GfInitParam {
public:
    virtual bool isAllWeapon() const { return false; }  // slot 0
    virtual void getBladeID() const;  // slot 1
    virtual void getEnArrangeID() const;  // slot 2
};
}  // namespace gf

#endif
