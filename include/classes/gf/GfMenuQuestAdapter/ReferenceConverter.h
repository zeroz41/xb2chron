#ifndef CLASSES_GF_GFMENUQUESTADAPTER_REFERENCECONVERTER_H
#define CLASSES_GF_GFMENUQUESTADAPTER_REFERENCECONVERTER_H

#include "classes/gf/GfMenuQuestAdapter.h"

namespace gf { class QuestID; }

namespace gf {
// table 0x7100B5D8A8
class GfMenuQuestAdapter::ReferenceConverter {
public:
    virtual ~ReferenceConverter();  // slot 0
    virtual void getQuestID(gf::QuestID&);  // slot 2
};
}  // namespace gf

#endif
