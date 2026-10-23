#ifndef GF_GFDATABLADECREATE_H
#define GF_GFDATABLADECREATE_H

namespace gf {
// (functions, by their symbols)
class GfDataBladeCreate {
public:
    static unsigned int getAssurePoint();
    static void resetAssurePoint();
    static unsigned int getAssureCount();
    static void resetAssureCount();
    static unsigned int getRareBladeAppearType();
    static void setRareBladeAppearType(unsigned int value);
};
}  // namespace gf

#endif
