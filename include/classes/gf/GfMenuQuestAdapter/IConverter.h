#ifndef CLASSES_GF_GFMENUQUESTADAPTER_ICONVERTER_H
#define CLASSES_GF_GFMENUQUESTADAPTER_ICONVERTER_H

#include "classes/gf/GfMenuQuestAdapter.h"

namespace gf {
// table none (its derived classes'): where a quest adapter's update takes its quest from (the name is the other
// adapters' IConverter, not the original's)
class GfMenuQuestAdapter::IConverter {
public:
    virtual ~IConverter() {}  // slot 0
    virtual void getQuestID(QuestID& id) = 0;  // slot 2
};
}  // namespace gf

#endif
