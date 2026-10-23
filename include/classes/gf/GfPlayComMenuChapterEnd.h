#ifndef CLASSES_GF_GFPLAYCOMMENUCHAPTEREND_H
#define CLASSES_GF_GFPLAYCOMMENUCHAPTEREND_H

#include "classes/gf/GfPlayCom.h"

namespace gf {
// table 0x7100B57C00; GfSequentialPlay::addMenuChapterEnd makes it
class GfPlayComMenuChapterEnd : public GfPlayCom {
public:
    explicit GfPlayComMenuChapterEnd(unsigned int id) : GfPlayCom(15, false), m_id(id) { s_activate++; }
    static GfPlayComMenuChapterEnd* create(unsigned int id);
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfPlayComMenuChapterEnd();  // slot 1
    virtual const char* getFuncName() const {  // slot 3
        static const char* func = "PlayComMenuChapterEnd";
        return func;
    }
    virtual void start();  // slot 4
    virtual void end();  // slot 5
    virtual bool update(const fw::UpdateInfo& info, bool flag);  // slot 6
    static mm::mtl::RTTI m_rtti;
    static int s_activate;  // the commands alive

    unsigned int m_id;  // GfSequentialPlay::addMenuChapterEnd's name
};
}  // namespace gf

#endif
