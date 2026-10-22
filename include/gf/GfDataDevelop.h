#ifndef GF_GFDATADEVELOP_H
#define GF_GFDATADEVELOP_H

namespace gf {

// the zones' development data (functions, by their symbols)
class GfDataDevelop {
public:
    static int getPoint(unsigned int zone);  // a zone's development points
    static int getLevel(unsigned int zone);  // a zone's development level
};

}  // namespace gf

#endif
