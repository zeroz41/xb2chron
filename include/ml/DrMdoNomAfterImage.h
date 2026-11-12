#ifndef ML_DRMDONOMAFTERIMAGE_H
#define ML_DRMDONOMAFTERIMAGE_H

#include "classes/ml/DrMan.h"
#include "classes/ml/DrMdlObj.h"
#include "ml/DrMdoNomClone.h"
#include "mm/mtl/FixStr.h"
#include "mtl/MemManager.h"
#include "mm/Col3.h"
#include "mm/Vec3.h"

namespace ml {
class DrMdoCtlNom;

// A normal model's after image: create clones the model m_num times (DrCreator::createMdl) into m_list;
// DrMdoCtlNom::createAfterImage news one (0xD8 bytes) into DrMdoCtlNom::m_afterImageStock[DrMan::s_nDblStockIdx].
// Field names are not the original's.
class DrMdoNomAfterImage : public DrMdoNomClone {
public:
    // one clone (0x20 bytes)
    struct wrkObjList {
        mm::Vec3 m_pos;  // 0x0: captureObj takes the model's matrix translation (the name is not the original's)
        DrMdlObj* m_mdl;  // 0x10
        // 0x18: updateParam advances it by its time step up to m_life; captureObj restarts it at 0 (the name is
        // not the original's)
        float m_time;
        unsigned char pad_1C[0x4];
    };

    DrMdoNomAfterImage() {
        m_list = nullptr;
        m_num = 0;
        m_cur = 0;
        m_flags = 0;
    }
    // the clones get setDeleteCall for the stock buffer, then the list is freed (create starts with the same)
    ~DrMdoNomAfterImage() {
        if (m_num != 0) {
            for (int i = 0; i < m_num; i++) {
                m_list[i].m_mdl->setDeleteCall(DrMan::s_nDblStockIdx);
            }
            m_num = 0;
            if (m_list != nullptr) {
                mtl::MemManager::deallocate(m_list, 0, false);
                m_list = nullptr;
            }
        }
    }

    void create(const DrMdoCtlNom*, float, float, float, const mm::Col3&, float, float, float, const mm::Col3&, float,
                float, float);
    void updateParam(wrkObjList*, const DrMdoCtlNom*, float, const mm::Vec3&);
    void captureObj(const DrMdoCtlNom*);

    wrkObjList* m_list;  // 0x0
    short m_num;  // 0x8
    short m_cur;  // 0xA: the clone captureObj fills next, wrapping at m_num (the name is not the original's)
    unsigned char pad_C[0x8];
    // updateParam fades a clone's alpha out between m_fadeStart and m_life and blends its rim bloom from the
    // start set (0x24) to the end set (0x3C) over m_life (the names are not the original's)
    float m_fadeStart;  // 0x14
    float m_life;  // 0x18
    unsigned char pad_1C[0x4];
    // 0x20: a bit per double-buffer index, set by DrMdoCtlNom::createAfterImage/releaseAfterImage on the
    // after image they replace (the name is not the original's)
    unsigned int m_flags;
    // 0x24/0x3C: the rim bloom work (MdoRimBloomWrk's first 0x18 bytes) at the start and the end of a clone's life
    mm::Col3 m_rimColorStart;  // 0x24
    float m_rimPowerStart;  // 0x30
    float m_rimBlackRatioStart;  // 0x34
    float m_rimEmissiveStart;  // 0x38
    mm::Col3 m_rimColorEnd;  // 0x3C
    float m_rimPowerEnd;  // 0x48
    float m_rimBlackRatioEnd;  // 0x4C
    float m_rimEmissiveEnd;  // 0x50
    mm::mtl::FixStr<128> m_name;  // 0x54, create copies the model's name (DrMdoCtlNom 0x238) into it
};
}  // namespace ml

#endif
