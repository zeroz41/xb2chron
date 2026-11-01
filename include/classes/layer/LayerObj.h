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
namespace layer { class LayerSortMan; }
namespace layer { class LayerSortObj; }
namespace layer { class LayerAnimeObj; class LayerResSecTexture; }
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
// a 2D affine matrix: the translation, then the 2x2 part (the field names and their order are inferred from
// mul, not the original's)
class LayerResMatrix {
public:
    // this = a then b (applyEnd: the object's matrix in its parent's)
    void mul(const LayerResMatrix& a, const LayerResMatrix& b) {
        m_xx = a.m_xx * b.m_xx + a.m_xy * b.m_yx;
        m_yx = a.m_yx * b.m_xx + a.m_yy * b.m_yx;
        m_transX = a.m_transX * b.m_xx + a.m_transY * b.m_yx + b.m_transX;
        m_xy = a.m_xx * b.m_xy + a.m_xy * b.m_yy;
        m_yy = a.m_yx * b.m_xy + a.m_yy * b.m_yy;
        m_transY = a.m_transX * b.m_xy + a.m_transY * b.m_yy + b.m_transY;
    }

    float m_transX;
    float m_transY;
    float m_xx;
    float m_yy;
    float m_xy;
    float m_yx;
};
// a multiplied and an added color (the field names are not the original's)
class LayerResColor {
public:
    // this = a's colors combined with b's (applyEnd: the object's in its parent's)
    void mul(const LayerResColor& a, const LayerResColor& b) {
        m_mulCol.r = a.m_mulCol.r * b.m_mulCol.r;
        m_mulCol.g = a.m_mulCol.g * b.m_mulCol.g;
        m_mulCol.b = a.m_mulCol.b * b.m_mulCol.b;
        m_mulCol.a = a.m_mulCol.a * b.m_mulCol.a;
        m_addCol.r = a.m_addCol.r + b.m_addCol.r;
        m_addCol.g = a.m_addCol.g + b.m_addCol.g;
        m_addCol.b = a.m_addCol.b + b.m_addCol.b;
    }

    mm::Col4 m_mulCol;
    mm::Col3 m_addCol;
};
class LayerBase;
// what an object's applyBegin/applyEnd pass down to its children (only the fields applyEnd reads and writes are
// known; the field names are not the original's)
class LayerResUpdateInfo {
public:
    unsigned char pad_0[0x40];
    const LayerResMatrix* m_matrix;  // 0x40: the parent's matrix
    const LayerResColor* m_color;  // 0x48: the parent's colors
    bool m_flag50;  // LayerObjTopLayout::applyEnd sets it for its children (the name is not the original's)
    unsigned char pad_51[0x7];
    unsigned int m_blendType;  // 0x58: LayerObjTopLayout::applyEnd passes its m_blendType down
    unsigned char pad_5C[0x14];
    const LayerBase* m_maskObj;  // 0x70: the mask object the children inherit
    unsigned char pad_78[0x10];  // LayerObjTopLayout::applyEnd's local copy is 0x88 bytes
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
    // sets the scale in all three m_params (inlined in setInitPosScl and LayerActBase::actcmd_scl, no symbol of its
    // own; the name is not the original's)
    void setInitScale(float x, float y) {
        m_params[1].m_scale[0] = x;
        m_params[0].m_scale[0] = x;
        m_params[2].m_scale[0] = x;
        m_params[1].m_scale[1] = y;
        m_params[0].m_scale[1] = y;
        m_params[2].m_scale[1] = y;
    }
    // setInitPos with the size too (LayerAccLayoutBinary::setLayoutObj passes a layout position's x, y, width, height)
    void setInitPosScl(float, float, float, float);
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
        // release: LayerObjManager::begin moves the object to its delete list (the name is not the original's)
        FLAG_RELEASE = 0x1,
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
        // set while the object's resource still needs resourceInit (LayerObjTopDef::resourceInit clears it)
        STATE_RESOURCE_INIT = 0x1,
        STATE_VIEWPORT = 0x10,
        // applyEnd: the object is skipped (its matrix and colors are not updated)
        STATE_NO_UPDATE = 0x10000,  // LayerAccLayoutObj::setViewPortMode
        STATE_PARTS_ACTION = 0x40,  // LayerAccAction reads the running action from m_actionData
        // LayerObjUtil::updatePosMatrixUniformBlock leaves the position unscaled by the LayerManager's screen
        // scale (LayerObjMesh::call_uniform_noImage passes it)
        STATE_RAW_POS = 0x800,
        // setDrawList: puts the object in the 3D sort space when its caller asks for it
        STATE_3D_SPACE = 0x400,
        // setDrawList: either bit keeps the object out of the sort lists
        STATE_NO_DRAW = 0x90000,
        // LayerObjTopDef::resourceInit sets it when its first texture has one of the formats 0x4D, 0x4F or 0x50
        STATE_TEX_FORMAT = 0x400000,
    };
    // what setPos/setRot/setScale/setMulCol/setAddCol write, one per m_flags entry and a third the getters fall
    // back to (the layout is not the original's)
    struct Param {
        // x, y: LayerActBase::actcmd_pos/scl interpolate them element by element
        float m_pos[2];
        float m_rot;
        float m_scale[2];
        unsigned char pad_14[0x8];
        LayerResColor m_color;  // setMulCol / setAddCol
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
    LayerResMatrix m_localMatrix;  // 0x1DC: applyEnd multiplies it by its parent's (the name is not the original's)
    float m_ctrlSpd;  // LayerActBase::actcmd_ctrlspd (the name is not the original's)
    unsigned char pad_1F8[0x4];
    // the z LayerObjUtil::updatePosMatrixUniformBlock writes into the position uniform (LayerObjMesh's
    // call_uniform_noImage; the name is not the original's)
    float m_posZ;
    float m_depth;  // setDrawList's set3DSpace distance (the name is not the original's)
    unsigned char pad_204[0x4];
    // what baseRelease deletes (the names are not the original's)
    LayerAnimeObj* m_animeObj[3];  // 0x208
    LayerResSecTexture* m_secTexture[3];  // 0x220
    grlib::CGLibDblUniformBlock* m_defUniform;  // 0x238
    const LayerBase* m_maskObj;  // setMaskObj
    // the mask object it draws with: m_maskObj, else its parent's (applyEnd; the name is not the original's)
    const LayerBase* m_curMaskObj;
};
inline void LayerObj::onFlag(unsigned int flag) { onFlag(LayerManager::s_nStkIdx, flag); }
inline void LayerObj::offFlag(unsigned int flag) { offFlag(LayerManager::s_nStkIdx, flag); }
inline const LayerObj::Param& LayerObj::getParam(unsigned int flag) const {
    if (isFlag(LayerManager::s_nStkIdx, flag)) return m_params[LayerManager::s_nStkIdx];
    return isFlag(LayerManager::s_nDebIdx, flag) ? m_params[LayerManager::s_nDebIdx] : m_params[2];
}
}  // namespace layer

#endif
