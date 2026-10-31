#ifndef GF_ITEMGETPARAM_H
#define GF_ITEMGETPARAM_H

namespace gf {

// how near a dropped item must be to be taken: entry 5 ("item_get") of the param manager's list 5
// (GfFobjDropitem::canGetItem's). The names are 1.0.0's (ItemGetParam::createReflection registers the fields by
// name and offset).
struct ItemGetParam {
    float radius;  // the reach across the ground (plus the owner bonus and GfFobjManager's leader bonus)
    float upper;   // how far above the taker the item may be
    float lower;   // and below
};

}  // namespace gf

#endif
