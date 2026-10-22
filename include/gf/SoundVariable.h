#ifndef GF_SOUNDVARIABLE_H
#define GF_SOUNDVARIABLE_H

namespace gf {
// a variable the sound side reads from an object: material, attribute, wall, water_depth, move_status, in order
enum SoundVariable : int {};

// its name, as the sound data spells it
const char* getSoundVariableName(SoundVariable variable);
}  // namespace gf

#endif
