#ifndef CLASSES_GF_GFPLAYCOMSTARTTUTORIAL_H
#define CLASSES_GF_GFPLAYCOMSTARTTUTORIAL_H

#include "classes/gf/GfPlayCom.h"
#include "mm/mtl/RTTI.h"
namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B585A0
class GfPlayComStartTutorial : public GfPlayCom {
public:
    explicit GfPlayComStartTutorial(unsigned int id) : GfPlayCom(49, false), m_id(id) {}
    static GfPlayComStartTutorial* create(unsigned int id);
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual const char* getFuncName() const {  // slot 3
        static const char* func = "GfPlayComStartTutorial";
        return func;
    }
    virtual void start();  // slot 4
    virtual void end();  // slot 5
    virtual bool update(const fw::UpdateInfo& info, bool flag);  // slot 6
    static mm::mtl::RTTI m_rtti;
    static int s_activateCount;

    int m_id;  // the tutorial's row (its script_file); signed, start compares it so. The name is not the original's
};
}  // namespace gf

#endif
