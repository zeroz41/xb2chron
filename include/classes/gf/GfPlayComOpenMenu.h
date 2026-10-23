#ifndef CLASSES_GF_GFPLAYCOMOPENMENU_H
#define CLASSES_GF_GFPLAYCOMOPENMENU_H

#include "classes/gf/GfPlayCom.h"

namespace gf {
// table 0x7100B57B70; GfSequentialPlay::addOpenMenu makes it
class GfPlayComOpenMenu : public GfPlayCom {
public:
    explicit GfPlayComOpenMenu(unsigned int menu) : GfPlayCom(11, false) {
        s_active++;
        m_menu = menu;
    }
    static GfPlayComOpenMenu* create(unsigned int menu);
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfPlayComOpenMenu();  // slot 1
    virtual const char* getFuncName() const {  // slot 3
        static const char* func = "GfPlayComOpenMenu";
        return func;
    }
    virtual void start();  // slot 4
    virtual void end();  // slot 5
    virtual bool update(const fw::UpdateInfo& info, bool flag);  // slot 6
    static mm::mtl::RTTI m_rtti;
    static int s_active;  // the commands alive

    unsigned int m_menu;  // GfSequentialPlay::addOpenMenu's name
};
}  // namespace gf

#endif
