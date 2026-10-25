#ifndef GF_GFDATAIDEA_H
#define GF_GFDATAIDEA_H

namespace gf {
// the blades' ideas (trust) data (functions, by their symbols)
class GfDataIdea {
public:
    static unsigned int calcLevel(unsigned int point);  // the level an idea's points reach (SDataIdea::setPoint)
};
}  // namespace gf

#endif
