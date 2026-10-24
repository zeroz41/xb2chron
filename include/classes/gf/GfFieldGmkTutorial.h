#ifndef CLASSES_GF_GFFIELDGMKTUTORIAL_H
#define CLASSES_GF_GFFIELDGMKTUTORIAL_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/FixStr.h"

namespace gf { class GfFieldGmkTutorial; class GfSetupParam; class MapjumpCallbackInfo; enum GEV : int; }

namespace gf {
// table 0x7100B524E8; runs a gimmick tutorial's script (create loads it into fw::ScriptManager's slot m_scriptId
// and starts it; isEnd waits for it to finish)
class GfFieldGmkTutorial : public ::mm::mtl::PtrSingleton< ::gf::GfFieldGmkTutorial> {
public:
    GfFieldGmkTutorial() : m_scriptId(0x44), m_arg(0), m_waitMover(false) {}
    virtual ~GfFieldGmkTutorial() {  // slot 0
        dispose();
    }
    static void build(const GfSetupParam& param);
    static void destroy();
    void dispose();
    void create(const char* name, unsigned int arg);
    bool isEnd() const;
    void gevMapjump(GEV ev, const MapjumpCallbackInfo& info);

    int m_scriptId;  // the fw::ScriptManager slot the script loads into (0x44); the name is not the original's
    mm::mtl::FixStr<64> m_name;  // the script create was given; the name is not the original's
    unsigned int m_arg;  // create's second argument, kept; the name is not the original's
    // GfPlayComWaitPlayerToStartGmkTuto sets it once the player has waited 3 seconds without the mover being ready
    // and clears it when the mover is (the name is not the original's); isEnd answers true while it is set
    bool m_waitMover;
};
}  // namespace gf

#endif
