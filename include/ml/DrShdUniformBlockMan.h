#ifndef ML_DRSHDUNIFORMBLOCKMAN_H
#define ML_DRSHDUNIFORMBLOCKMAN_H

namespace grlib {
class CGLibTriUniformBlock;
class CGLibTriUniformArray;
class CGLibDblUniformArray;
class CGLibOneUniformArray;
}

namespace ml {
struct MdsMpfMatTopHeader;
class DrResMdoVertex;

// Builds the model uniform blocks (its members take no object).
class DrShdUniformBlockMan {
public:
    // the uniform block table of a model's data (createMotionBlendObj; the names are not the original's)
    struct BlockInfo {
        unsigned int m_dataOfs;  // 0x0: from the vertex memory pool's data
        int m_size;  // 0x4: times m_num the block's size
        int m_num;  // 0x8
        unsigned char pad_c[0x2];
        unsigned char m_flags;  // 0xE, bit 0: the block gets uniform memory and a copy of its data
        unsigned char pad_f[0x1];
    };
    struct BlockHeader {
        unsigned char pad_0[0x8];
        int m_num;  // 0x8
        unsigned int m_infoOfs;  // 0xC: BlockInfo[m_num], from the model data
    };
    struct DataHead {
        unsigned char pad_0[0x28];
        unsigned int m_blockHeaderOfs;  // 0x28: its BlockHeader, from the model data
    };

    static void createUniformBoneObj(grlib::CGLibTriUniformBlock* block, int num);
    static void createUniformMdlObj(grlib::CGLibTriUniformArray* array, int num);
    static void createUniformVolTexCalcObj(grlib::CGLibDblUniformArray* array, unsigned int num);
    static void createUniformRimBloomCalcObj(grlib::CGLibDblUniformArray* array);
    static void createUniformMpfMaterialObj(grlib::CGLibDblUniformArray* array, const MdsMpfMatTopHeader* header);
    static void createMotionBlendObj(grlib::CGLibOneUniformArray* array, const unsigned char* data, DrResMdoVertex* vtx);
    static void changeMotionBlendObj(grlib::CGLibOneUniformArray* array, const unsigned char* data, DrResMdoVertex* vtx);
};
}  // namespace ml

#endif
