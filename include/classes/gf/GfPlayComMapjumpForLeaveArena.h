#ifndef CLASSES_GF_GFPLAYCOMMAPJUMPFORLEAVEARENA_H
#define CLASSES_GF_GFPLAYCOMMAPJUMPFORLEAVEARENA_H

#include "classes/gf/GfPlayCom.h"
#include "gf/GfReqParam.h"
#include "mm/mtl/RTTI.h"
namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B58A70; slot 1 is gf::GfPlayCom::~GfPlayCom() (this one's is implicit)
class GfPlayComMapjumpForLeaveArena : public GfPlayCom {
public:
    explicit GfPlayComMapjumpForLeaveArena(const GfMapjumpInfo& info)
        : GfPlayCom(47, false), m_req(-1), m_info(info), m_started(false) {}
    static GfPlayComMapjumpForLeaveArena* create(const GfMapjumpInfo& info);
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual const char* getFuncName() const {  // slot 3
        static const char* func = "MapjumpForLeaveArena";
        return func;
    }
    virtual void start();  // slot 4
    virtual void end();  // slot 5
    virtual bool update(const fw::UpdateInfo& info, bool flag);  // slot 6
    static mm::mtl::RTTI m_rtti;

    // update's GfReqCommand::reqMapjump handle, once the arena manager is out of state 9; the name is not the original's
    unsigned int m_req;
    GfMapjumpInfo m_info;
    bool m_started;  // start sets it (nothing in the unit reads it); the name is not the original's
};
}  // namespace gf

#endif
