#ifndef CLASSES_GF_GFOBJSETUPFIELDOBJ_H
#define CLASSES_GF_GFOBJSETUPFIELDOBJ_H

#include "mm/mtl/RTTI.h"
#include "classes/gf/GfObjSetup.h"
#include "classes/gf/GfInitParamFobj.h"

namespace gf {
// table 0x7100B6A688
class GfObjSetupFieldObj : public ::gf::GfObjSetup {
public:
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfObjSetupFieldObj() {}  // slot 1
    static mm::mtl::RTTI m_rtti;
    GfObjSetupFieldObj(const GfInitParamFobj& param);

    // the "paramid<n>" column of the parameter's BDAT row (createSetupParam; -1 at construction)
    int pad_6c;
    // GfFobjDropitem::initialize adds it to the drop's distance (the name is not the original's)
    float m_dropDistance;
    // when above 0, GfFobjDropitem::initialize waits that long before the item moves (the name is not the original's)
    float m_appearDelay;
    // the item's BDAT file and row: GfFobjDropitem::initialize reads its "Rarity", applyGetItem gives it (the names
    // are not the original's)
    unsigned int m_itemBdat;
    int m_itemId;
    unsigned int m_gold;  // GfFobjDropitem::emitDropgold's amount (the name is not the original's)
    // fn_7100287E30's amount; GfFobjDropitem::applyGetItem hands it to btl::Utility::fn_7100010900 (the name is not
    // the original's)
    unsigned int m_amount;
    // the field object row (GfInitParamFobj's m_objId); GfFobjDropitem::initialize reads its "dropSE" (the name is
    // not the original's)
    unsigned int m_fobjId;
    // GfFobjDropitem::emitDropitem stores its float argument (the value of the drop list entry) here
    float pad_8c;
    bool pad_90;
};
}  // namespace gf

#endif
