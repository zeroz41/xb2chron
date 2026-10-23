#ifndef CLASSES_GF_GFINITPARAMENEMY_H
#define CLASSES_GF_GFINITPARAMENEMY_H

#include "classes/gf/GfInitParam.h"

namespace gf {
// table 0x7100B3FB98
class GfInitParamEnemy : public ::gf::GfInitParam {
public:
    virtual unsigned int getBladeID() const;  // slot 1
    virtual void getEnArrangeID() const;  // slot 2
};
}  // namespace gf

#endif
