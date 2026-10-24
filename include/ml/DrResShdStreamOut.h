#ifndef ML_DRRESSHDSTREAMOUT_H
#define ML_DRRESSHDSTREAMOUT_H

#include "ml/DrShdDataObj.h"

namespace ml {

// A stream-out shader's settings: the constructor runs s_callStmOuSet[type], which fills m_shaderSel.
class DrResShdStreamOut {
public:
    DrResShdStreamOut(DrShdDataObj* data, int type);
    void setupStreamShader(unsigned int idx);
    void setDecNum(unsigned int idx);
    void stmShdset_Weight();
    void stmShdset_WetVtx();
    void stmShdset_MofSet();
    void stmShdset_MeshVtxSet();

    static void (DrResShdStreamOut::*s_callStmOuSet[9])();

    // Field names are not the original's (m_wetNumOfs follows the declaration name it holds).
    DrShdDataObj* m_data;          // 0x0
    int m_shaderSel[3];            // 0x8: -1 until a stmShdset_* member sets them
    unsigned short m_type;         // 0x14: index into s_callStmOuSet
    unsigned short m_wetNumOfs;    // 0x16: "WET_NUM"
};
}  // namespace ml

#endif
