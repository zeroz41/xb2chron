#ifndef CLASSES_ML_DRSHDLGTCLUSTERED_H
#define CLASSES_ML_DRSHDLGTCLUSTERED_H

#include "classes/ml/DrShdLgtDynamic.h"
#include "grlib/CGLibDblUniformBlock.h"
#include "ml/DrResFetch.h"

namespace ml { class DrLightMan; }
namespace ml { class DrMan; }
namespace ml { class DrLightObjPnt; }
namespace ml { class DrLightObjSpt; }
namespace ml { class DrShdLgtMan; }

namespace ml {
// table 0x7100B7E450
class DrShdLgtClustered : public ::ml::DrShdLgtDynamic {
public:
    // one cluster grid (c_ClusterSettings; the struct and field names are not the original's): the
    // constructor sizes each view's buffers from it
    struct ClusterSetting {
        int gridX;         // 0x0
        int gridY;         // 0x4
        int gridZ;         // 0x8, depth slices (addViewInfo fills gridZ + 1 slice depths)
        int cellLightMax;  // 0xC, the light-list entries one cell holds
        int lightMax;      // 0x10, stockPntList/stockSptList stop at it

        // inline (the name is not the original's)
        int getCellNum() const { return gridX * gridY * gridZ; }
    };
    // [m_bSmallGrid * 2 + (view != 0)]: view 0 has its own grid, views 1-3 share the second
    static const ClusterSetting c_ClusterSettings[4];
    // the view's grid (inline; the name is not the original's)
    const ClusterSetting& getClusterSetting(int view) const { return c_ClusterSettings[m_bSmallGrid * 2 + (view != 0)]; }

    // the bool is stored at 0x18 (true selects c_ClusterSettings' smaller grids; its meaning is not proven)
    DrShdLgtClustered(DrMan* drMan, bool flag);
    virtual ~DrShdLgtClustered();  // slot 0
    virtual void stockBegin();  // slot 2
    virtual void stockEnd();  // slot 3
    virtual void update();  // slot 4
    virtual void addViewInfo(int);  // slot 6
    virtual void delViewInfo(int);  // slot 7
    virtual void stockPntList(ml::DrLightObjPnt*);  // slot 8
    virtual void stockSptList(ml::DrLightObjSpt*);  // slot 9
    virtual void render(ml::DrShdLgtMan*, ml::DrLightMan*);  // slot 10
    virtual void debugRender();  // slot 11

    // allocates the work memory and sets up every view's buffers (the constructor's body)
    void createWork();
    void updateCluster();

    void setPntLightUniformBlock(unsigned int idx, unsigned int location);
    void setSptLightUniformBlock(unsigned int idx, unsigned int location);
    void setPointerListUniformBlock(unsigned int idx, unsigned int location);
    void setLightListUniformBlock(unsigned int idx, unsigned int location);
    void setParamUniformBlock(unsigned int idx, unsigned int location);
    void setPntLightStorageBuffer(unsigned int idx, unsigned int location);
    void setSptLightStorageBuffer(unsigned int idx, unsigned int location);
    void setPointerListStorageBuffer(unsigned int idx, unsigned int location);
    void setLightListStorageBuffer(unsigned int idx, unsigned int location);
    void setParamStorageBuffer(unsigned int idx, unsigned int location);

    // one view's light buffers (0x190 bytes; the set*UniformBlock/StorageBuffer members index it by view);
    // field names from those setters
    struct ViewWork {
        grlib::CGLibDblUniformBlock pntLight;     // 0x0
        grlib::CGLibDblUniformBlock sptLight;     // 0x38
        grlib::CGLibDblUniformBlock pointerList;  // 0x70
        grlib::CGLibDblUniformBlock lightList;    // 0xA8
        // 0xE0: 0x1D0 bytes (0x40 with the small grids); no setter binds it (the name is not the original's)
        grlib::CGLibDblUniformBlock extra;
        grlib::CGLibDblUniformBlock param;        // 0x118
        // the names below are not the original's
        int pntNum;          // 0x150, the point lights stockPntList stored this frame
        int sptNum;          // 0x154
        int listNum;         // 0x158, stockBegin clears it; stockEnd stops after updateCluster when it is 0
        float sliceNear;     // 0x15C, addViewInfo: 5.0, the first slice is at -sliceNear
        float sliceScale;    // 0x160, addViewInfo: 1.36, each slice depth is the previous one times it
        unsigned char pad_164[0x4];
        float* pSliceDepth;  // 0x168, gridZ + 1 depths in m_pWork
        unsigned char pad_170[0x20];
    };

    bool m_bSmallGrid;  // 0x18, the constructor's flag (the name is not the original's)
    unsigned char pad_19[0x7];
    ViewWork m_viewWork[4];  // 0x20, one per view (the constructor sets up four)
    // the names below are not the original's
    void* m_pWork = nullptr;  // 0x660, the destructor frees it
    int m_pntBuffRest = 0;  // 0x668, bytes left in the view's pntLight buffer (stockBegin, stockPntList)
    int m_sptBuffRest = 0;  // 0x66C
    float* m_pPntBuff = nullptr;  // 0x670, the next point light's entry in pntLight's buffer
    float* m_pSptBuff = nullptr;  // 0x678
    // 0x680: two gridX * gridY * gridZ * 8-byte tables in m_pWork (stockBegin clears both)
    unsigned long* m_pCellWork[2] = {};
    int m_cellLightNum = 0;  // 0x690, stockBegin clears it
    int m_cellLightMax = 0;  // 0x694, gridX * cellLightMax * gridY * gridZ of view 0's grid
    unsigned int* m_pCellLight = nullptr;  // 0x698, m_cellLightMax 16-byte entries in m_pWork
    DrResFetch m_fetch;  // 0x6A0, createWork sets it up with setLgtVertexParam (0x6B0, the size DrShdLgtHybrid's constructor allocates)
};
}  // namespace ml

#endif
