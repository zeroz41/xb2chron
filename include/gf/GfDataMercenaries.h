#ifndef GF_GFDATAMERCENARIES_H
#define GF_GFDATAMERCENARIES_H

namespace gf {
// the mercenary team's data (functions, by its symbols)
class GfDataMercenaries {
public:
    static int getLevel();  // up to 5 (GfMenuGameAdapter::update_MercenariesPoint shows no points at 5)
    static int getPoint();
    static int getPointMax();
};
}  // namespace gf

#endif
