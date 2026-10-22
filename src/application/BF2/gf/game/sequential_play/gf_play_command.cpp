#include "gf/FileStaticVec3.h"
#include "classes/gf/GfPlayComEventWeather.h"
#include "classes/gf/GfPlayComIraCampSave.h"
#include "classes/gf/GfPlayComOpenNpcEntry.h"
#include "classes/gf/GfPlayComMenuQuestList.h"
#include "classes/gf/GfPlayComMenuKizunaring.h"
#include "classes/gf/GfPlayComMenuCommon.h"
#include "classes/gf/GfPlayComMenuCommonFromParam.h"
#include "classes/gf/GfPlayComResetBlade.h"
#include "classes/gf/GfPlayComMoverSwitch.h"
#include "classes/gf/GfPlayComMapjumpForArena.h"
#include "classes/gf/GfPlayComMapjumpForLeaveArena.h"
#include "classes/gf/GfPlayComMapjumpForBattleMapFromArena.h"
#include "classes/gf/GfPlayComWaitArenaStateField.h"
#include "classes/gf/GfPlayComStartChallengeBattle.h"
#include "classes/gf/GfPlayComScriptTutorialSeq.h"
#include "classes/gf/GfPlayCom.h"
#include "classes/gf/GfPlayComEventFade.h"
#include "classes/gf/GfPlayComWaitEvent.h"
#include "classes/gf/GfPlayComWaitBattleEnd.h"
#include "classes/gf/GfPlayComEventPlayerStop.h"
#include "classes/gf/GfPlayComResetBladePlayerStop.h"
#include "classes/gf/GfPlayComAfterEventScript.h"
#include "classes/gf/GfPlayComEvent.h"
#include "classes/gf/GfPlayComOpenMenu2.h"
#include "classes/gf/GfPlayComStartTutorial.h"
#include "classes/gf/GfPlayComMenuChapterSave.h"
#include "classes/gf/GfPlayComMenuPrecious.h"
#include "classes/gf/GfPlayComCollect.h"
#include "classes/gf/GfPlayComFieldTbox.h"
#include "classes/gf/GfPlayComFieldSeq.h"
#include "classes/gf/GfPlayComWaitPlayerToStartGmkTuto.h"
#include "classes/gf/GfPlayComGmkTutorialSeq.h"
#include "classes/gf/GfPlayComPlayerDead.h"
#include "classes/gf/GfPlayComTalk.h"
#include "classes/gf/GfPlayComQuestOrderUI.h"
#include "classes/gf/GfPlayComQuestCompleteUI.h"
#include "classes/gf/GfPlayComGimmickTaskComplete.h"
#include "classes/gf/GfPlayComReturnTitle.h"
#include "classes/gf/GfPlayComBattleStart.h"
#include "classes/gf/GfPlayComExecuteSignal.h"
#include "classes/gf/GfPlayComChainAttack.h"
#include "classes/gf/GfPlayComArtsMovie.h"
#include "classes/gf/GfPlayComMenuObjCommonText.h"
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

