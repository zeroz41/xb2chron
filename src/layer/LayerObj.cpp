#include "classes/layer/LayerObj.h"
#include "classes/layer/LayerObjFont.h"
#include "layer/LayerObjUtil.h"
#include "classes/layer/LayerObjTopLayout.h"
#include "classes/layer/LayerObjTopTexObj.h"
#include "classes/layer/LayerObjTopMemObj.h"
#include "classes/layer/LayerObjTopPolyObj.h"
#include "layer/LayerRenderView.h"
#include "classes/layer/LayerObjTopFont.h"
#include "layer/LayerObjUtil.h"
#include "classes/layer/LayerObj.h"
#include "classes/layer/LayerActBase.h"
#include "classes/layer/LayerObjWork.h"
#include "classes/layer/LayerObjLayout.h"
#include "classes/layer/LayerObjManager.h"
#include "classes/layer/LayerObjTopDef.h"
#include "classes/layer/LayerObjTopMemObj.h"
#include "classes/layer/LayerObjTopTexObj.h"
#include "classes/layer/LayerObjTopPolyObj.h"
#include "classes/layer/LayerObjTopMaskObj.h"
#include "classes/layer/LayerObj.h"
#include "classes/layer/LayerActDef.h"
#include "classes/layer/LayerObjDraw.h"
#include "layer/LayerVertexObj.h"
#include "classes/layer/LayerObjMesh.h"
#include "classes/layer/LayerObjTopDef.h"
#include "layer/LayerObjUtil.h"
#include "classes/layer/LayerObjTopMaskObj.h"
#include "layer/LayerTextureObj.h"
#include "classes/layer/LayerObjTopPolyObj.h"
#include "classes/layer/LayerObj.h"
#include "classes/layer/LayerActBase.h"
#include "classes/layer/LayerActLayout.h"
#include "grlib/CGLibOneUniformBlock.h"
#include "layer/LayerPolyVertex.h"
#include "layer/LayerObjPlace.h"
#include "classes/layer/LayerObjTopPolyObj.h"
#include "classes/layer/LayerObjTopMemObj.h"
#include "classes/layer/LayerActLayout.h"
#include "layer/LayerAccManager.h"
#include "classes/layer/LayerShdManager.h"
#include "classes/layer/LayerManager.h"
#include "classes/layer/LayerObj.h"
#include "classes/layer/LayerActBase.h"
#include "classes/layer/LayerObjManager.h"
#include "classes/layer/LayerObjTopDef.h"
#include "classes/layer/LayerObjMesh.h"
#include "layer/LayerObjUtil.h"
#include "layer/LayerTextureObj.h"
#include "classes/layer/LayerObjTopMaskObj.h"
#include "classes/layer/LayerObjLayout.h"
#include "layer/LayerAccObjBase.h"
#include "layer/LayerAccFontObj.h"
#include "layer/LayerAccFontStyle.h"
#include "layer/LayerAccManager.h"
#include "layer/LayerAccPolyObj.h"
#include "layer/LayerAccMemObj.h"
#include "layer/LayerAccAction.h"
#include "layer/LayerAccDefTexture.h"
#include "layer/LayerAccDefObj.h"
#include "layer/LayerAccLayoutObj.h"
#include "classes/layer/LayerObj.h"
#include "classes/layer/LayerActBase.h"
#include "classes/layer/LayerObjWork.h"
#include "classes/layer/LayerObjTopMemObj.h"
#include "classes/layer/LayerObjTopPolyObj.h"
#include "classes/layer/LayerObjFont.h"
#include "classes/layer/LayerFontStyleObj.h"
#include "classes/layer/LayerFontIconObj.h"
#include "classes/layer/LayerFontResObj.h"
#include "classes/layer/LayerObjManager.h"
#include "classes/layer/LayerFontManager.h"
#include "classes/layer/LayerManager.h"
#include "classes/navi/NvmshAcObjBase.h"
#include "classes/layer/LayerSortObj.h"
#include "classes/layer/LayerObjTopDef.h"
#include "classes/layer/LayerObjTopFont.h"
#include "classes/layer/LayerObjTopTexObj.h"
#include "classes/layer/LayerObjSortDef.h"
#include "classes/layer/LayerObjSortFont.h"
#include "classes/layer/LayerObjSortTexObj.h"
#include "classes/layer/LayerObjSortPolyObj.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "classes/layer/LayerTagStr.h"
#include "layer/LayerSortMan.h"
#include "layer/LayerRenderView.h"
#include "classes/layer/LayerObjTopLayout.h"
#include "classes/layer/LayerObjSortLayout.h"

