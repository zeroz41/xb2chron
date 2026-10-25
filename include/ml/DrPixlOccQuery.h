#ifndef ML_DRPIXLOCCQUERY_H
#define ML_DRPIXLOCCQUERY_H

namespace ml {
class DrResQueryObj;

// DrPixlMan's pool of occlusion queries (DrPixlMan::m_occQuery). Only createObj is declared so far: it hands out
// a free DrResQueryObj, or nullptr (DrResUseQueryObj::begin tests it).
class DrPixlOccQuery {
public:
    DrResQueryObj* createObj();
};
}  // namespace ml

#endif
