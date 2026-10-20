#ifndef CLASSES_GF_GFMENUMSGLIST_H
#define CLASSES_GF_GFMENUMSGLIST_H

#include "classes/ui/UIListInfo.h"

namespace gf { class MsgID; }

namespace gf {
// table 0x7100B5F6A8
class GfMenuMsgList : public ::ui::UIListInfo< ::gf::MsgID> {
public:
    virtual ~GfMenuMsgList();  // slot 0
};
}  // namespace gf

#endif
