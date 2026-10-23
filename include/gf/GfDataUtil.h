#ifndef GF_GFDATAUTIL_H
#define GF_GFDATAUTIL_H

namespace gf {
// the game data's helpers (functions, by its symbols)
class GfDataUtil {
public:
    static int getMoney();
    static int getObjTypeByCharaId(unsigned int chara);  // the object type of a character
};
}  // namespace gf

#endif
