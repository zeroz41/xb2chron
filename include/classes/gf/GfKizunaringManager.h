#ifndef CLASSES_GF_GFKIZUNARINGMANAGER_H
#define CLASSES_GF_GFKIZUNARINGMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfSetupParam; class QuestCompleteParam; }

namespace gf {
// table 0x7100B56CF0; its destructor is its singleton's
class GfKizunaringManager : public ::mm::mtl::PtrSingleton<GfKizunaringManager> {
public:
    // the constructor, initialize and finalize are inline: the symbols name no copy of them
    GfKizunaringManager(const GfSetupParam& param) { initialize(param); }
    virtual ~GfKizunaringManager();  // slot 0
    void initialize(const GfSetupParam&) { m_initialized = true; }
    static void build(const GfSetupParam& param);
    static void destroy();
    void finalize() { m_initialized = false; }
    static void orderAchievement(unsigned int id);
    static void setupGame();  // empty; GfGameManager::setupGame calls it without an object
    void qevCompleteQuest(const QuestCompleteParam& param);
    bool m_initialized;  // set by initialize, cleared by finalize
};
}  // namespace gf

#endif
