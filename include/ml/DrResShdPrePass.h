#ifndef ML_DRRESSHDPREPASS_H
#define ML_DRRESSHDPREPASS_H

#include "ml/DrShdDataObj.h"

namespace ml {
// A pre-pass shader's settings: the constructor runs s_callShdSet[type], which fills m_shaderSel (same shape as
// DrResShdShw). Field names are not the original's (m_passTypeOfs holds the "DECL_PASS_TYPE" declaration).
class DrResShdPrePass {
public:
    DrResShdPrePass(DrShdDataObj* data, int type);
    void setupShader(unsigned int fetch, unsigned int passType);
    void preshdset_Obj();
    void preshdset_ObjT();
    void preshdset_ObjT_Al();
    void preshdset_Mot();
    void preshdset_MotT();
    void preshdset_MotT_Al();
    void preshdset_Inst();
    void preshdset_InstT();
    void preshdset_Obj_Al();
    void preshdset_ObjT_Al_Fs();
    void preshdset_Mot_Al();
    void preshdset_MotT_Al_Fs();
    void preshdset_Inst_Al();
    void preshdset_InstT_Al();
    void preshdset_Inst_Bill_Al();
    void preshdset_InstT_Bill_Al();
    void preshdset_Fw();
    void preshdset_FwT();
    void preshdset_FwT_Al();
    void preshdset_Fw_Al();
    void preshdset_FwT_Al_Fs();

    static void (DrResShdPrePass::*s_callShdSet[42])();

    DrShdDataObj* m_data;          // 0x0
    int m_shaderSel[11];           // 0x8: -1 until a preshdset_* member sets them
    unsigned int m_passTypeOfs;    // 0x34: "DECL_PASS_TYPE"
    unsigned short m_flags;        // 0x38: bit 0 while the constructor sets up
    unsigned short m_type;         // 0x3A: index into s_callShdSet
};
}  // namespace ml

#endif
