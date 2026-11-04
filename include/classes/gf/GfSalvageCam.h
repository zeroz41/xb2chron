#ifndef CLASSES_GF_GFSALVAGECAM_H
#define CLASSES_GF_GFSALVAGECAM_H

#include "mm/mtl/RTTI.h"
#include "classes/fw/Camera.h"

namespace gf {
// the salvage camera: its RTTI's parent is fw::Camera's. Only the RTTI is recovered so far; its members are not
// declared yet (GfQuestUtil::applyNeedFollowQuestTask/313414/3134FC/3135E4 are not its functions: they are quest helpers of
// QuestTaskParam.cpp, called by GfGameScene and GfQuestUtil::getMsgQuestTaskLog).
class GfSalvageCam : public ::fw::Camera {
public:
    static mm::mtl::RTTI m_rtti;
};
}  // namespace gf

#endif
