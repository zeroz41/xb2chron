#ifndef GF_GFDATAIDEA_H
#define GF_GFDATAIDEA_H

#include "mm/mtl/FixedVector.h"

namespace gf {
// the blades' ideas (trust) data (functions, by their symbols)
class GfDataIdea {
public:
    static unsigned int calcLevel(unsigned int point);  // the level an idea's points reach (SDataIdea::setPoint)
    // the two attributes an idea (0-3) stands for: 1/2, 3/6, 4/5, 7/8; nothing for another idea
    static void getIdeaAttribute(mm::mtl::FixedVector<unsigned int, 2>& attributes, unsigned int idea);
};
}  // namespace gf

#endif
