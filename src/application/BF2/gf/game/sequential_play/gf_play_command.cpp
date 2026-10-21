#include "classes/gf/GfPlayComCallbackEventSequence.h"
#include "classes/gf/GfPlayComGmkCameraSeq.h"
#include "classes/gf/GfPlayComHoodHomuraBattou.h"
#include "classes/gf/GfPlayComMapjump.h"
#include "classes/gf/GfPlayComMenuChapter.h"
#include "classes/gf/GfPlayComMenuChapterEnd.h"
#include "classes/gf/GfPlayComMenuCommon.h"
#include "classes/gf/GfPlayComMenuCommonFromParam.h"
#include "classes/gf/GfPlayComMenuDummyTutorial.h"
#include "classes/gf/GfPlayComMenuZone.h"
#include "classes/gf/GfPlayComMiniGame.h"
#include "classes/gf/GfPlayComOpenMenu.h"
#include "classes/gf/GfPlayComPause.h"
#include "classes/gf/GfPlayComResetBlade.h"
#include "classes/gf/GfPlayComSalvage.h"
#include "classes/gf/GfPlayComState.h"
#include "classes/gf/GfPlayComWait.h"

namespace gf {

void GfPlayComPause::end() {}

void GfPlayComState::end() {}

void GfPlayComWait::start() {}

void GfPlayComWait::end() {}

void GfPlayComMapjump::end() {}

void GfPlayComCallbackEventSequence::end() {}

void GfPlayComOpenMenu::end() {}

void GfPlayComMiniGame::end() {}

void GfPlayComMenuChapter::end() {}

void GfPlayComMenuChapterEnd::end() {}

void GfPlayComMenuZone::end() {}

void GfPlayComMenuDummyTutorial::end() {}

void GfPlayComMenuCommon::end() {}

void GfPlayComMenuCommonFromParam::end() {}

void GfPlayComSalvage::start() {}

void GfPlayComGmkCameraSeq::start() {}

void GfPlayComResetBlade::end() {}

void GfPlayComHoodHomuraBattou::start() {}

void GfPlayComHoodHomuraBattou::end() {}

}  // namespace gf
