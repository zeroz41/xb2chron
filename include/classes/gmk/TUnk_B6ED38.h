#ifndef CLASSES_GMK_TUNK_B6ED38_H
#define CLASSES_GMK_TUNK_B6ED38_H

#include "classes/gmk/TGmkList.h"
#include "classes/gmk/TUnk_B6D590.h"

namespace gmk {
// table 0x7100B6ED38; base TGmkList<TUnk_B6D590, ...> (table 0x7100B6EDE0, magic 'BCRW'). Placeholder name: the
// list of kind 0x3C, new in 3.0.1; nothing in 1.0.0 names it. GmkSet::createGmkLists constructs it inline
// (the base's table, then this one).
// It overrides the destructor and getInst (slot 6, fn_71005CF9E8: the base's code).
class TUnk_B6ED38 : public ::gmk::TGmkList< ::gmk::TUnk_B6D590, ::gmk::TUnk_B6D590::BdatInfo, 1465008962u, 1u, ::gmk::TUnk_B6D590Gob> {
public:
    explicit TUnk_B6ED38(unsigned int updateGmkNumPerFrame)
        : TGmkList(updateGmkNumPerFrame) {}
    virtual ~TUnk_B6ED38();  // slot 0
};
}  // namespace gmk

#endif
