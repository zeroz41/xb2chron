#ifndef GF_GFPOUCHUTIL_H
#define GF_GFPOUCHUTIL_H

namespace gf { struct SDataPouch; }

namespace gf {

// the pouches' helpers (functions, by 1.0.0's symbols)
class GfPouchUtil {
public:
    static SDataPouch& getPouch(unsigned int driver, unsigned int pouch);
};

}  // namespace gf

#endif
