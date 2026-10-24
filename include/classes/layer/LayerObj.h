#ifndef CLASSES_LAYER_LAYEROBJ_H
#define CLASSES_LAYER_LAYEROBJ_H

#include "layer/LayerBase.h"
#include "layer/LayerAccObjBase.h"
#include "mm/Col3.h"
#include "mm/Col4.h"
#include "mm/Mat44.h"
#include "classes/layer/LayerManager.h"

namespace layer { class LayerRenderView; }
namespace layer { class LayerResColor; }
namespace layer { class LayerResMatrix; }
namespace layer { class LayerResUpdateInfo; }
namespace layer { class LayerSortMan; }

namespace layer {
// table 0x7100B7F9E8
class LayerObj : public ::layer::LayerBase {
public:
    virtual ~LayerObj();  // slot 0
    virtual void release();  // slot 2
    virtual void resourceInit() {}  // slot 3
    virtual void apply(layer::LayerSortMan*, layer::LayerRenderView const*);  // slot 4
    virtual void applyBegin(layer::LayerResUpdateInfo&, layer::LayerRenderView const*);  // slot 5
    virtual void applyEnd(layer::LayerResUpdateInfo&, layer::LayerRenderView const*);  // slot 6
    virtual void setDrawList(layer::LayerSortMan*, bool) = 0;  // slot 7
    virtual void applyPartsSetup() {}  // slot 8
    virtual void applyParams(layer::LayerRenderView const*, layer::LayerResMatrix const&, layer::LayerResColor const&) {}  // slot 9

    void setPos(float x, float y);
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
        FLAG_MATRIX = 0x40000,  // setMatrix
        FLAG_FLIP_ON = 0x80000,  // setFlip(type, true), shifted by the type
        FLAG_FLIP_OFF = 0x200000,  // setFlip(type, false), shifted by the type
    };
    // the bits of m_stateFlags (the names are not the original's)
    enum {
        STATE_VIEWPORT = 0x10,  // LayerAccLayoutObj::setViewPortMode
        STATE_PARTS_ACTION = 0x40,  // LayerAccAction reads the running action from m_actionData
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

    // The field names follow the accessors that read and write them (not the original's).
    unsigned char pad_1C[0x4];
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
    unsigned char pad_170[0x24];
    unsigned short m_pixelWidth;  // getPixelWidth
    unsigned short m_pixelHeight;  // getPixelHeight
    unsigned char m_centerType;  // set/getCenterType (a LayerCenterType)
    unsigned char pad_199[0x3F];
    unsigned short m_runningActIdx[2];  // LayerAccAction::getRunningActIdx, indexed by LayerManager::s_nDebIdx
    unsigned char pad_1DC[0x64];
    const LayerBase* m_maskObj;  // setMaskObj
};
inline const LayerObj::Param& LayerObj::getParam(unsigned int flag) const {
    int index = LayerManager::s_nStkIdx;
    if (isFlag(index, flag)) {
        return m_params[index];
    }
    index = LayerManager::s_nDebIdx;
    return isFlag(index, flag) ? m_params[index] : m_params[2];
}
}  // namespace layer

#endif
