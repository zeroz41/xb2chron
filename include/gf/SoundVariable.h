#ifndef GF_SOUNDVARIABLE_H
#define GF_SOUNDVARIABLE_H

namespace gf {
// a variable the sound side reads from an object: material, attribute, wall, water_depth, move_status, in order
enum SoundVariable : int {};
// the values of the wall, water_depth and move_status variables, in the order their names are listed
enum SoundVariableWall : int {};
enum SoundVariableWaterDepth : int {};
enum SoundVarMoveStatus : int {};

// the sound variable WaterInPlugin::onEvent reads the splash's depth threshold from, in hundredths ("water_th")
extern const char* SND_VAR_WATER_THRESOULD_NAME;

// its name, as the sound data spells it
const char* getSoundVariableName(SoundVariable variable);
// the variable a name spells, -1 for none
int getSoundVariable(const char* name);
// a variable's value names (MAT_*, ATR_*, WALL_*, WATER_DEPTH_*, MOVE_*), "invalid" out of range, and back
const char* getMaterialVariableName(int value);
int getMaterialVariable(const char* name);
const char* getAttributeVariableName(int value);
int getAttrbiteVariable(const char* name);
const char* getWallVariableName(SoundVariableWall value);
int getWallVariable(const char* name);
const char* getWaterDepthVariableName(SoundVariableWaterDepth value);
int getWaterDepthVariable(const char* name);
const char* getMoveStatusVariableName(SoundVarMoveStatus value);
int getMoveStatusVariable(const char* name);
}  // namespace gf

#endif
