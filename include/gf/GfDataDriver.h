#ifndef GF_GFDATADRIVER_H
#define GF_GFDATADRIVER_H

namespace gf {
// the drivers' data (functions, by its symbols)
class GfDataDriver {
public:
    static int getMaxSetBladeNum(unsigned int driver);  // how many blades the driver can engage
};
}  // namespace gf

#endif
