#ifndef ML_DRMDOTEXTUREMAN_H
#define ML_DRMDOTEXTUREMAN_H

#include "ml/DrMdoResList.h"
#include "ml/DrResEtcTexList.h"
#include "ml/DrResMdoTexList.h"

namespace grlib { class CGLibTextureBuffer; }

namespace ml {
class DrMan;

// The model texture manager (no table: its constructor stores none). Field names are not the original's.
class DrMdoTextureMan {
public:
    DrMdoTextureMan(DrMan* drMan);
    ~DrMdoTextureMan();
    grlib::CGLibTextureBuffer* getTextureID(unsigned int id);

    DrMan* m_pDrMan;                              // 0x0
    DrMdoResList<DrResMdoTexList> m_texList;      // 0x8
    DrMdoResList<DrResEtcTexList> m_etcTexList;   // 0x18: getTextureID searches it
};
}  // namespace ml

#endif
