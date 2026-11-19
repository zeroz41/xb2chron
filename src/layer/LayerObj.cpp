#include "math.h"
#include "stdio.h"
#include "classes/layer/LayerObj.h"
#include "classes/layer/LayerObjFont.h"
#include "layer/LayerObjUtil.h"
#include "layer/LayerAccLayoutBinary.h"
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
#include "classes/ml/IDrDrawWorkInfo.h"
#include "layer/LayerAnimeObj.h"
#include "layer/LayerResSecTexture.h"
#include "classes/layer/LayerObjTopDef.h"
#include "classes/layer/LayerObjTopMemObj.h"
#include "classes/layer/LayerObjTopTexObj.h"
#include "classes/layer/LayerObjTopPolyObj.h"
#include "classes/layer/LayerObjTopMaskObj.h"
#include "classes/layer/LayerObj.h"
#include "classes/layer/LayerActDef.h"
#include "classes/layer/LayerObjDraw.h"
#include "layer/LayerVertexObj.h"
#include "layer/LayerVertexMan.h"
#include "grlib/CGLibTextureBuffer.h"
#include "layer/LayerResViewPortInfo.h"
#include "layer/LayerViewPort.h"
#include "classes/layer/LayerObjMesh.h"
#include "classes/layer/LayerObjTopDef.h"
#include "grlib/CGLibUniformArray.h"
#include "grlib/CGLibDblUniformBlock.h"
#include "grlib/CGLibVtxOneInstans.h"
#include "grlib/CGLibVtxInstans.h"
#include "layer/LayerObjUtil.h"
#include "classes/layer/LayerObjTopMaskObj.h"
#include "layer/LayerTextureObj.h"
#include "classes/layer/LayerObjTopPolyObj.h"
#include "classes/layer/LayerObj.h"
#include "classes/layer/LayerActBase.h"
#include "classes/layer/LayerActLayout.h"
#include "grlib/CGLibOneUniformBlock.h"
#include "layer/LayerPolyVertex.h"
#include "grlib/CGLibVtxVertex.h"
#include "grlib/CGLibVtxIndex.h"
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
#include "layer/LayerAccFormat.h"
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
#include "grlib/CGLibCtl.h"
#include "grlib/CGLibDecShader.h"

