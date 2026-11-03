#ifndef CLASSES_GMK_TUNK_B6EE88_H
#define CLASSES_GMK_TUNK_B6EE88_H

#include "classes/gmk/TGmkList.h"
#include "classes/gmk/TUnk_B6D5F8.h"

namespace gmk {
// table 0x7100B6EE88; base TGmkList<TUnk_B6D5F8, ...> (table 0x7100B6EF30, magic 'BCRP'). Placeholder name: the
// list of kind 0x3D, new in 3.0.1; nothing in 1.0.0 names it. GmkSet::createGmkLists constructs it inline
// (the base's table, then this one).
// It overrides the deleting destructor.
class TUnk_B6EE88 : public ::gmk::TGmkList< ::gmk::TUnk_B6D5F8, ::gmk::TUnk_B6D5F8::BdatInfo, 1347568450u, 3u, ::gmk::TUnk_B6D5F8Gob> {
public:
    explicit TUnk_B6EE88(unsigned int updateGmkNumPerFrame)
        : TGmkList(updateGmkNumPerFrame) {}
    // slot 0: inline, so its D2 is the base's (the table's slot 0 is TGmkList's D2)
    virtual ~TUnk_B6EE88() {}
};
}  // namespace gmk

#endif
