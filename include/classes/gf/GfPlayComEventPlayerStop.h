#ifndef CLASSES_GF_GFPLAYCOMEVENTPLAYERSTOP_H
#define CLASSES_GF_GFPLAYCOMEVENTPLAYERSTOP_H

#include "classes/gf/GfPlayCom.h"

namespace gf {
// table 0x7100B577F8
class GfPlayComEventPlayerStop : public GfPlayCom {
public:
    explicit GfPlayComEventPlayerStop(bool stop) : GfPlayCom(6, true), m_stop(stop) {}
    static GfPlayComEventPlayerStop* create(bool stop);
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual const char* getFuncName() const {  // slot 3
        static const char* func = "PlayComEventPlayerStop";
        return func;
    }
    virtual void start();  // slot 4
    virtual void end() {}  // slot 5
    virtual bool update(const fw::UpdateInfo& info, bool flag) { return true; }  // slot 6
    static mm::mtl::RTTI m_rtti;
    // how many stopping commands are alive (create counts up when it stops the player, start of a releasing one
    // counts down and releases at zero). 2.0.0's symbols name it
    static int s_stopRequests;

    bool m_stop;  // GfSequentialPlay::addEventPlayerStop's name
};
}  // namespace gf

#endif
