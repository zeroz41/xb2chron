#ifndef CLASSES_GF_GFMENUOBJSALVAGE_H
#define CLASSES_GF_GFMENUOBJSALVAGE_H

#include "classes/gf/GfMenuObject.h"

namespace gf { class GfMenuCallContext; }

namespace gf {
// table 0x7100B645F8
class GfMenuObjSalvage : public ::gf::GfMenuObject {
public:
    class ResultListener;
    virtual ~GfMenuObjSalvage();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    // what openResult shows (the name of the field is not the original's: StateSalvageResultUi gives 1 to 3 by the
    // raffle's rank)
    struct ResultParam {
        ResultParam() : m_rank(0), m_unk2(0) {}
        unsigned short m_rank;
        unsigned short m_unk2;
    };
    static void openResult(GfMenuCallContext* context, const ResultParam& param);
};
}  // namespace gf

#endif
