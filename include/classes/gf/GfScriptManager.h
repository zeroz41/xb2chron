#ifndef CLASSES_GF_GFSCRIPTMANAGER_H
#define CLASSES_GF_GFSCRIPTMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfScriptManager; }
namespace gf { class GfSetupParam; }

namespace gf {
// table 0x7100B6B900: the game's scripts, each a fw::ScriptManager script under a fixed id
class GfScriptManager : public ::mm::mtl::PtrSingleton< ::gf::GfScriptManager> {
public:
    // out of line in 1.0.0; build inlines it in 3.0.1
    GfScriptManager(const GfSetupParam& param) : m_initialized(false) { initialize(param); }
    virtual ~GfScriptManager();  // slot 0
    void initialize(const GfSetupParam& param);
    void finalize();
    static void build(const GfSetupParam& param);
    static void destroy();
    static void loadScript(unsigned int id, const char* name);
    static bool isScriptLoadError(unsigned int id);
    static void startScript(unsigned int id);
    static void destroyScript(unsigned int id);
    static bool isScriptWaitStart(unsigned int id);
    static bool isScriptLoaded(unsigned int id);
    static bool isScriptActive(unsigned int id);
    static bool isScriptFinish(unsigned int id);

    bool m_initialized;  // initialize sets it, finalize clears it
};
}  // namespace gf

#endif
