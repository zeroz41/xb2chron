#ifndef CLASSES_GF_GFFIELDGIMMICK_H
#define CLASSES_GF_GFFIELDGIMMICK_H

namespace gf {
// static helpers of gf_field_gimmick.cpp (only the ones gf_field_locator calls are declared)
class GfFieldGimmick {
public:
    // the FLD_maplist id of the map an RSC_GmkSetList row belongs to
    static int getBdatIdFrom_RSC_GmkSetList_To_FLD_maplist(int gmkSetId);
};
}  // namespace gf

#endif
