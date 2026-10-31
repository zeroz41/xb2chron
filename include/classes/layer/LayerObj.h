#ifndef CLASSES_LAYER_LAYEROBJ_H
#define CLASSES_LAYER_LAYEROBJ_H

#include "layer/LayerBase.h"
#include "layer/LayerAccObjBase.h"
#include "mm/Col3.h"
#include "mm/Col4.h"
#include "mm/Mat44.h"
#include "classes/layer/LayerManager.h"
#include "layer/LayerSortMan.h"

namespace layer { class LayerRenderView; }
namespace layer { class LayerResColor; }
namespace layer { class LayerResMatrix; }
namespace layer { class LayerResUpdateInfo; }
namespace layer { class LayerSortMan; }
namespace layer { class LayerSortObj; }
namespace grlib { class CGLibDblUniformBlock; }
namespace grlib { class CGLibRenderTarget; }

namespace layer {
// a layer object's screen bounds: the TopTexObj/TopMemObj/TopPolyObj applyParams reset them to +-100000, then
// LayerObjUtil::calcDispInfo computes them (the field names are not the original's)
class LayerResDispInfo {
public:
    float m_minX;
    float m_minY;
    float m_maxX;
    float m_maxY;
};
// what LayerObjUtil::calcDispInfo reads the object's size from; only the fields LayerAccObjBase reads are known
class LayerResRenderInfo {
public:
    unsigned char pad_0[0x8];
    float m_width;  // calcScl_Correction_Up's size (the name is not the original's)
    float m_height;  // calcScl_Correction_Up's size (the name is not the original's)
    short m_pixelX;  // calcScl_Pixel_Up adds it to m_pixelWidth (the name is not the original's)
    short m_pixelY;  // calcScl_Pixel_Up adds it to m_pixelHeight (the name is not the original's)
    short m_pixelWidth;  // getPixelWidth (calcScl_Pixel_Up reads it signed)
    short m_pixelHeight;  // getPixelHeight
    unsigned char m_centerType;  // set/getCenterType (a LayerCenterType)
};
// table 0x7100B7F9E8
class LayerObj : public ::layer::LayerBase {
public:
    // inline: its deleting destructor sits in the unit's tail with the table's other inline slots
    virtual ~LayerObj() {}  // slot 0
    virtual void release();  // slot 2
    // the derived destructors' first step
    void baseRelease();
    virtual void resourceInit() {}  // slot 3
    virtual void apply(layer::LayerSortMan*, layer::LayerRenderView const*);  // slot 4
    virtual void applyBegin(layer::LayerResUpdateInfo&, layer::LayerRenderView const*);  // slot 5
    virtual void applyEnd(layer::LayerResUpdateInfo&, layer::LayerRenderView const*);  // slot 6
    virtual void setDrawList(layer::LayerSortMan*, bool) = 0;  // slot 7
    virtual void applyPartsSetup() {}  // slot 8
    virtual void applyParams(layer::LayerRenderView const*, layer::LayerResMatrix const&, layer::LayerResColor const&) {}  // slot 9

    void setPos(float x, float y);
    // sets the position in all three m_params
    void setInitPos(float x, float y);
    void setRot(float rot);
    void setScale(float x, float y);
    void setMulCol(const mm::Col4& col);
    void setAddCol(const mm::Col3& col);
    void setMatrix(const mm::Mat44& mtx);
    void getPos(float& x, float& y) const;
    void getRot(float& rot) const;
    void getScale(float& x, float& y) const;
    const mm::Col4& getMulCol() const;
    const mm::Mat44& getMatrix() const;
    void setDisp(bool disp);
    void setFlip(LayerFlipType type, bool flip);

    // The field names follow LayerAccObjBase's accessors that read and write them (not the original's).
    // the bits m_flags[LayerManager::s_nStkIdx] collects: what was set this frame (the names are not the original's)
    enum {
        FLAG_POS = 0x2,  // setPos
        FLAG_SCALE = 0x4,  // setScale
        FLAG_ROT = 0x8,  // setRot
        FLAG_MUL_COL = 0x20,  // setMulCol
        FLAG_ADD_COL = 0x40,  // setAddCol
        FLAG_DISP_ON = 0x80,  // setDisp(true)
        FLAG_DISP_OFF = 0x100,  // setDisp(false)
        FLAG_PRIORITY_TBL = 0x800,  // LayerAccLayoutObj::createPriorityTbl clears it
        FLAG_ACTION_RUNNING = 0x10000,  // LayerAccAction::isRunning
        FLAG_ACTION_END = 0x20000,  // LayerActBase::actionEnd
        FLAG_MATRIX = 0x40000,  // setMatrix
        FLAG_FLIP_ON = 0x80000,  // setFlip(type, true), shifted by the type
        FLAG_FLIP_OFF = 0x200000,  // setFlip(type, false), shifted by the type
    };
    // the bits of m_stateFlags (the names are not the original's)
    enum {
        STATE_VIEWPORT = 0x10,  // LayerAccLayoutObj::setViewPortMode
        STATE_PARTS_ACTION = 0x40,  // LayerAccAction reads the running action from m_actionData
        // LayerObjUtil::updatePosMatrixUniformBlock leaves the position unscaled by the LayerManager's screen
        // scale (LayerObjMesh::call_uniform_noImage passes it)
        STATE_RAW_POS = 0x800,
        // setDrawList: puts the object in the 3D sort space when its caller asks for it
        STATE_3D_SPACE = 0x400,
        // setDrawList: either bit keeps the object out of the sort lists
        STATE_NO_DRAW = 0x90000,
    };
    // what setPos/setRot/setScale/setMulCol/setAddCol write, one per m_flags entry and a third the getters fall
    // back to (the layout is not the original's)
    struct Param {
        float m_posX;
        float m_posY;
        float m_rot;
        float m_scaleX;
        float m_scaleY;
        unsigned char pad_14[0x8];
        mm::Col4 m_mulCol;
        mm::Col3 m_addCol;
    };

