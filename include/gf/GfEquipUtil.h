#ifndef GF_GFEQUIPUTIL_H
#define GF_GFEQUIPUTIL_H

namespace gf { class SDataDriver; }

namespace gf {
// equipment helpers (functions, by its symbols)
class GfEquipUtil {
public:
    static unsigned int getEquipAcceResult(const SDataDriver& data, unsigned int slot, unsigned int accessory);
};
}  // namespace gf

#endif
