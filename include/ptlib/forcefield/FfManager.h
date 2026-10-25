#ifndef PTLIB_FORCEFIELD_FFMANAGER_H
#define PTLIB_FORCEFIELD_FFMANAGER_H

namespace ptlib {

// a force the force-field manager adds (effect::SystemManager keeps them until tail hands them on); its fields are not
// known yet
class AddForceParam {
public:
    unsigned char pad_0[0x40];
};

namespace forcefield {
class FfManager {
public:
    static FfManager*& getPtr();
    void addForce(const AddForceParam& param);
};
}  // namespace forcefield

}  // namespace ptlib

#endif
