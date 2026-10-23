#ifndef GF_GFSOUNDSOURCE_H
#define GF_GFSOUNDSOURCE_H

namespace gf {
// the resident sound sources (functions, by their symbols; split into the GmkElevator placeholder unit, after
// gf_sound's code): GfStaticRes::loadRequest loads each one's file
unsigned int getSoundSourceCount();
const char* getSoundSourceFileName(unsigned int index);
}  // namespace gf

#endif
