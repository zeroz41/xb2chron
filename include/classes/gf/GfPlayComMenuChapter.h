#ifndef CLASSES_GF_GFPLAYCOMMENUCHAPTER_H
#define CLASSES_GF_GFPLAYCOMMENUCHAPTER_H

#include "classes/gf/GfPlayCom.h"

namespace gf {
// table 0x7100B57BB8; GfSequentialPlay::addMenuChapter makes it
class GfPlayComMenuChapter : public GfPlayCom {
public:
    explicit GfPlayComMenuChapter(unsigned int id) : GfPlayCom(14, false), m_id(id) { s_activate++; }
    static GfPlayComMenuChapter* create(unsigned int id);
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfPlayComMenuChapter();  // slot 1
    virtual const char* getFuncName() const {  // slot 3
        static const char* func = "PlayComMenuChapter";
        return func;
    }
    virtual void start();  // slot 4
    virtual void end();  // slot 5
    virtual bool update(const fw::UpdateInfo& info, bool flag);  // slot 6
    static mm::mtl::RTTI m_rtti;
    static int s_activate;  // the commands alive

    unsigned int m_id;  // GfSequentialPlay::addMenuChapter's name
};
}  // namespace gf

#endif
