#ifndef CLASSES_GF_GFKIZUNARINGMANAGER_H
#define CLASSES_GF_GFKIZUNARINGMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfSetupParam; class QuestCompleteParam; }

namespace gf {
// table 0x7100B56CF0; its destructor is its singleton's
class GfKizunaringManager : public ::mm::mtl::PtrSingleton<GfKizunaringManager> {
public:
    GfKizunaringManager(const GfSetupParam& param);
    virtual ~GfKizunaringManager();  // slot 0
    void initialize(const GfSetupParam& param);
    static void build(const GfSetupParam& param);
    static void destroy();
    void finalize();
    static void orderAchievement(unsigned int id);
    void setupGame();
    void qevCompleteQuest(const QuestCompleteParam& param);
    bool m_initialized;  // set by initialize, cleared by finalize
};
}  // namespace gf

#endif
