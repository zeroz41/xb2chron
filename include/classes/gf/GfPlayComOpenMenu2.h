#ifndef CLASSES_GF_GFPLAYCOMOPENMENU2_H
#define CLASSES_GF_GFPLAYCOMOPENMENU2_H

#include "classes/gf/GfPlayCom.h"
#include "classes/mm/mtl/PtrSingleton.h"
namespace gf { enum MAINMENU : int; }
namespace gf { class GF_OBJ_HANDLE; }

namespace gf {
// table 0x7100B58558; GfSequentialPlay::addOpenMenu2 makes it
class GfPlayComOpenMenu2 : public GfPlayCom {
public:
    GfPlayComOpenMenu2(unsigned int menu, MAINMENU main) : GfPlayCom(12, false), m_menu(menu), m_main(main), pad_18(0), m_state(0) {}
    static GfPlayComOpenMenu2* create(unsigned int menu, MAINMENU main);
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual const char* getFuncName() const {  // slot 3
        static const char* func = "GfPlayComOpenMenu";
        return func;
    }
    virtual void start();  // slot 4
    virtual void end();  // slot 5
    virtual bool update(const fw::UpdateInfo& info, bool flag);  // slot 6
    static mm::mtl::RTTI m_rtti;

    unsigned int m_menu;
    MAINMENU m_main;  // GfSequentialPlay::addOpenMenu2's names
    int pad_18;
    int m_state;  // start sets 3; the name is not the original's
};
}  // namespace gf

#endif
