#ifndef CLASSES_GF_GFPLAYCOMMENUZONE_H
#define CLASSES_GF_GFPLAYCOMMENUZONE_H

#include "classes/gf/GfPlayCom.h"

namespace gf {
// table 0x7100B57C48; GfSequentialPlay::addMenuZone makes it
class GfPlayComMenuZone : public GfPlayCom {
public:
    explicit GfPlayComMenuZone(unsigned int id) : GfPlayCom(16, false), m_id(id) { s_activate++; }
    static GfPlayComMenuZone* create(unsigned int id);
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfPlayComMenuZone();  // slot 1
    virtual const char* getFuncName() const {  // slot 3
        static const char* func = "PlayComMenuZone";
        return func;
    }
    virtual void start();  // slot 4
    virtual void end();  // slot 5
    virtual bool update(const fw::UpdateInfo& info, bool flag);  // slot 6
    static mm::mtl::RTTI m_rtti;
    static int s_activate;  // the commands alive

    unsigned int m_id;  // GfSequentialPlay::addMenuZone's name
    float m_time;  // start sets 10 seconds, update counts it down; the name is not the original's
};
}  // namespace gf

#endif
