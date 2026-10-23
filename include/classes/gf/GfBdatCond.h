#ifndef CLASSES_GF_GFBDATCOND_H
#define CLASSES_GF_GFBDATCOND_H

#include "classes/gf/IDataBdat.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfBdatCond; }

namespace gf {
// table 0x7100B46BA8; IDataBdat at 0x8 (GfDataBdat::initialize keeps it in its list)
class GfBdatCond : public ::mm::mtl::PtrSingleton< ::gf::GfBdatCond>, public ::gf::IDataBdat {
public:
    GfBdatCond();
    virtual ~GfBdatCond();  // slot 0
    virtual void bdatRefresh();  // slot 2
    void destroyFP();
    // a condition list's entry (0-7): its type (3 an environment condition) and the condition
    unsigned int getConditionListConditionType(unsigned int id, unsigned int index) const;
    unsigned int getConditionListCondition(unsigned int id, unsigned int index) const;
    // an environment condition's weathers and time ranges, a bit each
    unsigned int getConditionEnvWeather(unsigned int id) const;
    unsigned int getConditionEnvTimeRange(unsigned int id) const;
    unsigned char pad_10[0x68];  // fields: size from GfDataBdat::initialize's allocation
};
}  // namespace gf

#endif