namespace layer {

void LayerObj::release() {
    onFlag(LayerManager::s_nStkIdx, 1);
    m_objType = 0;
    m_status = 0x22;
}
void LayerObj::setInitPos(float x, float y) {
    m_params[1].m_posX = x;
    m_params[0].m_posX = x;
    m_params[2].m_posX = x;
    m_params[1].m_posY = y;
    m_params[0].m_posY = y;
    m_params[2].m_posY = y;
}
void LayerObj::setPos(float x, float y) {
    int index = LayerManager::s_nStkIdx;
    m_params[index].m_posX = x;
    m_params[index].m_posY = y;
    onFlag(index, FLAG_POS);
}
void LayerObj::setRot(float rot) {
    int index = LayerManager::s_nStkIdx;
    m_params[index].m_rot = rot;
    onFlag(index, FLAG_ROT);
}
void LayerObj::setScale(float x, float y) {
    int index = LayerManager::s_nStkIdx;
    m_params[index].m_scaleX = x;
    m_params[index].m_scaleY = y;
    onFlag(index, FLAG_SCALE);
}
void LayerObj::setMulCol(const mm::Col4& col) {
    int index = LayerManager::s_nStkIdx;
    m_params[index].m_mulCol = col;
    onFlag(index, FLAG_MUL_COL);
}
void LayerObj::setAddCol(const mm::Col3& col) {
    int index = LayerManager::s_nStkIdx;
    m_params[index].m_addCol = col;
    onFlag(index, FLAG_ADD_COL);
}
void LayerObj::setMatrix(const mm::Mat44& mtx) {
    if (m_matrixIdx) {
        m_matrix[0] = mtx;
    } else {
        m_matrix[1] = mtx;
    }
    onFlag(LayerManager::s_nStkIdx, FLAG_MATRIX);
}
void LayerObj::getPos(float& x, float& y) const {
    const Param& param = getParam(FLAG_POS);
    x = param.m_posX;
    y = param.m_posY;
}
void LayerObj::getRot(float& rot) const { rot = getParam(FLAG_ROT).m_rot; }
void LayerObj::getScale(float& x, float& y) const {
    const Param& param = getParam(FLAG_SCALE);
    x = param.m_scaleX;
    y = param.m_scaleY;
}
void LayerObj::setDisp(bool disp) {
    if (disp) {
        onFlag(LayerManager::s_nStkIdx, FLAG_DISP_ON);
        offFlag(LayerManager::s_nStkIdx, FLAG_DISP_OFF);
    } else {
        offFlag(LayerManager::s_nStkIdx, FLAG_DISP_ON);
        onFlag(LayerManager::s_nStkIdx, FLAG_DISP_OFF);
    }
}
void LayerObj::setFlip(LayerFlipType type, bool flip) {
    if (flip) {
        onFlag(FLAG_FLIP_ON << type);
        offFlag(FLAG_FLIP_OFF << type);
    } else {
        onFlag(FLAG_FLIP_OFF << type);
        offFlag(FLAG_FLIP_ON << type);
    }
}
void LayerActBase::actionIdx(unsigned int index) {
    int stkIdx = LayerManager::s_nStkIdx;
    onFlag(stkIdx, FLAG_ACTION_RUNNING);
    m_runningActIdx[stkIdx] = index;
}
void LayerActBase::actionEnd() { onFlag(LayerManager::s_nStkIdx, FLAG_ACTION_END); }
bool LayerActBase::actcmd_no(const unsigned char*& cmd) {
    cmd += 4;
    return false;
}
bool LayerActBase::actcmd_priority(const unsigned char*& cmd) {
    m_priority = reinterpret_cast<const unsigned short*>(cmd)[1];
    cmd += 4;
    return false;
}
bool LayerActBase::actcmd_wait(const unsigned char*& cmd) {
    const unsigned char* wait = cmd;
    cmd += 8;
    if (reinterpret_cast<const float*>(wait)[1] <= m_actionData->m_runningSec) {
        return false;
    }
    return true;
}
bool LayerActBase::actcmd_ctrlspd(const unsigned char*& cmd) {
    m_ctrlSpd = reinterpret_cast<const float*>(cmd)[1];
    cmd += 8;
    return false;
}
bool LayerActBase::actend_no(const LyrActionData* data, bool cmdEnd) { return false; }
bool LayerActBase::actend_cmdend(const LyrActionData* data, bool cmdEnd) { return !cmdEnd; }
bool LayerActBase::actend_on(const LyrActionData* data, bool cmdEnd) { return true; }
bool LayerActDef::actcmd_iconnum(const unsigned char*& cmd) {
    m_iconNum = reinterpret_cast<const unsigned short*>(cmd)[1];
    cmd += 4;
    return false;
}
bool LayerActDef::actcmd_animicon(const unsigned char*& cmd) {
    const unsigned char* anim = cmd;
    const unsigned short* icons = reinterpret_cast<const unsigned short*>(anim + 0xC);
    bool wait;
    if (reinterpret_cast<const float*>(anim)[1] <= m_actionData->m_runningSec) {
        m_iconNum = icons[reinterpret_cast<const unsigned short*>(anim)[1] - 1];
        wait = false;
    } else {
        m_iconNum = icons[static_cast<unsigned int>(m_actionData->m_runningSec * reinterpret_cast<const float*>(anim)[2])];
        wait = true;
    }
    cmd = cmd + reinterpret_cast<const unsigned short*>(anim)[1] * 2 + 0xC;
    return wait;
}
bool LayerActLayout::actcmd_notcmd01(const unsigned char*& cmd) {
    cmd += 4;
    return false;
}
bool LayerActLayout::actcmd_notcmd03(const unsigned char*& cmd) {
    cmd += reinterpret_cast<const unsigned short*>(cmd)[1] * 2 + 0xC;
    return false;
}
bool LayerActLayout::actcmd_notcmd02(const unsigned char*& cmd) {
    cmd += 8;
    return false;
}
void LayerObjDraw::draw_call_onm_def(grlib::CGLibDblUniformBlock* block, const LyrDrawData* data) {
    LayerShdManager* shdManager = mm::mtl::PtrSingleton<LayerManager>::sys()->m_shdManager;
    shdManager->setupVertex(static_cast<LayerDefVertType>(0));
    shdManager->m_select.m_shaderType = 0;
    shdManager->setupShader(block);
    shdManager->renderQuadsIndex();
}
void LayerObjDraw::draw_call_onm_tex(grlib::CGLibDblUniformBlock* block, const LyrDrawData* data) {
    LayerShdManager* shdManager = mm::mtl::PtrSingleton<LayerManager>::sys()->m_shdManager;
    shdManager->setupVertex(static_cast<LayerDefVertType>(1));
    shdManager->m_select.m_shaderType = 1;
    shdManager->setupShader(block);
    unsigned char texNum = data->m_texNum;
    if (texNum != 0) {
        const TexRef* refs = m_texRefs->m_refs + data->m_texIdx;
        for (unsigned int i = 0; i != texNum; i++) {
            shdManager->setupTexture(*m_textures[refs[i].m_texIdx], static_cast<LayerSamplerType>(m_texFilterType), i);
        }
    }
    shdManager->renderQuadsIndex();
}
void LayerObjDraw::draw_call_res_def(grlib::CGLibDblUniformBlock* block, const LyrDrawData* data) {
    LayerShdManager* shdManager = mm::mtl::PtrSingleton<LayerManager>::sys()->m_shdManager;
    shdManager->setupVertex(m_vertexObj, data->m_vertexIdx);
    shdManager->m_select.m_shaderType = 0;
    shdManager->setupShader(block);
    m_vertexObj->render(data->m_renderIdx);
}
void LayerObjDraw::draw_call_res_tex(grlib::CGLibDblUniformBlock* block, const LyrDrawData* data) {
    LayerShdManager* shdManager = mm::mtl::PtrSingleton<LayerManager>::sys()->m_shdManager;
    shdManager->setupVertex(m_vertexObj, data->m_vertexIdx);
    shdManager->m_select.m_shaderType = 1;
    shdManager->setupShader(block);
    const TexRef* ref = m_texRefs->m_refs + data->m_texIdx;
    shdManager->setupTexture(*m_textures[ref->m_texIdx], static_cast<LayerSamplerType>(m_texFilterType), 0);
    m_vertexObj->render(data->m_renderIdx);
}
void LayerObjDraw::draw_call_icon(grlib::CGLibDblUniformBlock* block, const LyrDrawData* data) {
    LayerShdManager* shdManager = mm::mtl::PtrSingleton<LayerManager>::sys()->m_shdManager;
    shdManager->setupVertex(static_cast<LayerDefVertType>(2));
    shdManager->m_select.m_shaderType = 4;
    shdManager->setupShader(block);
    unsigned char texNum = data->m_texNum;
    if (texNum != 0) {
        const TexRef* refs = m_texRefs->m_refs + data->m_texIdx;
        for (unsigned int i = 0; i != texNum; i++) {
            shdManager->setupTexture(*m_textures[refs[i].m_texIdx], static_cast<LayerSamplerType>(m_texFilterType), i);
        }
    }
    shdManager->renderQuadsIndex();
}
void LayerObjFont::setColorMap(const LayerFontIconObj* colorMap, unsigned int pattern) {
    m_colorMap = colorMap;
    m_colorMapPattern = pattern;
}
void LayerObjFont::setBorderWeight(float weight) {
    int index = LayerManager::s_nStkIdx;
    m_borderWeight[index] = weight;
    m_borderWeightFlags |= 1 << index;
}
void LayerObjFont::setSlopeRot(float rot) { m_slopeRot = rot; }
float LayerObjFont::getSlopeRot() const { return m_slopeRot; }
void LayerObjManager::finalRender(const ml::IDrDrawWorkInfo* info) {
    m_drawInfo = info;
    m_sortMan->finalRender();
}
void LayerObjManager::end() {}
void LayerObjMesh::call_uniform_win_ga_X(LayerArgMdlRenInf& arg) { setUniformWinGaX(arg, false); }
void LayerObjMesh::call_uniform_win_ga_Y(LayerArgMdlRenInf& arg) { setUniformWinGaY(arg, false); }
void LayerObjMesh::call_uniform_noImage(LayerArgMdlRenInf& arg) {
    LayerObjUtil::updatePosMatrixUniformBlock(arg.m_buff, arg.m_matrix, *arg.m_viewMatrix, m_posZ,
                                              (m_stateFlags & STATE_RAW_POS) != 0);
    arg.m_buff += 8;
}
void LayerObjMesh::call_uniform_win_height(LayerArgMdlRenInf& arg) { setUniformWinHeight(arg, false); }
void LayerObjMesh::call_uniform_win_sclheight(LayerArgMdlRenInf& arg) { setUniformWinHeight(arg, true); }
void LayerObjMesh::call_uniform_win_sclga_X(LayerArgMdlRenInf& arg) { setUniformWinGaX(arg, true); }
void LayerObjMesh::call_uniform_win_sclga_Y(LayerArgMdlRenInf& arg) { setUniformWinGaY(arg, true); }
void LayerObjPlace::placeReset_Off(LayerResNode* node) {}
void LayerObjPlace::placeReset_Pos(LayerResNode* node) {
    node->m_posX = 0.0f;
    node->m_posY = 0.0f;
}
void LayerObjPlace::placeReset_Col(LayerResNode* node) {
    node->m_mulCol.r = 1.0f;
    node->m_mulCol.g = 1.0f;
    node->m_mulCol.b = 1.0f;
    node->m_mulCol.a = 1.0f;
    node->m_addCol.r = 0.0f;
    node->m_addCol.g = 0.0f;
    node->m_addCol.b = 0.0f;
}
void LayerObjPlace::placeReset_Pos_Col(LayerResNode* node) {
    placeReset_Col(node);
    placeReset_Pos(node);
}
void LayerObjPlace::placeFormat_u8(LayerResNode* node, int anim, const unsigned char* data, const unsigned char* frames, unsigned int frame) {
    s_resCallPlaceAnim[anim](node, data, frames[frame]);
}
void LayerObjPlace::placeFormat_u16(LayerResNode* node, int anim, const unsigned char* data, const unsigned char* frames, unsigned int frame) {
    s_resCallPlaceAnim[anim](node, data, reinterpret_cast<const unsigned short*>(frames)[frame]);
}
void LayerObjPlace::placeFormat_u32(LayerResNode* node, int anim, const unsigned char* data, const unsigned char* frames, unsigned int frame) {
    s_resCallPlaceAnim[anim](node, data, reinterpret_cast<const unsigned int*>(frames)[frame]);
}
void LayerObjPlace::placeAnm_Pos(LayerResNode* node, const unsigned char* data, unsigned int key) {
    const float* value = reinterpret_cast<const float*>(data) + key * 2;
    node->m_posX = value[0];
    node->m_posY = value[1];
}
void LayerObjPlace::placeAnm_Scl(LayerResNode* node, const unsigned char* data, unsigned int key) {
    const float* value = reinterpret_cast<const float*>(data) + key * 2;
    node->m_sclX = value[0];
    node->m_sclY = value[1];
}
void LayerObjPlace::placeAnm_Rot(LayerResNode* node, const unsigned char* data, unsigned int key) {
    const float* value = reinterpret_cast<const float*>(data) + key * 2;
    node->m_rotX = value[0];
    node->m_rotY = value[1];
}
void LayerObjPlace::placeAnm_Srt(LayerResNode* node, const unsigned char* data, unsigned int key) {
    const float* value = reinterpret_cast<const float*>(data) + key * 4;
    node->m_rotX = value[0];
    node->m_rotY = value[1];
    node->m_sclX = value[2];
    node->m_sclY = value[3];
}
void LayerObjPlace::placeAnm_AddCol(LayerResNode* node, const unsigned char* data, unsigned int key) {
    const unsigned char* value = data + key * 4;
    node->m_addCol.r = value[0] * (1.0f / 255.0f);
    node->m_addCol.g = value[1] * (1.0f / 255.0f);
    node->m_addCol.b = value[2] * (1.0f / 255.0f);
}
void LayerObjPlace::placeAnm_MulCol(LayerResNode* node, const unsigned char* data, unsigned int key) {
    const unsigned char* value = data + key * 4;
    node->m_mulCol.r = value[0] * (1.0f / 255.0f);
    node->m_mulCol.g = value[1] * (1.0f / 255.0f);
    node->m_mulCol.b = value[2] * (1.0f / 255.0f);
    node->m_mulCol.a = value[3] * (1.0f / 255.0f);
}
void LayerObjPlace::placeAnm_AllCol(LayerResNode* node, const unsigned char* data, unsigned int key) {
    const unsigned char* value = data + key * 8;
    node->m_mulCol.r = value[0] * (1.0f / 255.0f);
    node->m_mulCol.g = value[1] * (1.0f / 255.0f);
    node->m_mulCol.b = value[2] * (1.0f / 255.0f);
    node->m_mulCol.a = value[3] * (1.0f / 255.0f);
    node->m_addCol.r = value[4] * (1.0f / 255.0f);
    node->m_addCol.g = value[5] * (1.0f / 255.0f);
    node->m_addCol.b = value[6] * (1.0f / 255.0f);
}
void LayerObjPlace::placeAnm_Blend(LayerResNode* node, const unsigned char* data, unsigned int key) {
    node->m_blend = key;
    node->m_flags |= 0x2;
}
const unsigned short LayerObjUtil::UNIFORM_BLOCK_SIZE[12] = {
    0x80, 0x180, 0x80, 0x50, 0x60, 0x80, 0x60, 0x50, 0x80, 0x120, 0x40, 0x20,
};
int LayerObjUtil::getUniformBlockSizeAlOff(LayerUniType type) { return UNIFORM_BLOCK_SIZE[type]; }
void LayerObjTopDef::setDrawList(LayerSortMan* sortMan, bool use3D) {
    if (m_stateFlags & STATE_NO_DRAW) return;
    if (use3D) {
        if (m_stateFlags & STATE_3D_SPACE) {
            mm::mtl::PtrSingleton<LayerManager>::sys()->m_objManager->m_sortMan->set3DSpace(&m_sortObj, m_depth);
        } else {
            set2DSpace(sortMan, &m_sortObj);
        }
    } else {
        set2DSpace(sortMan, &m_sortObj);
    }
}
LayerObjTopFont::~LayerObjTopFont() {
    baseRelease();
    workRelease();
}
void LayerObjTopFont::applyParams(const LayerRenderView* view, const LayerResMatrix& matrix, const LayerResColor& color) {
    updateShaderParms(view, matrix, color);
}
void LayerObjUtil::getLayoutInfo(float* pos, const LyrLayoutPosData* data, LayerCenterType type, float sclX, float sclY) {
    s_CallDataPos[mm::mtl::PtrSingleton<LayerManager>::sys()->m_coordinate](pos, data, type, sclX, sclY);
}
void* LayerObjTopMemObj::getBuffer() {
    unsigned int index = LayerManager::s_nDebIdx;
    return m_buffers[index].m_pBuff;
}
void LayerObjTopMemObj::updateBufer() {
    unsigned int index = LayerManager::s_nDebIdx;
    unsigned long* clear = reinterpret_cast<unsigned long*>(m_clearBuffers[index].m_pBuff);
    clear[0] = 0;
    clear[1] = 0;
    m_clearBuffers[index].updateData();
    m_buffers[index].updateData();
}
void LayerObjTopMemObj::setRender(bool render) {
    if (render) {
        m_renderFlags |= RENDER_ON;
    } else {
        m_renderFlags &= ~RENDER_ON;
    }
}
void LayerObjTopMemObj::applyParams(const LayerRenderView* view, const LayerResMatrix& matrix, const LayerResColor& color) {
    m_viewData = view->m_viewData;
    m_dispInfo.m_minX = m_dispInfo.m_minY = -100000.0f;
    m_dispInfo.m_maxX = m_dispInfo.m_maxY = 100000.0f;
    LayerObjUtil::calcDispInfo(m_dispInfo, matrix, m_renderInfo);
    if (!(m_stateFlags & STATE_NO_DRAW)) updateDefUniformBlock(m_uniform, matrix, color, nullptr);
}
void LayerObjTopMemObj::setDrawList(LayerSortMan* sortMan, bool use3D) {
    if (m_stateFlags & STATE_NO_DRAW) return;
    if (use3D) {
        if (m_stateFlags & STATE_3D_SPACE) {
            mm::mtl::PtrSingleton<LayerManager>::sys()->m_objManager->m_sortMan->set3DSpace(&m_sortObj, m_depth);
        } else {
            set2DSpace(sortMan, &m_sortObj);
        }
    } else {
        set2DSpace(sortMan, &m_sortObj);
    }
}
LayerObjTopTexObj::~LayerObjTopTexObj() {
    baseRelease();
    m_uniform.release();
}
void LayerObjTopTexObj::applyParams(const LayerRenderView* view, const LayerResMatrix& matrix, const LayerResColor& color) {
    m_viewData = view->m_viewData;
    m_dispInfo.m_minX = m_dispInfo.m_minY = -100000.0f;
    m_dispInfo.m_maxX = m_dispInfo.m_maxY = 100000.0f;
    LayerObjUtil::calcDispInfo(m_dispInfo, matrix, m_renderInfo);
    if (!(m_stateFlags & STATE_NO_DRAW)) updateDefUniformBlock(m_uniform, matrix, color, nullptr);
}
void LayerObjTopTexObj::setDrawList(LayerSortMan* sortMan, bool use3D) {
    if (m_stateFlags & STATE_NO_DRAW) return;
    if (use3D) {
        if (m_stateFlags & STATE_3D_SPACE) {
            mm::mtl::PtrSingleton<LayerManager>::sys()->m_objManager->m_sortMan->set3DSpace(&m_sortObj, m_depth);
        } else {
            set2DSpace(sortMan, &m_sortObj);
        }
    } else {
        set2DSpace(sortMan, &m_sortObj);
    }
}
void LayerObjTopPolyObj::LockVertex() { m_locked = m_vertices[LayerManager::s_nStkIdx]; }
void LayerObjTopPolyObj::setVertex(unsigned int index, const LayerPolyVertex& vertex) {
    static_cast<LayerPolyVertex*>(m_locked)[index] = vertex;
}
void LayerObjTopPolyObj::UnlockVertex() {
    m_updateFlags |= UPDATE_VERTEX << LayerManager::s_nStkIdx;
    m_locked = nullptr;
}
void LayerObjTopPolyObj::LockIndex() { m_locked = m_indices[LayerManager::s_nStkIdx]; }
void LayerObjTopPolyObj::setIndex(unsigned int index, unsigned short value) {
    static_cast<unsigned short*>(m_locked)[index] = value;
}
void LayerObjTopPolyObj::UnlockIndex() {
    m_updateFlags |= UPDATE_INDEX << LayerManager::s_nStkIdx;
    m_locked = nullptr;
}
void LayerObjTopPolyObj::setIndexInfo(unsigned short start, unsigned short count) {
    int index = LayerManager::s_nStkIdx;
    m_updateFlags |= UPDATE_INDEX_INFO << index;
    m_indexStart[index] = start;
    m_indexCount[index] = count;
}
void LayerObjTopPolyObj::applyParams(const LayerRenderView* view, const LayerResMatrix& matrix, const LayerResColor& color) {
    m_viewData = view->m_viewData;
    m_dispInfo.m_minX = m_dispInfo.m_minY = -100000.0f;
    m_dispInfo.m_maxX = m_dispInfo.m_maxY = 100000.0f;
    LayerObjUtil::calcDispInfo(m_dispInfo, matrix, m_renderInfo);
    if (!(m_stateFlags & STATE_NO_DRAW)) updateDefUniformBlock(m_uniform, matrix, color, nullptr);
}
void LayerObjTopPolyObj::setDrawList(LayerSortMan* sortMan, bool use3D) {
    if (m_stateFlags & STATE_NO_DRAW) return;
    if (use3D) {
        if (m_stateFlags & STATE_3D_SPACE) {
            mm::mtl::PtrSingleton<LayerManager>::sys()->m_objManager->m_sortMan->set3DSpace(&m_sortObj, m_depth);
        } else {
            set2DSpace(sortMan, &m_sortObj);
        }
    } else {
        set2DSpace(sortMan, &m_sortObj);
    }
}
void LayerObjTopPolyObj::applyPartsSetup() { updateVertexBuffer(); }
void LayerObjTopMaskObj::resourceInit() {
    if (m_texture != nullptr) {
        m_texture->setupResource();
    }
}
LayerObjTopMaskObj::~LayerObjTopMaskObj() {
    baseRelease();
    m_uniform.release();
    if (m_texture != nullptr) {
        m_texture->release();
        m_texture = nullptr;
    }
}
void LayerObjSortDef::finalRender() { static_cast<LayerObjTopDef*>(m_obj)->finalRender(); }
void LayerObjSortFont::finalRender() { static_cast<LayerObjTopFont*>(m_obj)->finalRender(); }
void LayerObjSortTexObj::finalRender() { static_cast<LayerObjTopTexObj*>(m_obj)->finalRender(); }
void LayerObjSortPolyObj::finalRender() { static_cast<LayerObjTopPolyObj*>(m_obj)->finalRender(); }
void LayerObjSortLayout::finalRender() {
    LayerObjTopLayout* obj = static_cast<LayerObjTopLayout*>(m_obj);
    if (obj->m_sortMan) obj->m_sortMan->finalRender();
    if ((obj->m_renderFlags & LayerObjTopLayout::RENDER_TEX_OBJ) != LayerObjTopLayout::RENDER_TEX_OBJ) return;
    LayerShdManager* shdManager = mm::mtl::PtrSingleton<LayerManager>::sys()->m_shdManager;
    shdManager->setShaderMaskOff();
    shdManager->setupMainRenderTarget();
    shdManager->resetViewPort();
    if (!(obj->m_texObj->m_stateFlags & LayerObj::STATE_NO_DRAW)) obj->m_texObj->finalRender();
}
void LayerObjSortMemObj::finalRender() {
    LayerObjTopMemObj* obj = static_cast<LayerObjTopMemObj*>(m_obj);
    obj->setupRender();
    if (obj->m_renderFlags & LayerObjTopMemObj::RENDER_ON) obj->lastRender();
}
void LayerObjUtil::calcMdlPos_Center_Up(float* pos, float* out, const float* size, const LayerBasePos& base) {
    out[0] = base.m_alignX * size[0];
    out[1] = base.m_alignY * size[1];
}
void LayerObjUtil::calcMdlPos_Center_Down(float* pos, float* out, const float* size, const LayerBasePos& base) {
    out[0] = base.m_alignX * size[0];
    out[1] = (base.m_alignY + 1.0f) * size[1];
    pos[1] -= size[1];
}
void LayerObjUtil::calcMdlPos_Center_Center(float* pos, float* out, const float* size, const LayerBasePos& base) {
    out[0] = (base.m_alignX + 0.5f) * size[0];
    out[1] = (base.m_alignY + 0.5f) * size[1];
    pos[0] -= size[0] * 0.5f;
    pos[1] -= size[1] * 0.5f;
}
void LayerObjUtil::calcPos_Pixel_Up(float* pos, const LayerBasePos& base) {
    pos[0] = base.m_posX * mm::mtl::PtrSingleton<LayerManager>::sys()->getScreenCalcPosWidth();
    pos[1] = base.m_posY * mm::mtl::PtrSingleton<LayerManager>::sys()->getScreenCalcPosHeight();
}
void LayerObjUtil::calcPos_Correction_Up(float* pos, const LayerBasePos& base) {
    pos[0] = base.m_posX * mm::mtl::PtrSingleton<LayerManager>::sys()->getScreenCalcPosWidth();
    pos[1] = base.m_posY * mm::mtl::PtrSingleton<LayerManager>::sys()->getScreenCalcPosHeight();
}
void LayerObjUtil::calcScl_Pixel_Up(float* out, const LayerBasePos& base, const LayerResRenderInfo& info) {
    float pixelWidth = info.m_pixelWidth + info.m_pixelX;
    float width = mm::mtl::PtrSingleton<LayerManager>::sys()->getScreenCalcSclWidth() * pixelWidth;
    float pixelHeight = info.m_pixelHeight + info.m_pixelY;
    float height = mm::mtl::PtrSingleton<LayerManager>::sys()->getScreenCalcSclHeight() * pixelHeight;
    out[0] = width * base.m_sclX;
    out[1] = height * base.m_sclY;
}
void LayerObjUtil::calcScl_Correction_Up(float* out, const LayerBasePos& base, const LayerResRenderInfo& info) {
    float width = info.m_width * mm::mtl::PtrSingleton<LayerManager>::sys()->getScreenCalcSclWidth();
    float height = info.m_height * mm::mtl::PtrSingleton<LayerManager>::sys()->getScreenCalcSclHeight();
    out[0] = width * base.m_sclX;
    out[1] = height * base.m_sclY;
}
void LayerObjUtil::calcSwfScl_Pixel_Up(float* out, const LayerBasePos& base, const LayerResRenderInfo& info) {
    float pixelWidth = info.m_pixelWidth + info.m_pixelX;
    float pixelHeight = info.m_pixelHeight + info.m_pixelY;
    float size = pixelWidth > pixelHeight ? pixelWidth : pixelHeight;
    float width = mm::mtl::PtrSingleton<LayerManager>::sys()->getScreenCalcSclWidth() * size;
    float height = mm::mtl::PtrSingleton<LayerManager>::sys()->getScreenCalcSclHeight() * size;
    out[0] = base.m_sclX * width;
    out[1] = height * base.m_sclY;
}
void LayerObjUtil::calcSwfScl_Correction_Up(float* out, const LayerBasePos& base, const LayerResRenderInfo& info) {
    float size = info.m_width > info.m_height ? info.m_width : info.m_height;
    float width = size * mm::mtl::PtrSingleton<LayerManager>::sys()->getScreenCalcSclWidth();
    float height = size * mm::mtl::PtrSingleton<LayerManager>::sys()->getScreenCalcSclHeight();
    out[0] = width * base.m_sclX;
    out[1] = height * base.m_sclY;
}
void LayerObjUtil::calcPosData_Pixel_Up(float* pos, const LyrLayoutPosData* data, LayerCenterType type, float sclX, float sclY) {
    pos[2] = (data->m_right - data->m_left) / sclX;
    pos[3] = (data->m_bottom - data->m_top) / sclY;
    pos[0] = data->m_left;
    pos[1] = data->m_top;
    switch (type) {
    case 1:
        pos[1] += data->m_bottom;
        break;
    case 2:
        pos[0] += (data->m_right - data->m_left) * 0.5f;
        pos[1] += (data->m_bottom - data->m_top) * 0.5f;
        break;
    }
}
void LayerObjUtil::calcPosData_Correction_Up(float* pos, const LyrLayoutPosData* data, LayerCenterType type, float sclX, float sclY) {
    pos[0] = data->m_posX;
    pos[1] = data->m_posY;
    pos[2] = data->m_width;
    pos[3] = data->m_height;
    switch (type) {
    case 1:
        pos[1] += data->m_height * mm::mtl::PtrSingleton<LayerManager>::sys()->getScreenCalcPosHeight();
        break;
    case 2:
        pos[0] += data->m_width * 0.5f * mm::mtl::PtrSingleton<LayerManager>::sys()->getScreenCalcPosWidth();
        pos[1] += data->m_height * 0.5f * mm::mtl::PtrSingleton<LayerManager>::sys()->getScreenCalcPosHeight();
        break;
    }
}
void (*LayerObjUtil::s_CallScl[2])(float*, const LayerBasePos&, const LayerResRenderInfo&) = {
    LayerObjUtil::calcScl_Pixel_Up, LayerObjUtil::calcScl_Correction_Up};
void (*LayerObjUtil::s_CallPos[2])(float*, const LayerBasePos&) = {LayerObjUtil::calcPos_Pixel_Up,
                                                                   LayerObjUtil::calcPos_Correction_Up};
void (*LayerObjUtil::s_CallMdl[3])(float*, float*, const float*, const LayerBasePos&) = {
    LayerObjUtil::calcMdlPos_Center_Up, LayerObjUtil::calcMdlPos_Center_Down, LayerObjUtil::calcMdlPos_Center_Center};
void (*LayerObjUtil::s_CallSwfScl[2])(float*, const LayerBasePos&, const LayerResRenderInfo&) = {
    LayerObjUtil::calcSwfScl_Pixel_Up, LayerObjUtil::calcSwfScl_Correction_Up};
void (*LayerObjUtil::s_CallDataPos[2])(float*, const LyrLayoutPosData*, LayerCenterType, float, float) = {
    LayerObjUtil::calcPosData_Pixel_Up, LayerObjUtil::calcPosData_Correction_Up};

}  // namespace layer

