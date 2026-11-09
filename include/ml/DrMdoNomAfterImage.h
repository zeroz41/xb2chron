#ifndef ML_DRMDONOMAFTERIMAGE_H
#define ML_DRMDONOMAFTERIMAGE_H

#include "classes/ml/DrMan.h"
#include "classes/ml/DrMdlObj.h"
#include "ml/DrMdoNomClone.h"
#include "mm/mtl/FixStr.h"
#include "mtl/MemManager.h"

namespace mm { class Col3; class Vec3; }

namespace ml {
class DrMdoCtlNom;

// A normal model's after image: create clones the model m_num times (DrCreator::createMdl) into m_list;
// DrMdoCtlNom::createAfterImage news one (0xD8 bytes) into DrMdoCtlNom::m_afterImageStock[DrMan::s_nDblStockIdx].
// Field names are not the original's.
class DrMdoNomAfterImage : public DrMdoNomClone {
public:
    // one clone (0x20 bytes)
    struct wrkObjList {
        unsigned char pad_0[0x10];
        DrMdlObj* m_mdl;  // 0x10
        float m_alpha;  // 0x18, set from 0x18 of the after image (the name is not the original's)
        unsigned char pad_1C[0x4];
    };

    DrMdoNomAfterImage() {
        m_list = nullptr;
        m_num = 0;
        pad_A = 0;
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
    short pad_A;
    unsigned char pad_C[0x14];
    // 0x20: a bit per double-buffer index, set by DrMdoCtlNom::createAfterImage/releaseAfterImage on the
    // after image they replace (the name is not the original's)
    unsigned int m_flags;
    unsigned char pad_24[0x30];
    mm::mtl::FixStr<128> m_name;  // 0x54, create copies the model's name (DrMdoCtlNom 0x238) into it
};
}  // namespace ml

#endif
