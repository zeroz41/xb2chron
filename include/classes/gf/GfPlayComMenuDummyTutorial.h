#ifndef CLASSES_GF_GFPLAYCOMMENUDUMMYTUTORIAL_H
#define CLASSES_GF_GFPLAYCOMMENUDUMMYTUTORIAL_H

#include "classes/gf/GfPlayCom.h"

namespace gf {
// table 0x7100B57C90; GfSequentialPlay::addMenuDummyTutorial makes it
class GfPlayComMenuDummyTutorial : public GfPlayCom {
public:
    explicit GfPlayComMenuDummyTutorial(unsigned int id) : GfPlayCom(17, false), m_id(id) { s_activate++; }
    static GfPlayComMenuDummyTutorial* create(unsigned int id);
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfPlayComMenuDummyTutorial();  // slot 1
    virtual const char* getFuncName() const {  // slot 3
        static const char* func = "PlayComMenuDummyTutorial";
        return func;
    }
    virtual void start();  // slot 4
    virtual void end();  // slot 5
    virtual bool update(const fw::UpdateInfo& info, bool flag);  // slot 6
    static mm::mtl::RTTI m_rtti;
    static int s_activate;  // the commands alive

    unsigned int m_id;  // GfSequentialPlay::addMenuDummyTutorial's name
};
}  // namespace gf

#endif
