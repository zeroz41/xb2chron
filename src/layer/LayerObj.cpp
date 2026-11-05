#include "math.h"
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
    const Param& param = getParam(FLAG_POS);
    x = param.m_pos[0];
    y = param.m_pos[1];
}
void LayerObj::getRot(float& rot) const { rot = getParam(FLAG_ROT).m_rot; }
void LayerObj::getScale(float& x, float& y) const {
    const Param& param = getParam(FLAG_SCALE);
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
    const LyrActionData* data = m_actionData;
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
    const LyrActionData* data = m_actionData;
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
    const LyrActionData* data = m_actionData;
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
    const LyrActionData* data = m_actionData;
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
    if (m_actionData->m_flags & LyrActionData::FLAG_CMD_START) {
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
        m_frames[i].pad_4 = 0.0f;
    }
    m_texRefs->m_frameEnd = m_texRefs->m_anim->m_frameNum;
    m_texRefs->m_frameStart = 0.0f;
    m_frameTime = 0.0f;
    cmd += 4;
    return false;
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
void LayerObjMesh::call_uniform_win_ga_X(LayerArgMdlRenInf& arg) { setUniformWinGaX(arg, false); }
void LayerObjMesh::call_uniform_win_ga_Y(LayerArgMdlRenInf& arg) { setUniformWinGaY(arg, false); }
void LayerObjMesh::call_uniform_icon(LayerArgMdlRenInf& arg) {
    LayerObjUtil::updatePosMatrixUniformBlock(arg.m_buff, arg.m_matrix, *arg.m_viewMatrix, m_posZ,
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
LayerObjTopLayout::~LayerObjTopLayout() {
    baseRelease();
    workLayoutRelease();
    m_objList.deleteAll();
    m_childList[0].deleteAll();
    m_childList[1].deleteAll();
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
        m_renderTarget.setTextureInfo(m_memWidth, m_memHeight, static_cast<GrlSurfaceFormat>(37), false, 0);
        m_renderTarget.clearTexture(mm::Col4(0.0f, 0.0f, 0.0f, 0.0f), static_cast<GrlClaerMask>(15));
        unsigned int* size = reinterpret_cast<unsigned int*>(m_oneUniform.m_pBuff);
        size[0] = m_memWidth;
        size[1] = m_memHeight;
        if (m_memType == 3) {
            size[2] = m_memWidth >> 1;
            size[3] = m_memHeight >> 1;
        } else {
            size[2] = m_memWidth;
            size[3] = m_memHeight;
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