namespace layer {

void LayerObj::baseRelease() {
    if (m_defUniform != nullptr) {
        delete m_defUniform;
        m_defUniform = nullptr;
    }
    for (int i = 0; i < 3; i++) {
        if (m_animeObj[i] != nullptr) {
            delete m_animeObj[i];
            m_animeObj[i] = nullptr;
        }
    }
    for (int i = 0; i < 3; i++) {
        if (m_secTexture[i] != nullptr) {
            delete m_secTexture[i];
            m_secTexture[i] = nullptr;
        }
    }
}
void LayerObj::release() {
    onFlag(LayerManager::s_nStkIdx, FLAG_RELEASE);
    m_objType = 0;
    m_status = 0x22;
}
void LayerObj::setInitPos(float x, float y) {
    m_params[1].m_pos[0] = x;
    m_params[0].m_pos[0] = x;
    m_params[2].m_pos[0] = x;
    m_params[1].m_pos[1] = y;
    m_params[0].m_pos[1] = y;
    m_params[2].m_pos[1] = y;
}
void LayerObj::setInitPosScl(float x, float y, float width, float height) {
    if (m_objType == 2) {
        setInitPos(x, y);
        return;
    }
    if (m_stateFlags & 0x2) {
        if (mm::mtl::PtrSingleton<LayerManager>::sys()->m_coordinate != 0) {
            setInitPos(x + width, y);
        } else {
            setInitPos(x + static_cast<unsigned short>(m_renderInfo.m_pixelWidth) * width, y);
        }
        setInitScale(height, height);
    } else {
        setInitPos(x, y);
        if (mm::mtl::PtrSingleton<LayerManager>::sys()->m_coordinate != 0) {
            setInitScale(width / m_renderInfo.m_width, height / m_renderInfo.m_height);
        } else {
            setInitScale(width, height);
        }
    }
}
void LayerObj::updateDefSpace(grlib::CGLibDblUniformBlock*& uniform, LAYER_SPACE_TYPE space, const mm::Mat44& mtx) {
    switch (space) {
    case 2:
        LayerObjUtil::calcMatrixToZBuffPos(m_depth, m_posZ, mtx);
        m_stateFlags &= ~0x1000;
        m_stateFlags |= STATE_3D_SPACE | STATE_RAW_POS;
        LayerObjUtil::createWorldMatrixUniform(uniform, mtx, m_priority * 0.0625f);
        return;
    case 1:
        LayerObjUtil::calcMatrixToZBuffPos(m_depth, m_posZ, mtx);
        m_stateFlags |= STATE_3D_SPACE;
        break;
    default:
        m_posZ = 0.0f;
        break;
    }
    if (m_stateFlags & 0x1000) {
        m_stateFlags &= ~0x1000;
        if (uniform != nullptr) {
            delete uniform;
            uniform = nullptr;
        }
    } else if (uniform != nullptr) {
        m_stateFlags |= 0x1000;
    }
}
void LayerObj::applyEnd(LayerResUpdateInfo& info, const LayerRenderView* view) {
    if (m_stateFlags & STATE_NO_UPDATE) return;
    LayerResMatrix matrix;
    matrix.mul(m_localMatrix, *info.m_matrix);
    LayerResColor color;
    color.mul(m_params[2].m_color, *info.m_color);
    applyParams(view, matrix, color);
    if (m_maskObj != nullptr) {
        m_curMaskObj = m_maskObj;
    } else {
        m_curMaskObj = info.m_maskObj;
    }
}
void LayerObj::setPos(float x, float y) {
    int index = LayerManager::s_nStkIdx;
    m_params[index].m_pos[0] = x;
    m_params[index].m_pos[1] = y;
    onFlag(index, FLAG_POS);
}
void LayerObj::setRot(float rot) {
    int index = LayerManager::s_nStkIdx;
    m_params[index].m_rot = rot;
    onFlag(index, FLAG_ROT);
}
void LayerObj::setScale(float x, float y) {
    int index = LayerManager::s_nStkIdx;
    m_params[index].m_scale[0] = x;
    m_params[index].m_scale[1] = y;
    onFlag(index, FLAG_SCALE);
}
void LayerObj::setMulCol(const mm::Col4& col) {
    int index = LayerManager::s_nStkIdx;
    m_params[index].m_color.m_mulCol = col;
    onFlag(index, FLAG_MUL_COL);
}
void LayerObj::setAddCol(const mm::Col3& col) {
    int index = LayerManager::s_nStkIdx;
    m_params[index].m_color.m_addCol = col;
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
    const LayerResParmInfo& param = getParam(FLAG_POS);
    x = param.m_pos[0];
    y = param.m_pos[1];
}
void LayerObj::getRot(float& rot) const { rot = getParam(FLAG_ROT).m_rot; }
void LayerObj::getScale(float& x, float& y) const {
    const LayerResParmInfo& param = getParam(FLAG_SCALE);
    x = param.m_scale[0];
    y = param.m_scale[1];
}
const mm::Col4& LayerObj::getMulCol() const {
    if (isFlag(LayerManager::s_nStkIdx, FLAG_MUL_COL)) {
        return m_params[LayerManager::s_nStkIdx].m_color.m_mulCol;
    }
    if (isFlag(LayerManager::s_nDebIdx, FLAG_MUL_COL)) {
        return m_params[LayerManager::s_nDebIdx].m_color.m_mulCol;
    }
    return m_params[2].m_color.m_mulCol;
}
const mm::Mat44& LayerObj::getMatrix() const {
    if (isFlag(LayerManager::s_nStkIdx, FLAG_MATRIX)) {
        if (m_matrixIdx) return m_matrix[0];
        return m_matrix[1];
    }
    if (m_matrixIdx) return m_matrix[1];
    return m_matrix[0];
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
bool (LayerActBase::*LayerActBase::s_pCallActEnd[3])(const LyrActionData* data, bool cmdEnd) = {
    &LayerActBase::actend_no,
    &LayerActBase::actend_cmdend,
    &LayerActBase::actend_on,
};
bool (LayerActDef::*LayerActDef::s_pCallActCmd[14])(const unsigned char*& cmd) = {
    &LayerActBase::actcmd_no,     &LayerActDef::actcmd_iconnum,   &LayerActDef::actcmd_animicon,
    &LayerActBase::actcmd_pos,    &LayerActBase::actcmd_rot,      &LayerActBase::actcmd_scl,
    &LayerActBase::actcmd_numrot, &LayerActBase::actcmd_mulcol,   &LayerActBase::actcmd_addcol,
    &LayerActBase::actcmd_priority, &LayerActBase::actcmd_wait,   &LayerActDef::actcmd_animfrm,
    &LayerActDef::actcmd_animdef, &LayerActBase::actcmd_ctrlspd,
};
bool (LayerActLayout::*LayerActLayout::s_pCallActCmd[14])(const unsigned char*& cmd) = {
    &LayerActBase::actcmd_no,       &LayerActLayout::actcmd_notcmd01, &LayerActLayout::actcmd_notcmd03,
    &LayerActBase::actcmd_pos,      &LayerActBase::actcmd_rot,        &LayerActBase::actcmd_scl,
    &LayerActBase::actcmd_mulcol,   &LayerActBase::actcmd_addcol,     &LayerActBase::actcmd_priority,
    &LayerActBase::actcmd_wait,     &LayerActLayout::actcmd_notcmd02, &LayerActLayout::actcmd_notcmd01,
    &LayerActBase::actcmd_ctrlspd,
};
void LayerActBase::setupAction(unsigned char* work, const unsigned char* data) {
    const ActionHeader* header = reinterpret_cast<const ActionHeader*>(data);
    m_actionData = reinterpret_cast<ActionWork*>(work);
    m_actionData->m_data = data;
    m_actionData->m_cmdWork = reinterpret_cast<int*>(work + sizeof(ActionWork));
    m_actionData->m_actionMax = header->m_actionNum;
    m_actionData->m_actions = reinterpret_cast<const LyrActionData*>(data + header->m_actionOfs);
    m_actionData->m_runningSec = 0.0f;
    m_actionData->m_runningIdx = 0;
    m_actionData->m_flags = 0;
    if (header->m_cmdWorkNum != 0) {
        memset(m_actionData->m_cmdWork, 0, header->m_cmdWorkNum * sizeof(int));
    }
    if (header->m_flags & ActionHeader::FLAG_AUTO_START) {
        startAction();
        m_actionData->m_runningIdx = header->m_startIdx;
        m_actionData->m_flags |= ActionWork::FLAG_CMD_START;
        m_actionData->m_runningSec = 0.0f;
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
bool LayerActBase::actcmd_pos(const unsigned char*& cmd) {
    const ActionWork* data = m_actionData;
    bool wait = true;
    if (data->m_stepSec != 0.0f) {
        const float* arg = reinterpret_cast<const float*>(cmd);
        float pos[2];
        if (arg[3] <= data->m_runningSec) {
            for (int i = 0; i < 2; i++) pos[i] = arg[1 + i];
            wait = false;
        } else {
            float rate = 1.0f / ((arg[3] - data->m_runningSec) * data->m_stepRate);
            rate = 1.0f < rate ? 1.0f : rate;
            for (int i = 0; i < 2; i++) pos[i] = m_params[2].m_pos[i] + (arg[1 + i] - m_params[2].m_pos[i]) * rate;
        }
        setInitPos(pos[0], pos[1]);
    }
    cmd += 16;
    return wait;
}
bool LayerActBase::actcmd_rot(const unsigned char*& cmd) {
    const ActionWork* data = m_actionData;
    bool wait = true;
    if (data->m_stepSec != 0.0f) {
        const float* arg = reinterpret_cast<const float*>(cmd);
        const float* target = arg + 1;
        float rot;
        if (arg[2] <= data->m_runningSec) {
            rot = *target;
            wait = false;
        } else {
            float rate = 1.0f / ((arg[2] - data->m_runningSec) * data->m_stepRate);
            rate = 1.0f < rate ? 1.0f : rate;
            rot = m_params[2].m_rot + (*target - m_params[2].m_rot) * rate;
        }
        m_params[1].m_rot = rot;
        m_params[0].m_rot = rot;
        m_params[2].m_rot = rot;
    }
    cmd += 12;
    return wait;
}
bool LayerActBase::actcmd_scl(const unsigned char*& cmd) {
    const ActionWork* data = m_actionData;
    bool wait = true;
    if (data->m_stepSec != 0.0f) {
        const float* arg = reinterpret_cast<const float*>(cmd);
        float scl[2];
        if (arg[3] <= data->m_runningSec) {
            for (int i = 0; i < 2; i++) scl[i] = arg[1 + i];
            wait = false;
        } else {
            float rate = 1.0f / ((arg[3] - data->m_runningSec) * data->m_stepRate);
            rate = 1.0f < rate ? 1.0f : rate;
            for (int i = 0; i < 2; i++) scl[i] = m_params[2].m_scale[i] + (arg[1 + i] - m_params[2].m_scale[i]) * rate;
        }
        setInitScale(scl[0], scl[1]);
    }
    cmd += 16;
    return wait;
}
bool LayerActBase::actcmd_numrot(const unsigned char*& cmd) {
    const ActionWork* data = m_actionData;
    bool wait = true;
    if (data->m_stepSec != 0.0f) {
        const float* arg = reinterpret_cast<const float*>(cmd);
        wait = !(arg[2] <= data->m_runningSec);
        float rot = fmodf(m_params[2].m_rot + data->m_stepSec * arg[1], 6.2831855f);
        m_params[1].m_rot = rot;
        m_params[0].m_rot = rot;
        m_params[2].m_rot = rot;
    }
    cmd += 12;
    return wait;
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
void LayerActDef::updatePartsAction(const LyrActionData* action) {
    const unsigned char* cmd = m_actionData->m_data + action->m_cmdOfs;
    int i = 0;
    bool wait = false;
    for (; i < action->m_cmdNum; i++) {
        wait |= (this->*s_pCallActCmd[*reinterpret_cast<const unsigned short*>(cmd)])(cmd);
    }
    ActionWork* work = m_actionData;
    if (work->m_stepSec != 0.0f) {
        const LyrActionData* running = work->m_actions + work->m_runningIdx;
        if ((this->*s_pCallActEnd[running->m_endType])(running, wait)) {
            if (running->m_flags & LyrActionData::FLAG_LOOP) {
                m_actionData->m_runningSec = 0.0f;
                m_actionData->m_runningIdx = running->m_nextIdx;
            } else {
                m_stateFlags &= ~STATE_PARTS_ACTION;
            }
        }
    }
}
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
bool LayerActDef::actcmd_animfrm(const unsigned char*& cmd) {
    if (m_actionData->m_flags & ActionWork::FLAG_CMD_START) {
        const unsigned short* anim = reinterpret_cast<const unsigned short*>(cmd);
        m_texRefs->m_frameStart = anim[2];
        m_texRefs->m_frameEnd = anim[3];
        m_frames->m_frame = m_texRefs->m_frameStart;
    }
    m_frames->m_frame = m_texRefs->m_frameStart + m_actionData->m_runningSec * m_texRefs->m_anim->m_frameRate;
    cmd += 8;
    return !(m_texRefs->m_frameEnd <= m_frames->m_frame);
}
bool LayerActDef::actcmd_animdef(const unsigned char*& cmd) {
    int num = static_cast<const ResData*>(m_resData)->m_frameNum;
    for (int i = 0; i < num; i++) {
        m_frames[i].m_frame = 0.0f;
        m_frames[i].m_frameIdx = 0;
    }
    m_texRefs->m_frameEnd = m_texRefs->m_anim->m_frameNum;
    m_texRefs->m_frameStart = 0.0f;
    m_frameTime = 0.0f;
    cmd += 4;
    return false;
}
void LayerActLayout::updatePartsAction(const LyrActionData* action) {
    const unsigned char* cmd = m_actionData->m_data + action->m_cmdOfs;
    int i = 0;
    bool wait = false;
    for (; i < action->m_cmdNum; i++) {
        wait |= (this->*s_pCallActCmd[*reinterpret_cast<const unsigned short*>(cmd)])(cmd);
    }
    ActionWork* work = m_actionData;
    if (work->m_stepSec != 0.0f) {
        const LyrActionData* running = work->m_actions + work->m_runningIdx;
        if ((this->*s_pCallActEnd[running->m_endType])(running, wait)) {
            if (running->m_flags & LyrActionData::FLAG_LOOP) {
                m_actionData->m_runningSec = 0.0f;
                m_actionData->m_runningIdx = running->m_nextIdx;
            } else {
                m_stateFlags &= ~STATE_PARTS_ACTION;
            }
        }
    }
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
void LayerObjDraw::draw_call_win_def(grlib::CGLibDblUniformBlock* block, const LyrDrawData* data) {
    // lbl_71009B7AB8 (a 16-byte literal); the name is not the original's
    static const LayerSamplerType s_samplerTbl[] = {static_cast<LayerSamplerType>(3), static_cast<LayerSamplerType>(7),
                                                    static_cast<LayerSamplerType>(8), static_cast<LayerSamplerType>(1)};
    LayerShdManager* shdManager = mm::mtl::PtrSingleton<LayerManager>::sys()->m_shdManager;
    shdManager->setupVertex(m_vertexObj, data->m_vertexIdx);
    shdManager->m_select.m_shaderType = 3;
    shdManager->setupShader(block);
    LayerSamplerType sampler = data->m_samplerSel != 0 ? s_samplerTbl[data->m_samplerSel - 1]
                                                       : static_cast<LayerSamplerType>(m_texFilterType);
    unsigned int texNum = data->m_texNum;
    const TexRef* ref = &m_texRefs->m_refs[data->m_texIdx];
    for (unsigned int i = 0; i < texNum; i++, ref++) {
        shdManager->setupTexture(*m_textures[ref->m_texIdx], sampler, i);
    }
    m_vertexObj->render(data->m_renderIdx);
}
void LayerObjDraw::draw_call_win_tex(grlib::CGLibDblUniformBlock* block, const LyrDrawData* data) {
    // lbl_71009B7AB8 (a 16-byte literal); the name is not the original's
    static const LayerSamplerType s_samplerTbl[] = {static_cast<LayerSamplerType>(3), static_cast<LayerSamplerType>(7),
                                                    static_cast<LayerSamplerType>(8), static_cast<LayerSamplerType>(1)};
    LayerShdManager* shdManager = mm::mtl::PtrSingleton<LayerManager>::sys()->m_shdManager;
    shdManager->setupVertex(m_vertexObj, data->m_vertexIdx);
    shdManager->m_select.m_shaderType = 3;
    shdManager->setupShader(block);
    LayerSamplerType sampler = data->m_samplerSel != 0 ? s_samplerTbl[data->m_samplerSel - 1]
                                                       : static_cast<LayerSamplerType>(m_texFilterType);
    unsigned int texNum = data->m_texNum;
    const TexRef* ref = &m_texRefs->m_refs[data->m_texIdx];
    for (unsigned int i = 0; i < texNum; i++, ref++) {
        shdManager->setupTexture(*m_textures[ref->m_texIdx], sampler, i);
    }
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
void LayerObjDraw::draw_call_number(grlib::CGLibDblUniformBlock* block, const LyrDrawData* data) {
    LayerShdManager* shdManager = mm::mtl::PtrSingleton<LayerManager>::sys()->m_shdManager;
    shdManager->setupVertex(static_cast<LayerDefVertType>(2));
    shdManager->m_select.m_shaderType = 5;
    shdManager->setupShader(block);
    shdManager->setupInstaceVertex(*m_texRefs->m_number->m_instans, 0x24, 0);
    unsigned char texNum = data->m_texNum;
    if (texNum != 0) {
        const TexRef* refs = m_texRefs->m_refs + data->m_texIdx;
        for (unsigned int i = 0; i != texNum; i++) {
            shdManager->setupTexture(*m_textures[refs[i].m_texIdx], static_cast<LayerSamplerType>(m_texFilterType), i);
        }
    }
    shdManager->renderInstaceQuadsIndex(m_texRefs->m_number->m_num);
}
void LayerObjDraw::draw_call_hdr(grlib::CGLibDblUniformBlock* block, const LyrDrawData* data) {
    LayerShdManager* shdManager = mm::mtl::PtrSingleton<LayerManager>::sys()->m_shdManager;
    shdManager->setupVertex(static_cast<LayerDefVertType>(1));
    shdManager->m_select.m_shaderType = 10;
    shdManager->setupShader(block);
    const TexRef* ref = m_texRefs->m_refs + data->m_texIdx;
    shdManager->setupTexture(*m_textures[ref->m_texIdx], static_cast<LayerSamplerType>(m_texFilterType), 0);
    shdManager->setupTexture(shdManager->m_lut, static_cast<LayerSamplerType>(m_texFilterType), 1);
    shdManager->renderQuadsIndex();
}
// frees a text work and its in-place buffers (inline in workRelease, setMsg and applyPartsSetup; the name is not
// the original's)
static inline void releaseFontWork(LayerFontDrawBuffer::Work*& work) {
    if (work != nullptr) {
        work->m_instans->~CGLibVtxOneInstans();
        work->m_uniform->~CGLibDblUniformBlock();
        if (work != nullptr) {
            mtl::MemManager::deallocate(work, 0, false);
            work = nullptr;
        }
    }
}
void LayerObjFont::workRelease() {
    releaseFontWork(m_work);
    releaseFontWork(m_newWork[0]);
    releaseFontWork(m_newWork[1]);
    releaseFontWork(m_oldWork);
}
void LayerObjFont::setMsg(const unsigned char* text, const LayerFontResObj* font, const LayerFontStyleObj* style,
                          const LayerFontIconObj* icon, unsigned int styleIndex) {
    releaseFontWork(m_newWork[LayerManager::s_nStkIdx]);
    m_font = font;
    m_style = style;
    m_styleIndex = styleIndex;
    m_icon = icon;
    LayerFontDrawBuffer buffer(font, style, style->getStyleData(styleIndex), m_icon, m_dispSetting, this);
    buffer.m_horizontal = m_horizontal;
    buffer.m_vertical = m_vertical;
    m_newWork[LayerManager::s_nStkIdx] = buffer.createChar(text);
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
float LayerObjFont::getBorderWeight() const {
    if (m_borderWeightFlags & (1 << LayerManager::s_nStkIdx)) {
        return m_borderWeight[LayerManager::s_nStkIdx];
    }
    if (m_borderWeightFlags & (1 << LayerManager::s_nDebIdx)) {
        return m_borderWeight[LayerManager::s_nDebIdx];
    }
    return m_borderWeightDef;
}
void LayerObjFont::setSlopeRot(float rot) { m_slopeRot = rot; }
float LayerObjFont::getSlopeRot() const { return m_slopeRot; }
LayerBase* LayerObjManager::createStaticTexObj(const grlib::CGLibTextureBuffer& texture) {
    return new (mm::mtl::PtrSingleton<LayerManager>::sys()->m_workHandle, nullptr, 0, 4, false) LayerObjTopTexObj(&texture);
}
ml::CriticalSection& LayerObjManager::getCriticalSection() {
    static ml::CriticalSection s_cs;  // lbl_71015E9CC8, guard lbl_71015E9CF0; the name is not the original's
    return s_cs;
}
LayerObjManager::~LayerObjManager() {
    m_objList.deleteAll();
    m_setupList[0].deleteAll();
    m_setupList[1].deleteAll();
    m_deleteList.deleteAll();
    if (m_sortMan != nullptr) {
        delete m_sortMan;
        m_sortMan = nullptr;
    }
}
LayerBase* LayerObjManager::createObj(const void* resource) {
    ml::CS cs(getCriticalSection());
    LayerBase* obj = createStaticObj(resource);
    m_setupList[LayerManager::s_nStkIdx].addListNotNull(obj);
    return obj;
}
LayerBase* LayerObjManager::createMaskObj(const void* resource) {
    ml::CS cs(getCriticalSection());
    LayerBase* obj = createStaticMaskObj(resource);
    m_setupList[LayerManager::s_nStkIdx].addListNotNull(obj);
    return obj;
}
LayerBase* LayerObjManager::createStaticMaskObj(const void* resource) {
    const LyrFormatHeader* header = static_cast<const LyrFormatHeader*>(resource);
    if (header->m_magic == 'DHAL' && header->m_version == 10001) {
        return new (mm::mtl::PtrSingleton<LayerManager>::sys()->m_workHandle, nullptr, 0, 4, false) LayerObjTopMaskObj(resource);
    }
    return nullptr;
}
LayerBase* LayerObjManager::createLayoutObj() {
    ml::CS cs(getCriticalSection());
    LayerBase* obj = createStaticLayoutObj();
    m_setupList[LayerManager::s_nStkIdx].addListNotNull(obj);
    return obj;
}
LayerBase* LayerObjManager::createStaticLayoutObj() {
    return new (mm::mtl::PtrSingleton<LayerManager>::sys()->m_workHandle, nullptr, 0, 4, false) LayerObjTopLayout();
}
LayerBase* LayerObjManager::createStaticFontObj() { return new (mm::mtl::PtrSingleton<LayerManager>::sys()->m_workHandle, nullptr, 0, 4, false) LayerObjTopFont(); }
LayerBase* LayerObjManager::createTexObj(const grlib::CGLibTextureBuffer& texture) {
    ml::CS cs(getCriticalSection());
    LayerBase* obj = createStaticTexObj(texture);
    m_setupList[LayerManager::s_nStkIdx].addListNotNull(obj);
    return obj;
}
LayerBase* LayerObjManager::createMemObj(unsigned int width, unsigned int height, LayerMemType type) {
    ml::CS cs(getCriticalSection());
    LayerBase* obj = createStaticMemObj(width, height, type);
    m_setupList[LayerManager::s_nStkIdx].addListNotNull(obj);
    return obj;
}
LayerBase* LayerObjManager::createStaticMemObj(unsigned int width, unsigned int height, LayerMemType type) {
    return new (mm::mtl::PtrSingleton<LayerManager>::sys()->m_workHandle, nullptr, 0, 4, false) LayerObjTopMemObj(width, height, type);
}
LayerBase* LayerObjManager::createPolyObj(unsigned int width, unsigned int height, unsigned short vertexCount,
                                          unsigned short indexCount, LayerPrimitiveType type) {
    ml::CS cs(getCriticalSection());
    LayerBase* obj = createStaticPolyObj(width, height, vertexCount, indexCount, type);
    m_setupList[LayerManager::s_nStkIdx].addListNotNull(obj);
    return obj;
}
LayerBase* LayerObjManager::createStaticPolyObj(unsigned int width, unsigned int height, unsigned short vertexCount,
                                                unsigned short indexCount, LayerPrimitiveType type) {
    return new (mm::mtl::PtrSingleton<LayerManager>::sys()->m_workHandle, nullptr, 0, 4, false) LayerObjTopPolyObj(width, height, vertexCount, indexCount, type);
}
void LayerObjManager::begin() {
    m_deleteList.deleteAll();
    for (LayerBase* obj = m_setupList[LayerManager::s_nDebIdx].m_head; obj != nullptr;) {
        LayerBase* next = obj->m_next;
        m_setupList[LayerManager::s_nDebIdx].removeList(obj);
        static_cast<LayerObj*>(obj)->resourceInit();
        m_objList.addListNotNull(obj);
        obj = next;
    }
    m_setupList[LayerManager::s_nDebIdx].m_num = 0;
    m_setupList[LayerManager::s_nDebIdx].m_head = nullptr;
    m_setupList[LayerManager::s_nDebIdx].m_tail = nullptr;
    for (LayerBase* obj = m_objList.m_head; obj != nullptr;) {
        LayerBase* next = obj->m_next;
        if (static_cast<LayerObj*>(obj)->isFlag(LayerManager::s_nDebIdx, LayerObj::FLAG_RELEASE)) {
            m_objList.removeList(obj);
            m_deleteList.addListNotNull(obj);
        }
        obj = next;
    }
}
void LayerObjManager::apply(const ml::IDrDrawWorkInfo* info) {
    m_drawInfo = info;
    m_view.m_mode = 0;
    m_view.m_viewData = nullptr;
    m_sortMan->begin(info->m_eyePos);
    for (LayerBase* obj = m_objList.m_head; obj != nullptr;) {
        LayerBase* next = obj->m_next;
        static_cast<LayerObj*>(obj)->apply(m_sortMan, &m_view);
        obj = next;
    }
    m_sortMan->end();
}
void LayerObjManager::finalRender(const ml::IDrDrawWorkInfo* info) {
    m_drawInfo = info;
    m_sortMan->finalRender();
}
void LayerObjManager::end() {}
void LayerObjMesh::updateMeshUniformBlock(LayerArgMdlRenInf& arg) {
    if ((arg.m_node->m_flags & 1) != 0) {
        *arg.m_dispFlags &= ~1u;
        return;
    }
    *arg.m_dispFlags |= 1;
    arg.m_buff = reinterpret_cast<float*>(arg.m_uniformBlock->getBuff());
    (this->*s_pCallUniform[arg.m_meshInfo[3]])(arg);
    float* buff = arg.m_buff;
    float r = arg.m_node->m_color.m_mulCol.r * arg.m_color->m_mulCol.r;
    buff[0] = r;
    float g = arg.m_node->m_color.m_mulCol.g * arg.m_color->m_mulCol.g;
    buff[1] = g;
    float b = arg.m_node->m_color.m_mulCol.b * arg.m_color->m_mulCol.b;
    buff[2] = b;
    float a = arg.m_node->m_color.m_mulCol.a * arg.m_color->m_mulCol.a;
    buff[3] = a;
    buff[4] = arg.m_node->m_color.m_addCol.r + arg.m_color->m_addCol.r;
    buff[5] = arg.m_node->m_color.m_addCol.g + arg.m_color->m_addCol.g;
    buff[6] = arg.m_node->m_color.m_addCol.b + arg.m_color->m_addCol.b;
    buff[7] = 0.0f;
    arg.m_buff += 8;
    if ((arg.m_meshInfo[0] & 0x20) != 0) {
        if (m_gauge != 0) {
            float* gauge = arg.m_buff;
            for (int i = 0; i < 8; i++) {
                gauge[i] = 0.0f;
            }
            switch (m_gauge) {
            case 1:
                gauge[0] = m_param;
                gauge[2] = -1.0f;
                gauge[4] = 1.0f;
                break;
            case 2:
                gauge[1] = m_param;
                gauge[3] = -1.0f;
                gauge[5] = 1.0f;
                break;
            case 3:
                gauge[0] = m_param;
                gauge[2] = 1.0f;
                break;
            case 4:
                gauge[1] = m_param;
                gauge[3] = 1.0f;
                break;
            }
        }
        arg.m_buff += 8;
    }
    arg.m_uniformBlock->updateData();
}
void LayerObjMesh::call_uniform_win_ga_X(LayerArgMdlRenInf& arg) { setUniformWinGaX(arg, false); }
void LayerObjMesh::call_uniform_win_ga_Y(LayerArgMdlRenInf& arg) { setUniformWinGaY(arg, false); }
void LayerObjMesh::call_uniform_icon(LayerArgMdlRenInf& arg) {
    LayerObjUtil::updatePosMatrixUniformBlock(arg.m_buff, &arg.m_node->m_matrix, *arg.m_viewMatrix, m_posZ,
                                              (m_stateFlags & STATE_RAW_POS) != 0);
    arg.m_buff += 8;
    if (m_iconNum >= m_iconMax) m_iconNum = m_iconMax - 1;
    const ResData* res = static_cast<const ResData*>(m_resData);
    const IconData* icons = reinterpret_cast<const IconData*>(reinterpret_cast<const unsigned char*>(res) + res->m_iconOfs);
    const IconInfo* info =
        reinterpret_cast<const IconInfo*>(reinterpret_cast<const unsigned char*>(icons) + icons->m_infoOfs) + m_iconNum;
    float* buff = arg.m_buff;
    buff[0] = info->m_pos[0];
    buff[1] = info->m_pos[1];
    buff[2] = 0.0f;
    buff[3] = 0.0f;
    buff[4] = info->m_uv[0];
    buff[5] = info->m_uv[1];
    buff[6] = info->m_uv[2];
    buff[7] = info->m_uv[3];
    arg.m_buff += 8;
}
void LayerObjMesh::call_uniform_number(LayerArgMdlRenInf& arg) {
    LayerObjUtil::updatePosMatrixUniformBlock(arg.m_buff, &arg.m_node->m_matrix, *arg.m_viewMatrix, m_posZ,
                                              (m_stateFlags & STATE_RAW_POS) != 0);
    arg.m_buff += 8;
    m_texRefs->m_number->m_num = 0;
    const ResData* res = static_cast<const ResData*>(m_resData);
    const IconData* icons = reinterpret_cast<const IconData*>(reinterpret_cast<const unsigned char*>(res) + res->m_iconOfs);
    const IconInfo* infos =
        reinterpret_cast<const IconInfo*>(reinterpret_cast<const unsigned char*>(icons) + icons->m_infoOfs);
    char str[32];
    snprintf(str, sizeof(str), "%.2f", m_param);
    m_texRefs->m_number->m_instans->beginInstansBuff();
    NumberInstance* inst = static_cast<NumberInstance*>(m_texRefs->m_number->m_instans->getNextInstansBuff());
    float width = 0.0f;
    int size = 0;
    for (int i = 0; i < 32; i++) {
        int idx;
        if (str[i] == '.') {
            idx = 11;
        } else if (str[i] >= '0' && str[i] <= '9') {
            idx = str[i] - '0';
        } else {
            break;
        }
        const IconInfo* info = &infos[idx];
        NumberInstance* p = &inst[i];
        float w = info->m_pos[0];
        p->m_size[0] = w;
        p->m_size[1] = info->m_pos[1];
        p->m_pos[0] = i * info->m_pos[0];
        p->m_pos[1] = 0.0f;
        p->m_uv[0] = info->m_uv[0];
        p->m_uv[1] = info->m_uv[1];
        p->m_uv[2] = info->m_uv[2];
        p->m_uv[3] = info->m_uv[3];
        p->m_color = 0xFFFFFFFF;
        width += w;
        m_texRefs->m_number->m_num++;
        size += sizeof(NumberInstance);
    }
    NumberInstance* p = inst;
    for (unsigned int i = 0; i < m_texRefs->m_number->m_num; i++) {
        p->m_pos[0] -= width;
        p++;
    }
    m_texRefs->m_number->m_instans->m_offset += size;
    m_texRefs->m_number->m_instans->updateInstansBuff();
}
void LayerObjMesh::call_uniform_noImage(LayerArgMdlRenInf& arg) {
    LayerObjUtil::updatePosMatrixUniformBlock(arg.m_buff, &arg.m_node->m_matrix, *arg.m_viewMatrix, m_posZ,
                                              (m_stateFlags & STATE_RAW_POS) != 0);
    arg.m_buff += 8;
}
void LayerObjMesh::call_uniform_win_height(LayerArgMdlRenInf& arg) { setUniformWinHeight(arg, false); }
void LayerObjMesh::call_uniform_win_sclheight(LayerArgMdlRenInf& arg) { setUniformWinHeight(arg, true); }
void LayerObjMesh::call_uniform_win_sclga_X(LayerArgMdlRenInf& arg) { setUniformWinGaX(arg, true); }
void LayerObjMesh::call_uniform_win_sclga_Y(LayerArgMdlRenInf& arg) { setUniformWinGaY(arg, true); }
void LayerObjPlace::placeReset_Off(LayerResNode* node) {}
void LayerObjPlace::placeReset_Pos(LayerResNode* node) {
    node->m_pos.x = 0.0f;
    node->m_pos.y = 0.0f;
}
void LayerObjPlace::placeReset_Srt(LayerResNode* node) {
    node->m_rot = LayerResNode::Pair(0.0f, 0.0f);
    node->m_scl.x = node->m_scl.y = 1.0f;
}
void LayerObjPlace::placeReset_Pos_Srt(LayerResNode* node) {
    node->m_pos = LayerResNode::Pair(0.0f, 0.0f);
    node->m_scl = LayerResNode::Pair(1.0f, 1.0f);
    node->m_rot = LayerResNode::Pair(0.0f, 0.0f);
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
void LayerObjPlace::placeReset_Srt_Col(LayerResNode* node) {
    placeReset_Col(node);
    placeReset_Srt(node);
}
void LayerObjPlace::placeReset_Pos_Srt_Col(LayerResNode* node) {
    placeReset_Col(node);
    placeReset_Pos_Srt(node);
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
    node->m_pos.x = value[0];
    node->m_pos.y = value[1];
}
void LayerObjPlace::placeAnm_Scl(LayerResNode* node, const unsigned char* data, unsigned int key) {
    const float* value = reinterpret_cast<const float*>(data) + key * 2;
    node->m_scl.x = value[0];
    node->m_scl.y = value[1];
}
void LayerObjPlace::placeAnm_Rot(LayerResNode* node, const unsigned char* data, unsigned int key) {
    const float* value = reinterpret_cast<const float*>(data) + key * 2;
    node->m_rot.x = value[0];
    node->m_rot.y = value[1];
}
void LayerObjPlace::placeAnm_Srt(LayerResNode* node, const unsigned char* data, unsigned int key) {
    const float* value = reinterpret_cast<const float*>(data) + key * 4;
    node->m_rot.x = value[0];
    node->m_rot.y = value[1];
    node->m_scl.x = value[2];
    node->m_scl.y = value[3];
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
LayerObjTopDef::~LayerObjTopDef() {
    if (m_work != nullptr) {
        m_texRefs->m_uniforms->release();
    }
    baseRelease();
    m_resTex.clear();
    if (m_vertexObj != nullptr) {
        m_vertexObj->release();
        m_vertexObj = nullptr;
    }
    if (m_textureObj != nullptr) {
        m_textureObj->release();
        m_textureObj = nullptr;
    }
    if (m_work != nullptr) {
        mtl::MemManager::deallocate(m_work, 0, false);
        m_work = nullptr;
    }
}
void LayerObjTopDef::resourceInit() {
    if (!(m_stateFlags & STATE_RESOURCE_INIT)) return;
    const ResData* res = static_cast<const ResData*>(m_resData);
    if (res->m_vertexOfs != 0) {
        m_vertexObj = mm::mtl::PtrSingleton<LayerManager>::sys()->m_shdManager->m_vertexMan->createVertexObj(
            reinterpret_cast<const unsigned char*>(res) + res->m_vertexOfs);
    }
    if (m_textureObj != nullptr) {
        m_textureObj->setupResource();
        if (m_textureObj->m_texNum != 0) {
            switch (static_cast<int>(m_textureObj->getTexture(0)->getFormat())) {
            case 0x4D:
            case 0x4F:
            case 0x50:
                m_stateFlags |= STATE_TEX_FORMAT;
                break;
            }
        }
    }
    m_stateFlags &= ~STATE_RESOURCE_INIT;
}
void LayerObjTopDef::updateFast() {
    if (m_resTex.updateTexutre(m_textures, m_textureObj)) {
        m_stateFlags &= ~STATE_TEX_FORMAT;
        switch (static_cast<int>(m_textures[0]->getFormat())) {
        case 0x4D:
        case 0x4F:
        case 0x50:
            m_stateFlags |= STATE_TEX_FORMAT;
            break;
        }
    }
    if (isFlag(LayerManager::s_nDebIdx, FLAG_ANIME_PAUSE_ON | FLAG_ANIME_PAUSE_OFF | FLAG_HIDE_ON | FLAG_HIDE_OFF)) {
        if (isFlag(LayerManager::s_nDebIdx, FLAG_ANIME_PAUSE_ON)) {
            m_stateFlags |= STATE_ANIME_PAUSE;
        } else if (isFlag(LayerManager::s_nDebIdx, FLAG_ANIME_PAUSE_OFF)) {
            m_stateFlags &= ~STATE_ANIME_PAUSE;
        }
        if (isFlag(LayerManager::s_nDebIdx, FLAG_HIDE_ON)) {
            m_stateFlags |= STATE_HIDE;
        } else if (isFlag(LayerManager::s_nDebIdx, FLAG_HIDE_OFF)) {
            m_stateFlags &= ~STATE_HIDE;
        }
    }
    m_frameCtrlSpd = m_ctrlSpd;
    updateAction();
    updateDefPos();
    if (m_animeObj[2] != nullptr) {
        float frame = m_frameCtrlSpd * mm::mtl::PtrSingleton<LayerManager>::sys()->m_frameRate.y;
        if (m_animeObj[2]->update(m_params[2], (m_stateFlags & STATE_ANIME_PAUSE) ? 0.0f : frame)) {
            if (m_animeObj[2] != nullptr) {
                delete m_animeObj[2];
                m_animeObj[2] = nullptr;
            }
        }
    }
    if (m_params[2].m_color.m_mulCol.a <= 0.0f && m_objType != 7) {
        m_stateFlags |= STATE_ALPHA_ZERO;
    }
}
void LayerObjTopDef::updateParams(LayerArgMdlRenInf& arg, const LayerRenderView* view) {
    m_texRefs->m_viewData = view->m_viewData;
    m_dispInfo.m_minX = m_dispInfo.m_minY = -100000.0f;
    m_dispInfo.m_maxX = m_dispInfo.m_maxY = 100000.0f;
    LayerObjUtil::calcDispInfo(m_dispInfo, *arg.m_viewMatrix, m_renderInfo);
    if (m_stateFlags & STATE_NO_DRAW) return;
    arg.m_dispFlags = m_texRefs->m_dispFlags;
    const TexRefList::Draw* draw = m_texRefs->m_draws;
    for (int i = 0; i < m_texRefs->m_drawNum; i++, draw++) {
        unsigned int index = i;
        arg.m_node = &m_texRefs->m_nodes[draw->m_nodeIdx];
        arg.m_meshInfo = m_texRefs->m_meshInfos[draw->m_meshIdx].m_data;
        arg.m_uniformBlock = &m_texRefs->m_uniforms->m_pArray[index];
        updateMeshUniformBlock(arg);
        arg.m_dispFlags++;
    }
    if (m_secTexture[2] != nullptr) {
        m_secTexture[2]->update();
    }
}
void LayerObjTopDef::applyEnd(LayerResUpdateInfo& info, const LayerRenderView* view) {
    if (m_stateFlags & STATE_NO_UPDATE) return;
    LayerResMatrix matrix;
    matrix.mul(m_localMatrix, *info.m_matrix);
    LayerResColor color;
    color.mul(m_params[2].m_color, *info.m_color);
    LayerArgMdlRenInf arg;
    arg.m_viewMatrix = &matrix;
    arg.m_color = &color;
    updateParams(arg, view);
    if (m_maskObj != nullptr) {
        m_curMaskObj = m_maskObj;
    } else {
        m_curMaskObj = info.m_maskObj;
    }
}
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
void LayerObjTopFont::applyPartsSetup() {
    releaseFontWork(m_oldWork);
    if (m_newWork[LayerManager::s_nDebIdx] != nullptr) {
        m_oldWork = m_work;
        m_work = m_newWork[LayerManager::s_nDebIdx];
        m_newWork[LayerManager::s_nDebIdx] = nullptr;
    }
    if (m_borderWeightFlags & (1 << LayerManager::s_nDebIdx)) {
        m_borderWeightDef = m_borderWeight[LayerManager::s_nDebIdx];
        m_borderWeightFlags &= ~(1 << LayerManager::s_nDebIdx);
    }
}
void LayerObjTopFont::setDrawList(LayerSortMan* sortMan, bool use3D) {
    if (m_stateFlags & STATE_NO_DRAW) return;
    if (m_work == nullptr) return;
    if (use3D) {
        if (m_stateFlags & STATE_3D_SPACE) {
            mm::mtl::PtrSingleton<LayerManager>::sys()->m_objManager->m_sortMan->set3DSpace(m_work->m_sortObj, m_depth);
        } else {
            set2DSpace(sortMan, m_work->m_sortObj);
        }
    } else {
        set2DSpace(sortMan, m_work->m_sortObj);
    }
}
void LayerObjTopFont::applyParams(const LayerRenderView* view, const LayerResMatrix& matrix, const LayerResColor& color) {
    updateShaderParms(view, matrix, color);
}
void LayerObjTopFont::finalRender() {
    LayerShdManager* shdManager = mm::mtl::PtrSingleton<LayerManager>::sys()->m_shdManager;
    const LayerObjTopMaskObj* maskObj = static_cast<const LayerObjTopMaskObj*>(m_curMaskObj);
    if (maskObj != nullptr && !(maskObj->m_stateFlags & STATE_NO_DRAW)) {
        if (maskObj->m_dispInfo.m_minX <= 0.0f || maskObj->m_dispInfo.m_minY <= 0.0f ||
            maskObj->m_dispInfo.m_maxX >= 1.0f || maskObj->m_dispInfo.m_maxY >= 1.0f) {
            return;
        }
        shdManager->setShaderMaskMode(maskObj);
    } else if (m_viewData != nullptr) {
        shdManager->setViewPort(m_viewData);
    } else {
        shdManager->setShaderMaskOff();
        shdManager->resetViewPort();
    }
    unsigned int blend = LayerShdManager::s_resDefBlend[m_curBlendType];
    if (shdManager->m_curBlend != blend) {
        LayerShdManager::s_CallBlend[blend]();
        shdManager->m_curBlend = blend;
    }
    if (!(m_stateFlags & STATE_3D_SPACE)) {
        shdManager->setDepthBufferCheckOff();
    } else if (!(m_stateFlags & STATE_RAW_POS)) {
        shdManager->setDepthBufferCheckOn();
    } else {
        shdManager->set3DSpaceMode(m_defUniform);
    }
    shdManager->setupVertex(static_cast<LayerDefVertType>(2));
    if (m_work->m_charNum != 0) {
        if (m_borderWeightDef > mm::mtl::PtrSingleton<LayerManager>::sys()->m_timeScale) {
            shdManager->m_select.m_iconType = 5;
            shdManager->m_select.m_shaderType = 2;
            shdManager->setupShader(m_work->m_uniform);
            shdManager->setupInstaceVertex(*m_work->m_instans, LayerFontTag::FONT_INSTANCE_SIZE, 0);
            shdManager->setupTexture(*m_work->m_font->m_texture, static_cast<LayerSamplerType>(m_texFilterType), 0);
            shdManager->renderInstaceQuadsIndex(m_work->m_charNum);
            shdManager->m_select.m_iconType = m_colorMap != nullptr ? 4 : 3;
            shdManager->m_select.m_shaderType = 2;
            shdManager->setupShader(m_work->m_uniform);
            shdManager->setupInstaceVertex(*m_work->m_instans, LayerFontTag::FONT_INSTANCE_SIZE, 0);
            shdManager->setupTexture(*m_work->m_font->m_texture, static_cast<LayerSamplerType>(m_texFilterType), 0);
            if (m_colorMap != nullptr) {
                const LayerTextureObj* colorMap = m_colorMap->m_texture;
                shdManager->setupTexture(*colorMap->getTexture(0), static_cast<LayerSamplerType>(m_texFilterType), 1);
            }
            shdManager->renderInstaceQuadsIndex(m_work->m_charNum);
        } else {
            shdManager->m_select.m_iconType = m_colorMap != nullptr ? 2 : 1;
            shdManager->m_select.m_shaderType = 2;
            shdManager->setupShader(m_work->m_uniform);
            shdManager->setupInstaceVertex(*m_work->m_instans, LayerFontTag::FONT_INSTANCE_SIZE, 0);
            shdManager->setupTexture(*m_work->m_font->m_texture, static_cast<LayerSamplerType>(m_texFilterType), 0);
            if (m_colorMap != nullptr) {
                const LayerTextureObj* colorMap = m_colorMap->m_texture;
                shdManager->setupTexture(*colorMap->getTexture(0), static_cast<LayerSamplerType>(m_texFilterType), 1);
            }
            shdManager->renderInstaceQuadsIndex(m_work->m_charNum);
        }
    }
    if (m_work->m_iconNum != 0) {
        shdManager->m_select.m_iconType = 6;
        shdManager->m_select.m_shaderType = 2;
        shdManager->setupShader(m_work->m_uniform);
        shdManager->setupInstaceVertex(*m_work->m_instans, LayerFontTag::FONT_INSTANCE_SIZE, m_work->m_iconOffset);
        const LayerTextureObj* icon = m_icon->m_texture;
        shdManager->setupTexture(*icon->getTexture(0), static_cast<LayerSamplerType>(m_texFilterType), 0);
        shdManager->renderInstaceQuadsIndex(m_work->m_iconNum);
    }
}
LayerObjTopLayout::~LayerObjTopLayout() {
    baseRelease();
    workLayoutRelease();
    m_objList.deleteAll();
    m_childList[0].deleteAll();
    m_childList[1].deleteAll();
}
void LayerObjTopLayout::workLayoutCreate(const void* resource) {
    m_resData = resource;
    const LyrLayoutBinHeader* header = static_cast<const LyrLayoutBinHeader*>(resource);
    m_layoutData = static_cast<const char*>(resource) + header->m_dataOfs;
    const LyrLayoutPosData* posData =
        reinterpret_cast<const LyrLayoutPosData*>(static_cast<const char*>(resource) + header->m_posDataOfs);
    m_posData = posData;
    const LyrLayoutBinTbl* tbl =
        reinterpret_cast<const LyrLayoutBinTbl*>(static_cast<const char*>(resource) + header->m_tblOfs);
    const LyrLayoutBinObj* objs =
        reinterpret_cast<const LyrLayoutBinObj*>(static_cast<const char*>(resource) + tbl->m_ofs);
    int num = header->m_posNum;
    for (int i = 0; i < num; i++, posData++) {
        if (posData->m_flags & LyrLayoutPosData::FLAG_OBJ) {
            const LyrLayoutBinObj* objData = &objs[posData->m_objIdx];
            LayerObj* obj = static_cast<LayerObj*>(
                LayerObjManager::createStaticObj(static_cast<const char*>(m_resData) + objData->m_resOfs));
            float pos[4];
            LayerObjUtil::getLayoutInfo(pos, posData, static_cast<LayerCenterType>(obj->m_renderInfo.m_centerType),
                                        static_cast<unsigned short>(obj->m_renderInfo.m_pixelWidth),
                                        static_cast<unsigned short>(obj->m_renderInfo.m_pixelHeight));
            obj->setInitPosScl(pos[0], pos[1], pos[2], pos[3]);
            m_objList.addListNotNull(obj);
        }
    }
    m_renderInfo.m_scale[0] = 1.0f;
    m_renderInfo.m_scale[1] = 1.0f;
    m_renderInfo.m_width = 1.0f;
    m_renderInfo.m_height = 1.0f;
    m_renderInfo.m_pixelX = 0;
    m_renderInfo.m_pixelY = 0;
    m_renderInfo.m_pixelWidth = 0;
    m_renderInfo.m_pixelHeight = 0;
}
void LayerObjTopLayout::updateDispOffLayout(LayerResUpdateInfo& info, const LayerRenderView* view) {
    for (LayerBase* obj = m_objList.m_head; obj != nullptr;) {
        LayerBase* next = obj->m_next;
        if (static_cast<LayerObj*>(obj)->isFlag(LayerManager::s_nDebIdx, LayerObj::FLAG_RELEASE)) {
            m_objList.removeList(obj);
            mm::mtl::PtrSingleton<LayerManager>::sys()->m_objManager->m_deleteList.addListNotNull(obj);
        } else {
            static_cast<LayerObj*>(obj)->applyBegin(info, view);
        }
        obj = next;
    }
    if (m_renderFlags & RENDER_TEXTURE) {
        m_texObj->applyBegin(info, view);
    }
}
void LayerObjTopLayout::updateEndLayout(const LayerRenderView* view, LayerResUpdateInfo& info) {
    if (m_oldUniform != nullptr) {
        delete m_oldUniform;
        m_oldUniform = nullptr;
    }
    LayerRenderView localView;
    const LayerRenderView* childView;
    if (m_renderFlags & RENDER_TEXTURE) {
        LayerObjUtil::calcLayerRenderView(localView, m_viewPortInfo, m_uniform, m_texViewPort, view, info.m_matrix);
        m_viewPortInfo.m_pRenderTarget = m_renderTarget;
        m_viewPortInfo.m_clearColor = m_clearColor;
        m_viewPortInfo.m_flags = 0;
        childView = &localView;
    } else if (m_stateFlags & STATE_VIEWPORT) {
        LayerObjUtil::calcLayerRenderView(localView, m_viewPortInfo, m_uniform, m_viewPort, view, info.m_matrix);
        m_viewPortInfo.m_pRenderTarget = nullptr;
        m_viewPortInfo.m_flags = 0;
        childView = &localView;
    } else {
        m_oldUniform = m_uniform;
        m_uniform = nullptr;
        childView = view;
    }
    for (LayerBase* obj = m_objList.m_head; obj != nullptr;) {
        LayerBase* next = obj->m_next;
        static_cast<LayerObj*>(obj)->applyEnd(info, childView);
        obj = next;
    }
    if (m_renderFlags & RENDER_TEXTURE) {
        m_texObj->applyEnd(info, view);
    }
}
void LayerObjTopLayout::applyEnd(LayerResUpdateInfo& info, const LayerRenderView* view) {
    if (m_stateFlags & STATE_NO_UPDATE) return;
    LayerResMatrix matrix;
    matrix.mul(m_localMatrix, *info.m_matrix);
    LayerResColor color;
    color.mul(m_params[2].m_color, *info.m_color);
    LayerResUpdateInfo child;
    child.m_matrix = &matrix;
    child.m_color = &color;
    child.m_flag50 = true;
    child.m_blendType = m_blendType;
    if (m_maskObj != nullptr) {
        child.m_maskObj = m_maskObj;
    } else {
        child.m_maskObj = info.m_maskObj;
    }
    updateEndLayout(view, child);
    m_dispInfo.m_minX = m_dispInfo.m_minY = -100000.0f;
    m_dispInfo.m_maxX = m_dispInfo.m_maxY = 100000.0f;
    LayerObjUtil::calcLayoutDispInfo(m_dispInfo, matrix, m_renderInfo);
}
void LayerObjUtil::calcLayerRenderView(LayerRenderView& view, LayerResViewPortInfo& info,
                                       grlib::CGLibDblUniformBlock*& uniform, const LayerViewPort& vp,
                                       const LayerRenderView* parent, const LayerResMatrix* matrix) {
    LayerShdManager* shdManager = mm::mtl::PtrSingleton<LayerManager>::sys()->m_shdManager;
    view = *parent;
    float posX = matrix->m_transX * shdManager->m_screenWidth;
    float posY = matrix->m_transY * shdManager->m_screenHeight * (1.0f / shdManager->m_viewPortDivY);
    info.m_viewPort.m_x = posX + vp.m_x;
    info.m_viewPort.m_y = posY + vp.m_y;
    info.m_viewPort.m_height = vp.m_height;
    info.m_viewPort.m_width = vp.m_width;
    if (uniform == nullptr) {
        uniform = new (mm::mtl::PtrSingleton<LayerManager>::sys()->m_gxHandle, nullptr, 0, 4, false)
            grlib::CGLibDblUniformBlock();
        uniform->setup(0x40);
    }
    float* buff = reinterpret_cast<float*>(uniform->getBuff());
    float vx = info.m_viewPort.m_x;
    float scale = shdManager->m_viewPortScale;
    float x = vx * scale / shdManager->m_screenWidth;
    float y = scale * info.m_viewPort.m_y / shdManager->m_screenHeight;
    float sclX = 1.0f / (scale * info.m_viewPort.m_width / shdManager->m_screenWidth);
    float sclY = 1.0f / (scale * info.m_viewPort.m_height / shdManager->m_screenHeight);
    buff[0] = sclX;
    buff[1] = sclY;
    buff[2] = sclX - 1.0f + x * -2.0f * sclX;
    buff[3] = -((sclY - 1.0f) - (y + y) * sclY);
    uniform->updateData();
    info.m_pUniform = uniform;
    view.m_viewData = &info;
}
void LayerObjUtil::getLayoutInfo(float* pos, const LyrLayoutPosData* data, LayerCenterType type, float sclX, float sclY) {
    s_CallDataPos[mm::mtl::PtrSingleton<LayerManager>::sys()->m_coordinate](pos, data, type, sclX, sclY);
}
void LayerObjTopTexObj::finalRender() {
    LayerShdManager* shdManager = mm::mtl::PtrSingleton<LayerManager>::sys()->m_shdManager;
    const LayerObjTopMaskObj* maskObj = static_cast<const LayerObjTopMaskObj*>(m_curMaskObj);
    if (maskObj != nullptr && !(maskObj->m_stateFlags & STATE_NO_DRAW)) {
        if (maskObj->m_dispInfo.m_minX <= 0.0f || maskObj->m_dispInfo.m_minY <= 0.0f ||
            maskObj->m_dispInfo.m_maxX >= 1.0f || maskObj->m_dispInfo.m_maxY >= 1.0f) {
            return;
        }
        shdManager->setShaderMaskMode(maskObj);
    } else if (m_viewData != nullptr) {
        shdManager->setViewPort(m_viewData);
    } else {
        shdManager->setShaderMaskOff();
        shdManager->resetViewPort();
    }
    unsigned int blend = LayerShdManager::s_resDefBlend[m_curBlendType];
    if (shdManager->m_curBlend != blend) {
        LayerShdManager::s_CallBlend[blend]();
        shdManager->m_curBlend = blend;
    }
    if (!(m_stateFlags & STATE_3D_SPACE)) {
        shdManager->setDepthBufferCheckOff();
    } else if (!(m_stateFlags & STATE_RAW_POS)) {
        shdManager->setDepthBufferCheckOn();
    } else {
        shdManager->set3DSpaceMode(m_defUniform);
    }
    shdManager->m_select.m_gaugeType = 1;
    shdManager->setSecTexture(m_secTexture[2]);
    shdManager->setupVertex(static_cast<LayerDefVertType>(1));
    shdManager->m_select.m_shaderType = 1;
    shdManager->setupShader(&m_uniform);
    shdManager->setupTexture(*m_texture, static_cast<LayerSamplerType>(m_texFilterType), 0);
    shdManager->renderQuadsIndex();
}
// the render size and the buffers' size of memSize (inline in createWorkBuffer; the name is not the original's)
static inline unsigned int calcWorkSize(LayerObjTopMemObj* obj, LayerObjTopMemObj::MemSize memSize) {
    obj->m_renderInfo.m_width = 1.0f;
    obj->m_renderInfo.m_height = static_cast<float>(obj->m_memSize.m_height) / static_cast<float>(memSize.m_width);
    if (memSize.m_width > memSize.m_height) {
        obj->m_renderInfo.m_scale[0] = 1.0f;
        obj->m_renderInfo.m_scale[1] = static_cast<float>(memSize.m_height) / static_cast<float>(memSize.m_width);
    } else {
        obj->m_renderInfo.m_scale[0] = static_cast<float>(memSize.m_width) / static_cast<float>(memSize.m_height);
        obj->m_renderInfo.m_scale[1] = 1.0f;
    }
    obj->m_renderInfo.m_pixelX = 0;
    obj->m_renderInfo.m_pixelY = 0;
    obj->m_renderInfo.m_pixelWidth = memSize.m_width;
    obj->m_renderInfo.m_pixelHeight = memSize.m_height;
    unsigned int size;
    if (obj->m_memType == 2) {
        size = memSize.m_width * 2 * memSize.m_height;
    } else {
        size = memSize.m_width * memSize.m_height;
        if (obj->m_memType == 3) {
            size += -size & 0xFF;
            obj->m_planeOfs = size;
            unsigned int chromaSize = (memSize.m_width & ~1) * (memSize.m_height >> 1);
            chromaSize += -chromaSize & 0xF;
            obj->m_planeSize = chromaSize;
            size = chromaSize + size;
        } else {
            size *= 3;
        }
    }
    size += -size & 0xF;
    return size;
}
void LayerObjTopMemObj::createWorkBuffer() {
    m_uniform.setup(0x80);
    unsigned int size = calcWorkSize(this, m_memSize);
    m_buffers[0].setup(size);
    m_buffers[1].setup(size);
    m_oneUniform.setup(0x10);
    m_clearBuffers[0].setup(0x10);
    unsigned long* clear = reinterpret_cast<unsigned long*>(m_clearBuffers[0].m_pBuff);
    clear[0] = 0;
    clear[1] = 0;
    m_clearBuffers[1].setup(0x10);
    clear = reinterpret_cast<unsigned long*>(m_clearBuffers[1].m_pBuff);
    clear[0] = 0;
    clear[1] = 0;
}
LayerObjTopMemObj::~LayerObjTopMemObj() {
    baseRelease();
    m_renderTarget.release();
    m_uniform.release();
    m_oneUniform.release();
    m_buffers[0].release();
    m_buffers[1].release();
    m_clearBuffers[0].release();
    m_clearBuffers[1].release();
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
void LayerObjTopMemObj::resourceInit() {
    if (m_renderFlags & RENDER_INIT) {
        m_renderFlags &= ~RENDER_INIT;
        m_renderTarget.setTextureInfo(m_memSize.m_width, m_memSize.m_height, static_cast<GrlSurfaceFormat>(37), false, 0);
        m_renderTarget.clearTexture(mm::Col4(0.0f, 0.0f, 0.0f, 0.0f), static_cast<GrlClaerMask>(15));
        unsigned int* size = reinterpret_cast<unsigned int*>(m_oneUniform.m_pBuff);
        size[0] = m_memSize.m_width;
        size[1] = m_memSize.m_height;
        if (m_memType == 3) {
            size[2] = m_memSize.m_width >> 1;
            size[3] = m_memSize.m_height >> 1;
        } else {
            size[2] = m_memSize.m_width;
            size[3] = m_memSize.m_height;
        }
        m_oneUniform.updateData();
    }
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
void LayerObjTopMemObj::setupRender() {
    unsigned int index = LayerManager::s_nDebIdx;
    m_renderFlags &= ~(1 << index);
    LayerShdManager* shdManager = mm::mtl::PtrSingleton<LayerManager>::sys()->m_shdManager;
    shdManager->m_select.m_shaderType = 9;
    shdManager->m_select.m_option = m_memType;
    grlib::CGLibDecShader* shader = shdManager->setupShader();
    m_renderTarget.setRenderTarget();
    m_oneUniform.setUniformBlock(shader->getCurrentShader().getUniformBlockOfs("U_MENU"));
    m_buffers[index].setStorageBuffer(0);
    if (m_memType != 1) m_buffers[index].setStorageBuffer(1, m_planeOfs, m_planeSize);
    m_clearBuffers[index].setStorageBuffer(2);
    shdManager->setupVertex(static_cast<LayerDefVertType>(3));
    shdManager->renderQuadsIndex();
    grlib::CGLibCtlShader::setMemoryBarrierBit(0x25);
    shdManager->m_select.m_shaderType = 9;
    shdManager->m_select.m_option = 4;
    shdManager->setupShader();
    m_clearBuffers[index].setStorageBuffer(2);
    shdManager->setupVertex(static_cast<LayerDefVertType>(3));
    grlib::CGLibCtlVertex::renderVertex(static_cast<GrlPrimitiveType>(0), 1);
    grlib::CGLibCtlShader::setMemoryBarrierBit(0x21);
    shdManager->getDefRenderTarget()->setRenderTarget();
}
void LayerObjTopMemObj::lastRender() {
    LayerShdManager* shdManager = mm::mtl::PtrSingleton<LayerManager>::sys()->m_shdManager;
    const LayerObjTopMaskObj* maskObj = static_cast<const LayerObjTopMaskObj*>(m_curMaskObj);
    if (maskObj != nullptr && !(maskObj->m_stateFlags & STATE_NO_DRAW)) {
        if (maskObj->m_dispInfo.m_minX <= 0.0f || maskObj->m_dispInfo.m_minY <= 0.0f ||
            maskObj->m_dispInfo.m_maxX >= 1.0f || maskObj->m_dispInfo.m_maxY >= 1.0f) {
            return;
        }
        shdManager->setShaderMaskMode(maskObj);
    } else if (m_viewData != nullptr) {
        shdManager->setViewPort(m_viewData);
    } else {
        shdManager->setShaderMaskOff();
        shdManager->resetViewPort();
    }
    unsigned int blend = LayerShdManager::s_resDefBlend[m_curBlendType];
    if (shdManager->m_curBlend != blend) {
        LayerShdManager::s_CallBlend[blend]();
        shdManager->m_curBlend = blend;
    }
    if (!(m_stateFlags & STATE_3D_SPACE)) {
        shdManager->setDepthBufferCheckOff();
    } else if (!(m_stateFlags & STATE_RAW_POS)) {
        shdManager->setDepthBufferCheckOn();
    } else {
        shdManager->set3DSpaceMode(m_defUniform);
    }
    shdManager->m_select.m_gaugeType = 1;
    shdManager->setSecTexture(m_secTexture[2]);
    shdManager->setupVertex(static_cast<LayerDefVertType>(1));
    shdManager->m_select.m_shaderType = 1;
    shdManager->setupShader(&m_uniform);
    shdManager->setupTexture(*m_renderTarget.m_pTexture, static_cast<LayerSamplerType>(m_texFilterType), 0);
    shdManager->renderQuadsIndex();
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
LayerObjTopPolyObj::~LayerObjTopPolyObj() {
    baseRelease();
    m_uniform.release();
    releasePoly(m_polyWork);
    m_resTex.clear();
    if (m_polyBuffer != nullptr) {
        mtl::MemManager::deallocate(m_polyBuffer, 0, false);
        m_polyBuffer = nullptr;
    }
}
void LayerObjTopPolyObj::LockVertex() { m_locked = m_polyWork.m_vertices[LayerManager::s_nStkIdx]; }
void LayerObjTopPolyObj::setVertex(unsigned int index, const LayerPolyVertex& vertex) {
    static_cast<LayerPolyVertex*>(m_locked)[index] = vertex;
}
void LayerObjTopPolyObj::UnlockVertex() {
    m_updateFlags |= UPDATE_VERTEX << LayerManager::s_nStkIdx;
    m_locked = nullptr;
}
void LayerObjTopPolyObj::LockIndex() { m_locked = m_polyWork.m_indices[LayerManager::s_nStkIdx]; }
void LayerObjTopPolyObj::setIndex(unsigned int index, unsigned short value) {
    static_cast<unsigned short*>(m_locked)[index] = value;
}
void LayerObjTopPolyObj::UnlockIndex() {
    m_updateFlags |= UPDATE_INDEX << LayerManager::s_nStkIdx;
    m_locked = nullptr;
}
void LayerObjTopPolyObj::setTexutre(const void* texture) { m_resTex.setAddTexture(texture, 0); }
void LayerObjTopPolyObj::setTexutre(grlib::CGLibTextureBuffer& texture) { m_resTex.setAddTexture(texture, 0); }
void LayerObjResTex::setAddTexture(const void* res, unsigned int index) {
    for (LayerResAddTexObj* obj = m_list.m_head; obj != nullptr; obj = obj->m_next) {
        if (obj->m_index == index) obj->m_flags |= 1 << LayerManager::s_nStkIdx;
    }
    LayerResAddTexObj* obj =
        new (mm::mtl::PtrSingleton<LayerManager>::sys()->m_workHandle, nullptr, 0, 4, false) LayerResAddTexObj(res, index);
    m_addLists[LayerManager::s_nStkIdx].addListNotNull(obj);
}
void LayerObjResTex::setAddTexture(grlib::CGLibTextureBuffer& texture, unsigned int index) {
    for (LayerResAddTexObj* obj = m_list.m_head; obj != nullptr; obj = obj->m_next) {
        if (obj->m_index == index) obj->m_flags |= 1 << LayerManager::s_nStkIdx;
    }
    LayerResAddTexObj* obj = new (mm::mtl::PtrSingleton<LayerManager>::sys()->m_workHandle, nullptr, 0, 4, false)
        LayerResAddTexObj(&texture, index);
    m_addLists[LayerManager::s_nStkIdx].addListNotNull(obj);
}
void LayerObjTopPolyObj::setIndexInfo(unsigned short start, unsigned short count) {
    int index = LayerManager::s_nStkIdx;
    m_updateFlags |= UPDATE_INDEX_INFO << index;
    m_indexStart[index] = start;
    m_indexCount[index] = count;
}
void LayerObjTopPolyObj::releasePoly(layPolyWork& work) {
    for (int i = 0; i < 2; i++) {
        if (work.m_vertex[i] != nullptr) {
            delete work.m_vertex[i];
            work.m_vertex[i] = nullptr;
        }
    }
    for (int i = 0; i < 2; i++) {
        if (work.m_index[i] != nullptr) {
            delete work.m_index[i];
            work.m_index[i] = nullptr;
        }
    }
}
void LayerObjResTex::clear() {
    m_list.deleteAll();
    m_addLists[0].deleteAll();
    m_addLists[1].deleteAll();
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
bool LayerObjResTex::updateTexutre(grlib::CGLibTextureBuffer** textures, LayerTextureObj* textureObj) {
    bool changed = false;
    unsigned int index = LayerManager::s_nDebIdx;
    LayerLinkList<LayerResAddTexObj>& addList = m_addLists[index];
    for (LayerResAddTexObj* obj = m_list.m_head; obj != nullptr;) {
        LayerResAddTexObj* next = obj->m_next;
        if ((1 << LayerManager::s_nDebIdx) & obj->m_flags) {
            if (textures != nullptr) {
                textures[obj->m_index] = textureObj->getTexture(obj->m_index);
                changed = true;
            }
            m_list.deleteList(obj);
        }
        obj = next;
    }
    if (addList.m_head != nullptr) {
        for (LayerResAddTexObj* obj = addList.m_head; obj != nullptr;) {
            LayerResAddTexObj* next = obj->m_next;
            addList.removeList(obj);
            obj->setupResource();
            if (textures != nullptr) {
                textures[obj->m_index] = obj->getTexObj(0);
                changed = true;
            }
            m_list.addListNotNull(obj);
            obj = next;
        }
        addList.m_num = 0;
        addList.m_head = nullptr;
        addList.m_tail = nullptr;
    }
    return changed;
}
void LayerObjTopPolyObj::applyPartsSetup() { updateVertexBuffer(); }
void LayerObjTopPolyObj::finalRender() {
    LayerShdManager* shdManager = mm::mtl::PtrSingleton<LayerManager>::sys()->m_shdManager;
    const LayerObjTopMaskObj* maskObj = static_cast<const LayerObjTopMaskObj*>(m_curMaskObj);
    if (maskObj != nullptr && !(maskObj->m_stateFlags & STATE_NO_DRAW)) {
        if (maskObj->m_dispInfo.m_minX <= 0.0f || maskObj->m_dispInfo.m_minY <= 0.0f ||
            maskObj->m_dispInfo.m_maxX >= 1.0f || maskObj->m_dispInfo.m_maxY >= 1.0f) {
            return;
        }
        shdManager->setShaderMaskMode(maskObj);
    } else if (m_viewData != nullptr) {
        shdManager->setViewPort(m_viewData);
    } else {
        shdManager->setShaderMaskOff();
        shdManager->resetViewPort();
    }
    unsigned int blend = LayerShdManager::s_resDefBlend[m_curBlendType];
    if (shdManager->m_curBlend != blend) {
        LayerShdManager::s_CallBlend[blend]();
        shdManager->m_curBlend = blend;
    }
    if (!(m_stateFlags & STATE_3D_SPACE)) {
        shdManager->setDepthBufferCheckOff();
    } else if (!(m_stateFlags & STATE_RAW_POS)) {
        shdManager->setDepthBufferCheckOn();
    } else {
        shdManager->set3DSpaceMode(m_defUniform);
    }
    if (m_texture != nullptr && m_texture->isInitialized()) {
        shdManager->m_select.m_option = 2;
    } else {
        shdManager->m_select.m_option = 1;
    }
    shdManager->setSecTexture(m_secTexture[2]);
    grlib::CGLibCtlVertex::setVertex(*m_polyWork.m_vertex[m_vertexBufIdx]);
    shdManager->m_select.m_shaderType = 6;
    shdManager->setupShader(&m_uniform);
    if (m_texture != nullptr && m_texture->isInitialized()) {
        shdManager->setupTexture(*m_texture, static_cast<LayerSamplerType>(m_texFilterType), 0);
    }
    m_polyWork.m_index[m_indexBufIdx]->drawIndex(m_drawIndexCount, m_drawIndexStart * 2);
}
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
const grlib::CGLibTextureBuffer& LayerObjTopMaskObj::getTexture() const { return *m_texture->getTexture(0); }
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
const unsigned int LayerShdManager::s_resDefBlend[6] = {0, 3, 5, 7, 2, 0};
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

