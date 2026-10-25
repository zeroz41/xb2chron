#ifndef ML_DRGPUCHECKRENDER_H
#define ML_DRGPUCHECKRENDER_H

#include "grlib/CGLibDblUniformBlock.h"
#include "mm/Vec4.h"

namespace grlib { class CGLibVtxInstans; }

namespace ml {
class DrCalcViewWork;
class DrShdDataList;

// draws DrGpuCheckObj's occlusion queries (DrMdlMan::m_gpuCheckRender): each object puts its position and radius
// (16 bytes) in the instance ring and draws a box (mode 2) or a quad (mode 1) with shader 8. The field names are
// not the original's.
class DrGpuCheckRender {
public:
    DrGpuCheckRender();
    ~DrGpuCheckRender();
    void beginUpdate();
    void endUpdate();
    void beginRender(bool clear);
    void endRender();
    void render(unsigned int ofs, int mode);

    DrCalcViewWork* m_viewWork;      // 0x0, DrMan's current DrCalcMan's
    DrShdDataList* m_shdList;        // 0x8
    grlib::CGLibVtxInstans* m_instans;  // 0x10, DrMdlMan's vertex manager's
    grlib::CGLibDblUniformBlock m_uniform;  // 0x18 (0x80 bytes)
    mm::Vec4* m_instansBuff;         // 0x50, where the next object's position and radius go
    unsigned int m_instansOfs;       // 0x58, its offset in the ring
    unsigned int m_instansStart;     // 0x5C, the offset at beginUpdate
    unsigned int m_declOfs;          // 0x60, the shader's "EFFMODE" declaration
    int m_mode;                      // 0x64, the mode the shader is set up for
};
}  // namespace ml

#endif
