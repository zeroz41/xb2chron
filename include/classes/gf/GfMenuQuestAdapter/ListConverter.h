#ifndef CLASSES_GF_GFMENUQUESTADAPTER_LISTCONVERTER_H
#define CLASSES_GF_GFMENUQUESTADAPTER_LISTCONVERTER_H

#include "classes/gf/GfMenuQuestAdapter.h"

namespace gf { class QuestID; }

namespace gf {
// table 0x7100B5D8D0
class GfMenuQuestAdapter::ListConverter {
public:
    virtual ~ListConverter();  // slot 0
    virtual void getQuestID(gf::QuestID&);  // slot 2
};
}  // namespace gf

#endif
