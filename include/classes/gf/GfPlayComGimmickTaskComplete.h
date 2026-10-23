#ifndef CLASSES_GF_GFPLAYCOMGIMMICKTASKCOMPLETE_H
#define CLASSES_GF_GFPLAYCOMGIMMICKTASKCOMPLETE_H

#include "classes/gf/GfPlayCom.h"
namespace gmk { enum GmkType : int; }

namespace gf {
// table 0x7100B580B8
class GfPlayComGimmickTaskComplete : public GfPlayCom {
public:
    GfPlayComGimmickTaskComplete(gmk::GmkType type, unsigned int id, float time) : GfPlayCom(35, false), m_type(type), m_id(id), m_time(time) {}
    static GfPlayComGimmickTaskComplete* create(gmk::GmkType type, unsigned int id, float time);
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual const char* getFuncName() const {  // slot 3
        static const char* func = "GimmickTaskComplete";
        return func;
    }
    virtual void start() {}  // slot 4
    virtual void end() {}  // slot 5
    virtual bool update(const fw::UpdateInfo& info, bool flag);  // slot 6
    static mm::mtl::RTTI m_rtti;

    gmk::GmkType m_type;
    unsigned int m_id;
    float m_time;  // GfSequentialPlay::addGimmickTaskComplete's names
};
}  // namespace gf

#endif
