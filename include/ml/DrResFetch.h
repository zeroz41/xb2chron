#ifndef ML_DRRESFETCH_H
#define ML_DRRESFETCH_H

#include "grlib/CGLibVtxFetch.h"

namespace ml {
// The vertex fetch resource. Only the static vertex attribute setters are declared so far; the layout is not.
class DrResFetch {
public:
    // fills one vertex attribute: format, shader location, offset in the vertex, stream
    typedef void (*SetVertFunc)(int offset, unsigned int location, grlib::CGLibVtxAttr& attr);
    static void vert_set_VEC3(int offset, unsigned int location, grlib::CGLibVtxAttr& attr);
    static void vert_set_BYTE(int offset, unsigned int location, grlib::CGLibVtxAttr& attr);
    static void vert_set_USHORT2(int offset, unsigned int location, grlib::CGLibVtxAttr& attr);
    static void vert_set_VEC2(int offset, unsigned int location, grlib::CGLibVtxAttr& attr);
    static void vert_set_U32(int offset, unsigned int location, grlib::CGLibVtxAttr& attr);
    static void vert_set_SHORT4(int offset, unsigned int location, grlib::CGLibVtxAttr& attr);
    static void vert_set_GmPos4(int offset, unsigned int location, grlib::CGLibVtxAttr& attr);
    static void vert_set_GmScl2(int offset, unsigned int location, grlib::CGLibVtxAttr& attr);
    static void vert_set_GmCol4(int offset, unsigned int location, grlib::CGLibVtxAttr& attr);
    static void vert_set_GmCal1(int offset, unsigned int location, grlib::CGLibVtxAttr& attr);
    static void vert_set_GmCal2(int offset, unsigned int location, grlib::CGLibVtxAttr& attr);
    static void vert_set_GmCal3(int offset, unsigned int location, grlib::CGLibVtxAttr& attr);
    static void vert_set_GmInt(int offset, unsigned int location, grlib::CGLibVtxAttr& attr);
    static void vert_set_S32(int offset, unsigned int location, grlib::CGLibVtxAttr& attr);
    static void vert_set_GmFloat(int offset, unsigned int location, grlib::CGLibVtxAttr& attr);
    static void vert_set_OutLineNom(int offset, unsigned int location, grlib::CGLibVtxAttr& attr);
    static void vert_set_OutLineCol(int offset, unsigned int location, grlib::CGLibVtxAttr& attr);
    static void vert_set_MofPos(int offset, unsigned int location, grlib::CGLibVtxAttr& attr);
    static void vert_set_MofNom(int offset, unsigned int location, grlib::CGLibVtxAttr& attr);
    static void vert_set_MofTan(int offset, unsigned int location, grlib::CGLibVtxAttr& attr);
    static void vert_set_MofNewTan(int offset, unsigned int location, grlib::CGLibVtxAttr& attr);
    static void vert_set_SHORT2(int offset, unsigned int location, grlib::CGLibVtxAttr& attr);

    static SetVertFunc s_callSetVert[52];
};
}  // namespace ml

#endif
