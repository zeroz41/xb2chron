#ifndef CLASSES_GMK_GMKKIZUNATALK_H
#define CLASSES_GMK_GMKKIZUNATALK_H

#include "classes/gmk/AGmkBase.h"

namespace gf { class GF_OBJ_HANDLE; }

namespace gmk {
// table 0x7100B6DFD0
class GmkKizunaTalk : public ::gmk::AGmkBase {
public:
    class BdatInfo;
    virtual ~GmkKizunaTalk();  // slot 0
    virtual void getGmkType() const;  // slot 2
    virtual void create(gmk::AGmkBase::CreateInfo const&);  // slot 4
    virtual void dispose();  // slot 5
    virtual void update(float);  // slot 6
    virtual void debugDraw() const;  // slot 7
    virtual void onPlayerAccessed(gf::GF_OBJ_HANDLE*);  // slot 9
};
}  // namespace gmk

#endif
