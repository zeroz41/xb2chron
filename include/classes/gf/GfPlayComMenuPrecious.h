#ifndef CLASSES_GF_GFPLAYCOMMENUPRECIOUS_H
#define CLASSES_GF_GFPLAYCOMMENUPRECIOUS_H

#include "classes/gf/GfPlayCom.h"
#include "mm/mtl/RTTI.h"
namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B57CD8
class GfPlayComMenuPrecious : public GfPlayCom {
public:
    explicit GfPlayComMenuPrecious(unsigned int id) : GfPlayCom(22, false), m_id(id) { s_activate++; }
    static GfPlayComMenuPrecious* create(unsigned int id);
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfPlayComMenuPrecious();  // slot 1
    virtual const char* getFuncName() const {  // slot 3
        static const char* func = "PlayComMenuPrecious";
        return func;
    }
    virtual void start();  // slot 4
    virtual void end();  // slot 5
    virtual bool update(const fw::UpdateInfo& info, bool flag);  // slot 6
    static mm::mtl::RTTI m_rtti;
    // how many are running (GfPlayFactory::createMenuPrecious queues its command list in mode 1 only while none is)
    static int s_activate;
    // how many have started and not ended (start counts up, end down; nothing else reads it). The name is not
    // the original's: 3.0.1 leaves it unnamed (lbl_7100EA4CC4)
    static int s_start;

    unsigned int m_id;  // the precious window start opens; the name is not the original's
};
}  // namespace gf

#endif
