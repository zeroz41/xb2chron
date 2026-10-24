#ifndef CLASSES_GF_GFPLAYCOMSTARTTUTORIAL_H
#define CLASSES_GF_GFPLAYCOMSTARTTUTORIAL_H

#include "classes/gf/GfPlayCom.h"
#include "mm/mtl/RTTI.h"
namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B585A0
class GfPlayComStartTutorial : public GfPlayCom {
public:
    static GfPlayComStartTutorial* create(unsigned int id);
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfPlayComStartTutorial();  // slot 1
    virtual const char* getFuncName() const;  // slot 3
    virtual void start();  // slot 4
    virtual void end();  // slot 5
    virtual bool update(const fw::UpdateInfo& info, bool flag);  // slot 6
    static mm::mtl::RTTI m_rtti;
};
}  // namespace gf

#endif
