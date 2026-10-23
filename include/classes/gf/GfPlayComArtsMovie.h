#ifndef CLASSES_GF_GFPLAYCOMARTSMOVIE_H
#define CLASSES_GF_GFPLAYCOMARTSMOVIE_H

#include "classes/gf/GfPlayCom.h"
#include "mm/mtl/FixStr.h"

namespace gf {
// table 0x7100B58190
class GfPlayComArtsMovie : public GfPlayCom {
public:
    explicit GfPlayComArtsMovie(const char* name) : GfPlayCom(41, true), m_name(name) {}
    static GfPlayComArtsMovie* create(const char* name);
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual const char* getFuncName() const {  // slot 3
        static const char* func = "ArtsMovie";
        return func;
    }
    virtual void start();  // slot 4
    virtual void end();  // slot 5
    virtual bool update(const fw::UpdateInfo& info, bool flag);  // slot 6
    static mm::mtl::RTTI m_rtti;

    mm::mtl::FixStr<64> m_name;  // GfSequentialPlay::addArtsMovie names it
};
}  // namespace gf

#endif
