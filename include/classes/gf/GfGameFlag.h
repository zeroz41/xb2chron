#ifndef CLASSES_GF_GFGAMEFLAG_H
#define CLASSES_GF_GFGAMEFLAG_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfSetupParam; }
namespace gf { class GameFlag; }

namespace gf {
// table 0x7100B50FA0; its destructor is its singleton's
class GfGameFlag : public ::mm::mtl::PtrSingleton<GfGameFlag> {
public:
    // inline: the module has no copy of it, nor of initialize, finalize and isInitialized
    GfGameFlag(const GfSetupParam& param) { initialize(param); }
    virtual ~GfGameFlag();  // slot 0
    void initialize(const GfSetupParam& param) { m_initialized = true; }
    static void build(const GfSetupParam& param);
    static void destroy();
    void finalize() { m_initialized = false; }
    static bool isInitialized() {
        GfGameFlag* flag = get();
        if (flag != nullptr) {
            return flag->m_initialized;
        }
        return false;
    }
    // a flag of the game's data: type is its width in bits (1, 2, 4, 8, 16 or 32)
    static void setLocal(unsigned int type, int index, unsigned int value);
    static unsigned int getLocal(const GameFlag& flag, unsigned int type, int index);
    static void setLocal(GameFlag& flag, unsigned int type, int index, unsigned int value);
    static unsigned int getLocal(unsigned int type, int index);
    static void clear();
    bool m_initialized;  // set by initialize, cleared by finalize
};
}  // namespace gf

#endif
