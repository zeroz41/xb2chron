#ifndef GF_GFDATABLADEARTS_H
#define GF_GFDATABLADEARTS_H

namespace gf {
class GfDataBladeArts {
public:
    static bool getName(unsigned char*& bdat, unsigned int& id, unsigned int skill);
    static bool getCaption(unsigned char*& bdat, unsigned int& id, unsigned int skill);
    static bool getExName(unsigned char*& bdat, unsigned int& id, unsigned int skill);
    static bool getExCaption(unsigned char*& bdat, unsigned int& id, unsigned int skill);
    static unsigned int getEnhance(unsigned int arts, unsigned int index);
};
}  // namespace gf

#endif
