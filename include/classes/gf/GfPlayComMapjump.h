#ifndef CLASSES_GF_GFPLAYCOMMAPJUMP_H
#define CLASSES_GF_GFPLAYCOMMAPJUMP_H

#include "classes/gf/GfPlayCom.h"
#include "mm/mtl/RTTI.h"
namespace gf { class GfMapjumpInfo; }
namespace gf {
// table 0x7100B58480
class GfPlayComMapjump : public GfPlayCom {
public:
    static GfPlayComMapjump* create(const GfMapjumpInfo& info);
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfPlayComMapjump();  // slot 1
    virtual const char* getFuncName() const;  // slot 3
    virtual void start();  // slot 4
    virtual void end();  // slot 5
    virtual void vf6();  // slot 6
    static mm::mtl::RTTI m_rtti;
};
}  // namespace gf

#endif
