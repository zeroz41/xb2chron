#ifndef CLASSES_GF_GFPLAYCOMMAPJUMP_H
#define CLASSES_GF_GFPLAYCOMMAPJUMP_H

#include "classes/gf/GfPlayCom.h"
#include "gf/GfReqParam.h"
#include "mm/mtl/RTTI.h"
namespace gf {
// table 0x7100B58480; slot 1 is GfPlayCom's destructor (this one's is implicit)
class GfPlayComMapjump : public GfPlayCom {
public:
    explicit GfPlayComMapjump(const GfMapjumpInfo& info) : GfPlayCom(5, false), m_req(-1), m_info(info) {}
    static GfPlayComMapjump* create(const GfMapjumpInfo& info);
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual const char* getFuncName() const {  // slot 3
        static const char* func = "PlayComMapjump";
        return func;
    }
    virtual void start();  // slot 4
    virtual void end();  // slot 5
    virtual bool update(const fw::UpdateInfo& info, bool flag);  // slot 6
    static mm::mtl::RTTI m_rtti;

    unsigned int m_req;  // start's GfReqCommand::reqMapjump handle; the name is not the original's
    GfMapjumpInfo m_info;
};
}  // namespace gf

#endif
