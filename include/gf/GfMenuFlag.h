#ifndef GF_GFMENUFLAG_H
#define GF_GFMENUFLAG_H

namespace gf {

// the menus' one-bit flags, ids 0-99 (get1 reads GfGameFlag's local 1-bit flag 39474 + id)
class GfMenuFlag {
public:
    static void set1(int id, unsigned int value);
    static unsigned int get1(int id);  // 0 for an id past 99
};

}  // namespace gf

#endif