    // the entry the getters read for a value: this frame's when it set it, else the one being read back when that
    // set it, else the third (the name is not the original's)
    const Param& getParam(unsigned int flag) const;
    // an m_flags entry's bits (the index is unsigned: the original zero-extends it; the names are not the original's)
    bool isFlag(unsigned int index, unsigned int flag) const { return (m_flags[index] & flag) != 0; }
    void onFlag(unsigned int index, unsigned int flag) { m_flags[index] |= flag; }
    void offFlag(unsigned int index, unsigned int flag) { m_flags[index] &= ~flag; }
    // the LayerManager::s_nStkIdx entry's bits (setFlip computes the bits before it reads the index)
    void onFlag(unsigned int flag);
    void offFlag(unsigned int flag);
    // updates the object's default uniform block from its matrix and color (the TopTexObj/TopMemObj/TopPolyObj
    // applyParams)
    void updateDefUniformBlock(grlib::CGLibDblUniformBlock& uniform, const LayerResMatrix& matrix,
                               const LayerResColor& color, const grlib::CGLibRenderTarget* target);
    // setDrawList's 2D case: puts obj in sortMan's 2D space while the object is on screen (the name is not the
    // original's)
    void set2DSpace(LayerSortMan* sortMan, LayerSortObj* obj) const {
        if (m_dispInfo.m_minX <= 0.0f || m_dispInfo.m_minY <= 0.0f || m_dispInfo.m_maxX >= 1.0f || m_dispInfo.m_maxY >= 1.0f) {
            return;
        }
        sortMan->set2DSpace(obj, m_priority);
    }

    // The field names follow the accessors that read and write them (not the original's).
    unsigned char m_status;  // release sets 0x22 (the name is not the original's)
    unsigned char pad_1D[0x3];
    mm::Mat44 m_matrix[2];  // setMatrix writes the one m_matrixIdx does not name
    unsigned int m_flags[2];  // FLAG_*, indexed by LayerManager::s_nStkIdx / s_nDebIdx
    unsigned int m_stateFlags;  // STATE_*
    unsigned char pad_AC[0xC];
    const void* m_resData;  // getResData
    unsigned short m_priority;  // setPriority
    unsigned char m_matrixIdx;  // getMatrix
    unsigned char m_space;  // setSpace (a LAYER_SPACE_TYPE)
    unsigned char m_blendType;  // setBlendType (a LayerBlendType)
    unsigned char pad_C5[0x1];
    unsigned char m_texFilterType;  // setTexFilterType (a LayerTexFilterType)
    unsigned char pad_C7[0x1];
    Param m_params[3];
    // the screen bounds setDrawList tests: drawn only while [0] > 0, [1] > 0, [2] < 1 and [3] < 1 (the name is not
    // the original's)
    LayerResDispInfo m_dispInfo;
    LayerResRenderInfo m_renderInfo;  // 0x180
    unsigned char pad_19C[0x3C];  // the render info is 4-aligned (floats at 0x188)
    unsigned short m_runningActIdx[2];  // LayerAccAction::getRunningActIdx, indexed by LayerManager::s_nDebIdx
    unsigned char pad_1DC[0x18];
    float m_ctrlSpd;  // LayerActBase::actcmd_ctrlspd (the name is not the original's)
    unsigned char pad_1F8[0x4];
    // the z LayerObjUtil::updatePosMatrixUniformBlock writes into the position uniform (LayerObjMesh's
    // call_uniform_noImage; the name is not the original's)
    float m_posZ;
    float m_depth;  // setDrawList's set3DSpace distance (the name is not the original's)
    unsigned char pad_204[0x3C];
    const LayerBase* m_maskObj;  // setMaskObj
};
inline void LayerObj::onFlag(unsigned int flag) { onFlag(LayerManager::s_nStkIdx, flag); }
inline void LayerObj::offFlag(unsigned int flag) { offFlag(LayerManager::s_nStkIdx, flag); }
inline const LayerObj::Param& LayerObj::getParam(unsigned int flag) const {
    if (isFlag(LayerManager::s_nStkIdx, flag)) return m_params[LayerManager::s_nStkIdx];
    return isFlag(LayerManager::s_nDebIdx, flag) ? m_params[LayerManager::s_nDebIdx] : m_params[2];
}
}  // namespace layer

#endif
