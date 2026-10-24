#ifndef ML_DRRESSHDSHW_H
#define ML_DRRESSHDSHW_H

#include "ml/DrShdDataObj.h"

namespace ml {
class DrResFetch;

// A shadow shader's settings: the constructor runs s_callShwSet[type], which fills m_shaderSel.
class DrResShdShw {
public:
    DrResShdShw(DrShdDataObj* data, int type);
    void setupShader(DrResFetch* fetch);
    void setDecAType(unsigned int idx);
    void setDecBType(unsigned int idx);
    void shwShdset_DefObj();
    void shwShdset_Inst();
    void shwShdset_Mot();
    void shwShdset_InstMot();
    void shwShdset_Fw();

    static void (DrResShdShw::*s_callShwSet[5])();

    // Field names are not the original's (m_*TypeOfs follow the declaration names they hold).
    DrShdDataObj* m_data;          // 0x0
    int m_shaderSel[7];            // 0x8: -1 until a shwShdset_* member sets them
    unsigned short m_texTypeOfs;   // 0x24: "TEX_TYPE"
    unsigned short m_sptTypeOfs;   // 0x26: "SPT_TYPE"
    unsigned short m_flags;        // 0x28: bit 0 while the constructor sets up
    unsigned short m_type;         // 0x2A: index into s_callShwSet
};
}  // namespace ml

#endif