mm::mtl::RTTI GfPlayCom::m_rtti("GfPlayCom", nullptr, nullptr);
mm::mtl::RTTI GfPlayComEventFade::m_rtti("GfPlayComEventFade", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComEventWeather::m_rtti("GfPlayComEventWeather", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComPause::m_rtti("GfPlayComPause", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComState::m_rtti("GfPlayComState", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComWait::m_rtti("GfPlayComWait", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComWaitEvent::m_rtti("GfPlayComWaitEvent", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComMapjump::m_rtti("GfPlayComMapjump", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComWaitBattleEnd::m_rtti("GfPlayComWaitBattleEnd", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComEventPlayerStop::m_rtti("GfPlayComEventPlayerStop", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComResetBladePlayerStop::m_rtti("GfPlayComResetBladePlayerStop", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComAfterEventScript::m_rtti("GfPlayComAfterEventScript", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComEvent::m_rtti("GfPlayComEvent", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComCallbackEventSequence::m_rtti("GfPlayComCallbackEventSequence", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComIraCampSave::m_rtti("GfPlayComIraCampSave", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComOpenMenu::m_rtti("GfPlayComOpenMenu", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComOpenMenu2::m_rtti("GfPlayComOpenMenu2", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComStartTutorial::m_rtti("GfPlayComStartTutorial", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComOpenNpcEntry::m_rtti("GfPlayComOpenNpcEntry", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComMiniGame::m_rtti("GfPlayComMiniGame", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComMenuChapterSave::m_rtti("GfPlayComMenuChapterSave", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComMenuChapter::m_rtti("GfPlayComMenuChapter", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComMenuChapterEnd::m_rtti("GfPlayComMenuChapterEnd", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComMenuZone::m_rtti("GfPlayComMenuZone", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComMenuDummyTutorial::m_rtti("GfPlayComMenuDummyTutorial", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComMenuQuestList::m_rtti("GfPlayComMenuQuestList", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComMenuKizunaring::m_rtti("GfPlayComMenuKizunaring", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComMenuPrecious::m_rtti("GfPlayComMenuPrecious", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComMenuCommon::m_rtti("GfPlayComMenuCommon", &GfPlayCom::m_rtti, nullptr);
mm::mtl::FixedQueue<unsigned int, 32> GfPlayComMenuCommon::s_list;
mm::mtl::RTTI GfPlayComMenuCommonFromParam::m_rtti("GfPlayComMenuCommonFromParam", &GfPlayCom::m_rtti, nullptr);
mm::mtl::FixedQueue<unsigned int, 32> GfPlayComMenuCommonFromParam::s_list;
mm::mtl::RTTI GfPlayComSalvage::m_rtti("GfPlayComSalvage", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComCollect::m_rtti("GfPlayComCollect", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComFieldTbox::m_rtti("GfPlayComFieldTbox", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComFieldSeq::m_rtti("GfPlayComFieldSeq", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComWaitPlayerToStartGmkTuto::m_rtti("GfPlayComWaitPlayerToStartGmkTuto", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComGmkTutorialSeq::m_rtti("GfPlayComGmkTutorialSeq", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComGmkCameraSeq::m_rtti("GfPlayComGmkCameraSeq", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComPlayerDead::m_rtti("GfPlayComPlayerDead", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComTalk::m_rtti("GfPlayComTalk", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComQuestOrderUI::m_rtti("GfPlayComQuestOrderUI", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComQuestCompleteUI::m_rtti("GfPlayComQuestCompleteUI", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComGimmickTaskComplete::m_rtti("GfPlayComGimmickTaskComplete", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComReturnTitle::m_rtti("GfPlayComReturnTitle", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComBattleStart::m_rtti("GfPlayComBattleStart", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComExecuteSignal::m_rtti("GfPlayComExecuteSignal", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComChainAttack::m_rtti("GfPlayComChainAttack", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComArtsMovie::m_rtti("GfPlayComArtsMovie", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComResetBlade::m_rtti("GfPlayComResetBlade", &GfPlayCom::m_rtti, nullptr);
mm::mtl::FixedVector<signed char, 3> GfPlayComResetBlade::s_execFlag;
mm::mtl::RTTI GfPlayComMoverSwitch::m_rtti("GfPlayComMoverSwitch", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComHoodHomuraBattou::m_rtti("GfPlayComHoodHomuraBattou", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComMenuObjCommonText::m_rtti("GfPlayComMenuObjCommonText", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComMapjumpForArena::m_rtti("GfPlayComMapjumpForArena", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComMapjumpForLeaveArena::m_rtti("GfPlayComMapjumpForLeaveArena", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComMapjumpForBattleMapFromArena::m_rtti("GfPlayComMapjumpForBattleMapFromArena", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComWaitArenaStateField::m_rtti("GfPlayComWaitArenaStateField", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComStartChallengeBattle::m_rtti("GfPlayComStartChallengeBattle", &GfPlayCom::m_rtti, nullptr);
mm::mtl::RTTI GfPlayComScriptTutorialSeq::m_rtti("GfPlayComScriptTutorialSeq", &GfPlayCom::m_rtti, nullptr);

}  // namespace gf
