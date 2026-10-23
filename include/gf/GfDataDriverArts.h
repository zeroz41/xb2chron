#ifndef GF_GFDATADRIVERARTS_H
#define GF_GFDATADRIVERARTS_H

namespace gf {
// the drivers' arts data (functions, by their symbols)
class GfDataDriverArts {
public:
    // the message tables of the arts' names and captions, and an arts' ids in them
    static unsigned char* getNameFP();
    static unsigned int getNameID(unsigned int arts);
    static unsigned char* getCaptionFP();
    static unsigned int getCaptionID(unsigned int arts);
};
}  // namespace gf

#endif
