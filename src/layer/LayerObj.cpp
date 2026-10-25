#include "classes/layer/LayerObj.h"
#include "classes/layer/LayerActDef.h"
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

namespace layer {

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
void LayerObjFont::setColorMap(const LayerFontIconObj* colorMap, unsigned int pattern) {
    m_colorMap = colorMap;
    m_colorMapPattern = pattern;
}
void LayerObjFont::setSlopeRot(float rot) { m_slopeRot = rot; }
float LayerObjFont::getSlopeRot() const { return m_slopeRot; }
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
void LayerObjTopPolyObj::applyPartsSetup() { updateVertexBuffer(); }
void LayerObjTopMaskObj::resourceInit() {
    if (m_texture != nullptr) {
        m_texture->setupResource();
    }
}
void LayerObjSortDef::finalRender() { static_cast<LayerObjTopDef*>(m_obj)->finalRender(); }
void LayerObjSortFont::finalRender() { static_cast<LayerObjTopFont*>(m_obj)->finalRender(); }
void LayerObjSortTexObj::finalRender() { static_cast<LayerObjTopTexObj*>(m_obj)->finalRender(); }
void LayerObjSortPolyObj::finalRender() { static_cast<LayerObjTopPolyObj*>(m_obj)->finalRender(); }

}  // namespace layer

