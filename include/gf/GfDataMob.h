#ifndef GF_GFDATAMOB_H
#define GF_GFDATAMOB_H

namespace gf {
// the mobs' data, by their row id (functions, by its symbols)
class GfDataMob {
public:
    static const char* getName(unsigned int mob);
    // the message table and row of the mob's name
    static bool getName(unsigned char*& bdat, unsigned int& id, unsigned int mob);
    static unsigned int getFootStep(unsigned int mob);
    static unsigned int getFootStepEffect(unsigned int mob);
};
}  // namespace gf

#endif
