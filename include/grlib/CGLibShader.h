#ifndef GRLIB_CGLIBSHADER_H
#define GRLIB_CGLIBSHADER_H

#include "nvn/nvn.h"

namespace grlib {

// the reflection data a program's binary carries, four resource tables (uniform blocks, storage buffers, textures,
// images): entries found by name, a table from a binding location to its entry (0xFF: none), and per entry the
// shader stages it is bound in (stage index, binding pairs). Read by CGLibShader::getUniformBlockOfs,
// getTextureLocation and the CGLibShader_plf binders; the names are not the original's.
struct CGLibShaderBufferInfo {  // a uniform block or storage buffer (0x10 bytes)
    unsigned int m_nameOfs;  // 0x0, from the binary's start
    unsigned char pad_4[0x4];
    unsigned int m_stageOfs;  // 0x8, from the binary's start
    unsigned char m_location;  // 0xC
    unsigned char m_stageNum;  // 0xD
    unsigned short m_size;  // 0xE
};
struct CGLibShaderTextureInfo {  // a texture or image (0xC bytes)
    unsigned int m_nameOfs;  // 0x0, from the binary's start
    unsigned int m_stageOfs;  // 0x4, from the binary's start
    unsigned char m_location;  // 0x8
    unsigned char m_stageNum;  // 0x9
    unsigned char pad_A[0x2];
};
struct CGLibShaderResourceTbl {
    short m_num;  // 0x0
    unsigned short m_locationNum;  // 0x2
    unsigned int m_entryOfs;  // 0x4, from the binary's start
    unsigned int m_locationTblOfs;  // 0x8, from the binary's start
};
struct CGLibShaderInfo {
    unsigned char pad_0[0x20];
    CGLibShaderResourceTbl m_uniformBlocks;  // 0x20
    CGLibShaderResourceTbl m_storageBuffers;  // 0x2C
    CGLibShaderResourceTbl m_textures;  // 0x38
    CGLibShaderResourceTbl m_images;  // 0x44
};

// the platform part of a shader program: its binary and reflection data, and the NVN binding of its resources
// (the field names are not the original's)
class CGLibShader_plf {
public:
    void setUniformBlock(unsigned int location, NVNcommandBuffer* pCmdBuf, unsigned long gpuAddress, unsigned int size);
    void setStorageBuffer(unsigned int location, NVNcommandBuffer* pCmdBuf, unsigned long gpuAddress, unsigned int size);
    void setTextureHandle(unsigned int location, NVNcommandBuffer* pCmdBuf, unsigned long handle);
    void setImageHandle(unsigned int location, NVNcommandBuffer* pCmdBuf, unsigned long handle);

    unsigned char* m_pData;  // 0x0
    const CGLibShaderInfo* m_pInfo;  // 0x8
};

// one shader program (0xD8 bytes): where its textures and uniform blocks are bound
class CGLibShader : public CGLibShader_plf {
public:
    unsigned int getTextureLocation(const char* name) const;
    unsigned int getUniformBlockOfs(const char* name) const;
    // the size of the uniform block bound at a location, 0 for none (inline: no copy of its own; the name is not
    // the original's)
    unsigned int getUniformBlockSize(unsigned int location) const {
        const CGLibShaderResourceTbl& tbl = m_pInfo->m_uniformBlocks;
        if (location <= tbl.m_locationNum) {
            unsigned int idx = (m_pData + tbl.m_locationTblOfs)[location];
            if (idx != 0xFF) {
                return reinterpret_cast<const CGLibShaderBufferInfo*>(m_pData + tbl.m_entryOfs)[idx].m_size;
            }
        }
        return 0;
    }

    unsigned char pad_10[0x4];
    // the stages the program holds and the NVN program CGLibCtlShader::setShader binds (the names are not the
    // original's)
    unsigned int m_stages;  // 0x14
    NVNprogram m_program;  // 0x18
};

}  // namespace grlib

#endif
