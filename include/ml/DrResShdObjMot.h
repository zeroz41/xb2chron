#ifndef ML_DRRESSHDOBJMOT_H
#define ML_DRRESSHDOBJMOT_H

#include "ml/DrShdDataObj.h"

namespace ml {

// A motion-blur shader's settings: the constructor runs s_callMotObjSet[type], whose motblur_* member fills
// m_shaderSel with select values and the uniform block offsets / texture location of the current shader.
class DrResShdObjMot {
public:
    DrResShdObjMot(DrShdDataObj* data, int type);
    void motblur_motObj();
    void motblur_motObjTex();
    void motblur_notObj();
    void motblur_notObjTex();

    static void (DrResShdObjMot::*s_callMotObjSet[6])();

    // Field names are not the original's.
    DrShdDataObj* m_data;          // 0x0
    int m_shaderSel[5];            // 0x8: -1 until a motblur_* member sets them
    unsigned short m_flags;        // 0x1C: bit 0 while the constructor sets up
    unsigned short m_type;         // 0x1E: index into s_callMotObjSet
};
}  // namespace ml

#endif
