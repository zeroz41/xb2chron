#ifndef CLASSES_GF_GFMENUQUESTLIST_H
#define CLASSES_GF_GFMENUQUESTLIST_H

#include "classes/ui/UIListInfo.h"

namespace gf { class QuestID; }

namespace gf {
// table 0x7100B5F760
class GfMenuQuestList : public ::ui::UIListInfo< ::gf::QuestID> {
public:
    virtual ~GfMenuQuestList();  // slot 0
};
}  // namespace gf

#endif
