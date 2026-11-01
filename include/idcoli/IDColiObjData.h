#ifndef IDCOLI_IDCOLIOBJDATA_H
#define IDCOLI_IDCOLIOBJDATA_H

#include "classes/idcoli/IDColiObjBase.h"
#include "mtl/MemManager.h"

namespace mm { class Mat44; }

namespace idcoli {
// a primitive's entry in a 'CHCL' binary; only its size (the first member, what the primset functions hand the
// IDColiPrimitive creators) is declared
class CHCLBaseData {
public:
    mm::Vec3 m_size;
};
class CHCLBaseInfo;

// a 'CHCL' binary's header and the block its m_infoOffset points to (only what this unit reads; the names are not
// the original's)
class CHCLHeader {
public:
    unsigned int m_magic;  // 'CHCL'
    unsigned int m_version;  // 0x2712
    unsigned int m_flags;  // 1: no primitive work, 2: m_subObj
    unsigned int m_infoOffset;
};
class CHCLInfo {
public:
    unsigned int m_dataOffset;
    int m_primNum;
    unsigned int m_boneOffset;
    int m_boneNum;
    unsigned char pad_10[0x10];
    unsigned int m_primIndexOffset;  // 0x20, unsigned shorts indexing IDColiObjData::m_primWork
    int m_primIndexNum;  // 0x24
};

// a collision object built from collision data (1.0.0's table _ZTVN6idcoli13IDColiObjDataE derives it from
// IDColiObjBase); IDColiParmsCharacter and IDColiParmsBone reach a character's through it. Only the members their
// code uses are declared; the field names are not the original's.
class IDColiObjData : public IDColiObjBase {
public:
    // a bone's entry in the binary (0x44 bytes; the name is not the original's)
    struct BoneInfo {
        unsigned char pad_0[0x40];
        unsigned int m_nameOffset;  // 0x40, from the binary's start
    };
    // a primitive's work: its base shape and type (0xC0 bytes; the names are not the original's)
    struct PrimWork {
        unsigned char m_base[0xB0];
        IDColiBaseType m_baseType;  // 0xB0
        unsigned char pad_b4[0xC];
    };
    const CHCLInfo* getInfo() const {
        return reinterpret_cast<const CHCLInfo*>(reinterpret_cast<const char*>(m_binary) + m_binary->m_infoOffset);
    }
    const unsigned short* getPrimIndices(const CHCLInfo* info) const {
        return reinterpret_cast<const unsigned short*>(reinterpret_cast<const char*>(m_binary) +
                                                       info->m_primIndexOffset);
    }
    IDColiObjData(IDColiTreeTop* tree) : IDColiObjBase(tree) {
        m_binary = nullptr;
        m_work = nullptr;
        m_primWork = nullptr;
        m_boneNum = 0;
        m_primNum = 0;
        m_subObj = nullptr;
    }
    void createBinary(const void* data);
    void calcNodeMatrix(mm::Mat44& out, const mm::Mat44& parent, const CHCLBaseData* data, const CHCLBaseInfo* info);
    void calcLinkNodeMatrix(mm::Mat44& out, const CHCLBaseInfo* info);
    void primset_sphere(void* base, IDColiBaseType& type, const CHCLBaseData* data, const CHCLBaseInfo* info);
    void primset_capsule(void* base, IDColiBaseType& type, const CHCLBaseData* data, const CHCLBaseInfo* info);
    void primset_bone_capsule(void* base, IDColiBaseType& type, const CHCLBaseData* data, const CHCLBaseInfo* info);
    void primset_box(void* base, IDColiBaseType& type, const CHCLBaseData* data, const CHCLBaseInfo* info);
    void primset_base(void* base, IDColiBaseType& type, const CHCLBaseData* data, const CHCLBaseInfo* info);
    void primset_poli(void* base, IDColiBaseType& type, const CHCLBaseData* data, const CHCLBaseInfo* info);
    void primset_subbase(void* base, IDColiBaseType& type, const CHCLBaseData* data, const CHCLBaseInfo* info);
    const char* getBoneName(int index) const;
    void setBoneMatrix(int index, const mm::Mat44& matrix);
    // releases m_subObj when flag 0x200 is set (release, createBinary and the destructors; inferred name)
    void releaseSubObj() {
        if (m_flags & 0x200) {
            m_flags &= ~0x200;
            if (m_subObj != nullptr) {
                m_subObj->release();
            }
            m_subObj = nullptr;
        }
    }
    // frees createBinary's work buffer (createBinary and the destructors; inferred name)
    void releaseWork() {
        if (m_work != nullptr) {
            mtl::MemManager::deallocate(m_work, 0, false);
            m_work = nullptr;
        }
        m_primWork = nullptr;
        m_boneNum = 0;
        m_primNum = 0;
    }
    const CHCLHeader* m_binary;  // 0x1D0, the 'CHCL' data createBinary was given
    BoneInfo* m_boneInfo;  // 0x1D8
    void* m_work;  // 0x1E0, createBinary's allocation
    PrimWork* m_primWork;  // 0x1E8, inside m_work after the bone matrices
    mm::Mat44* m_boneMatrix;  // 0x1F0, at m_work
    int m_boneNum;  // 0x1F8, IDColiParmsBone::getBoneMax
    int m_primNum;  // 0x1FC
    IDColiObj* m_subObj;  // 0x200
    unsigned char pad_208[8];
    int pad_210;  // IDColiObjChar::update zeroes it
    // two floats, not an array: IDColiObjChar::update zeroes them with one 8-byte store, not 0x210 with 0x214
    float pad_214;  // IDColiObjChar::update zeroes it
    float pad_218;  // IDColiObjChar::update zeroes it
    unsigned char pad_21c[4];
    float m_adsorption;  // 0x220, IDColiParmsCharacter::setAdsorption
};
}  // namespace idcoli

#endif
