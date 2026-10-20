#ifndef CLASSES_GMK_GMKWARP_H
#define CLASSES_GMK_GMKWARP_H

#include "classes/gmk/AGmkBase.h"

namespace gf { class GF_OBJ_HANDLE; }
namespace gf { namespace IGfObjListener { enum OBJEVT : int; }}

namespace gmk {
// table 0x7100B6CCA8
class GmkWarp : public ::gmk::AGmkBase {
public:
    class BdatInfo;
    virtual ~GmkWarp();  // slot 0
    virtual void getGmkType() const;  // slot 2
    virtual void create(gmk::AGmkBase::CreateInfo const&);  // slot 4
    virtual void dispose();  // slot 5
    virtual void update(float);  // slot 6
    virtual void debugDraw() const;  // slot 7
    virtual void onGobEvent(gf::IGfObjListener::OBJEVT, gf::GF_OBJ_HANDLE*);  // slot 8
    virtual void onPlayerAccessed(gf::GF_OBJ_HANDLE*);  // slot 9
    virtual void debugUpdateMmf();  // slot 10
};
}  // namespace gmk

#endif
