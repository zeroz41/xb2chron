#ifndef GRLIB_CGLIBUTILOBJ_H
#define GRLIB_CGLIBUTILOBJ_H

#include "grlib/CGLibDecShader.h"
#include "grlib/CGLibVtxFetch.h"
#include "grlib/CGLibSampler.h"

namespace grlib {
// the context's utility objects (0x128 bytes: CGLibSystemContext holds it at 0x2320, two pointers follow it). Its
// constructor (out of line, CGLibUtilObj's unit) builds the shader, three vertex fetches, two samplers and a vertex
// object at 0xD8, then stores 0 at 0x100 and 0x110 and 5 at 0x118 (the field names are not the original's).
class CGLibUtilObj {
public:
    CGLibUtilObj();
    ~CGLibUtilObj();

    CGLibDecShader m_decShader;       // 0x0: CGLibCtlShader::getDecShader
    CGLibVtxFetch m_vtxFetches[3];    // 0x68: CGLibCtlShader::getVtxFetch
    CGLibSampler m_samplers[2];       // 0x98: CGLibCtlShader::getSampler
    unsigned char pad_D8[0x50];
};
}  // namespace grlib

#endif
