#ifndef GF_GFDATADRIVER_H
#define GF_GFDATADRIVER_H

namespace gf {
// the drivers' data (functions, by its symbols)
class GfDataDriver {
public:
    static int getMaxSetBladeNum(unsigned int driver);  // how many blades the driver can engage
    static bool isActivateUnuse(unsigned int driver);
    // the slot of the driver's engaged blade
    static int getBladeSet(unsigned int driver);
    // the blade in the driver's slot (GfMenuObjBladeSwitch::update asks GfMenuObjUtil::isValidBlade about it)
    static unsigned int getBlade(unsigned int driver, int slot);
};
}  // namespace gf

#endif
