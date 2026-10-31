#ifndef GRLIB_CGLIBUTILOBJ_H
#define GRLIB_CGLIBUTILOBJ_H

#include "grlib/CGLibDecShader.h"
#include "grlib/CGLibVtxFetch.h"
#include "grlib/CGLibSampler.h"
#include "grlib/CGLibVtxVertex.h"
#include "grlib/CGLibVtxIndex.h"

namespace grlib {
// the context's utility objects (0x128 bytes: CGLibSystemContext holds it at 0x2320, two pointers follow it). Its
// constructor (out of line, CGLibUtilObj's unit) builds the shader, three vertex fetches, two samplers and a vertex
// object at 0xD8 and an index object at 0x100; setup fills them with the utility shader and a screen quad (the
// field names are not the original's).
class CGLibUtilObj {
public:
    CGLibUtilObj();
    ~CGLibUtilObj();
    void setup();
    void release();

    CGLibDecShader m_decShader;       // 0x0: CGLibCtlShader::getDecShader
    CGLibVtxFetch m_vtxFetches[3];    // 0x68: CGLibCtlShader::getVtxFetch
    CGLibSampler m_samplers[2];       // 0x98: CGLibCtlShader::getSampler
    CGLibVtxVertex m_vtxVertex;       // 0xD8: the screen quad
    CGLibVtxIndex m_vtxIndex;         // 0x100
};
}  // namespace grlib

#endif
