#ifndef GRLIB_CGLIBSHADER_H
#define GRLIB_CGLIBSHADER_H

#include "nvn/nvn.h"
#include "nvn/nvn_FuncPtrInline.h"
#include "classes/grlib/CGLibManager.h"
#include "grlib/CGLibVtlMemPool.h"

namespace grlib {

// the reflection data a program's binary carries, four resource tables (uniform blocks, storage buffers, textures,
// images): entries found by name, a table from a binding location to its entry (0xFF: none), and per entry the
// shader stages it is bound in (stage index, binding pairs). Read by CGLibShader::getUniformBlockOfs,
// getTextureLocation and the CGLibShader_plf binders; the names are not the original's.
struct CGLibShaderBufferInfo {  // a uniform block or storage buffer (0x10 bytes)
    unsigned int m_nameOfs;  // 0x0, from the binary's start
    // 0x4, 0x6: the block's member values, an index into CGLibShaderInfo::m_valTblOfs's table
    // (getUniformBlockValOfs; the names are not the original's)
    unsigned short m_valNum;  // 0x4
    unsigned short m_valIdx;  // 0x6
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
struct CGLibShaderStageInfo {  // a stage's code (0x14 bytes; the names are not the original's)
    unsigned char m_stage;  // 0x0: an NVNshaderStage (5: compute)
    unsigned char pad_1[0x3];
    unsigned int m_codeOfs;  // 0x4: from createShader's code offset in the pool
    unsigned char pad_8[0x4];
    unsigned int m_controlOfs;  // 0xC: in createShader's control sections
    unsigned char pad_10[0x4];
};
struct CGLibShaderInfo {
    unsigned char pad_0[0x18];
    int m_stageOfs;  // 0x18: the CGLibShaderStageInfo table, from the binary's start (the name is not the original's)
    unsigned int m_stageNum;  // 0x1C (the name is not the original's)
    CGLibShaderResourceTbl m_uniformBlocks;  // 0x20
    CGLibShaderResourceTbl m_storageBuffers;  // 0x2C
    CGLibShaderResourceTbl m_textures;  // 0x38
    CGLibShaderResourceTbl m_images;  // 0x44
    unsigned char pad_50[0xC];
    // the uniform blocks' member values (CGLibShaderValInfo, getUniformBlockValOfs; the name is not the original's)
    unsigned int m_valTblOfs;  // 0x5C, from the binary's start
};
struct CGLibShaderValInfo {  // a uniform block member (0x8 bytes)
    unsigned int m_nameOfs;  // 0x0, from the binary's start
    unsigned int m_ofs;  // 0x4: its offset in the block
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

// the kind of shader createShader builds (its values are not known: createShader does not read it;
// CGLibDecShader::setupMemPoolShader passes its bool flag)
enum CGLibShderType {};

// one shader program (0xD8 bytes): where its textures and uniform blocks are bound
class CGLibShader : public CGLibShader_plf {
public:
    unsigned int getTextureLocation(const char* name) const;
    unsigned int getUniformBlockOfs(const char* name) const;
    // the offset of the member called name in the uniform block bound at location, -1 for none (the parameter
    // names are not the original's)
    unsigned int getUniformBlockValOfs(unsigned int location, const char* name) const;
    // initializes m_program from the reflection data, its code at codeOfs in pool and the control sections
    // (the parameter names are not the original's)
    void createShader(const unsigned char* data, unsigned int codeOfs, const unsigned char* control,
                      CGLibVtlMemPool* pool, CGLibShderType type);
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

    // finalizes m_program when it is initialized (inline: createShader does it twice, CGLibDecShader::release per
    // program; the name is not the original's)
    void releaseProgram() {
        if (m_flags & 1) {
            m_pData = nullptr;
            nvnProgramFinalize(&m_program);
            m_flags &= ~5;
        }
    }

    // initializes m_program from the reflection data, its code at codeOfs in pool and the control sections
    // (inline: createShader and CGLibDecShader::changeMemPoolSetMem inline it; the name is not the original's)
    void setupProgram(const unsigned char* data, unsigned int codeOfs, const unsigned char* control,
                      CGLibVtlMemPool* pool) {
        releaseProgram();
        nvnProgramInitialize(&m_program, &CGLibManager::sys()->m_device);
        m_stages = 0;
        const CGLibShaderInfo* pInfo = reinterpret_cast<const CGLibShaderInfo*>(data);
        const CGLibShaderStageInfo* pStage = reinterpret_cast<const CGLibShaderStageInfo*>(data + pInfo->m_stageOfs);
        NVNbufferAddress poolAddress = pool->m_gpuAddress;
        m_stages = (pStage->m_stage == 5) ? 0x20 : 0x1F;
        NVNshaderData stageData[6];
        unsigned int num = pInfo->m_stageNum;
        long i;
        for (i = 0; i < num; i++, pStage++) {
            stageData[i].control = control + pStage->m_controlOfs;
            stageData[i].data = poolAddress + codeOfs + pStage->m_codeOfs;
        }
        nvnProgramSetShaders(&m_program, i, stageData);
        m_flags |= 1;
        m_pData = const_cast<unsigned char*>(data);
        m_pInfo = pInfo;
    }

    // bit 0: m_program is initialized (CGLibDecShader::release finalizes it and clears bits 0 and 2; the name is
    // not the original's)
    unsigned int m_flags;  // 0x10
    // the stages the program holds and the NVN program CGLibCtlShader::setShader binds (the names are not the
    // original's)
    unsigned int m_stages;  // 0x14
    NVNprogram m_program;  // 0x18
};

}  // namespace grlib

#endif
