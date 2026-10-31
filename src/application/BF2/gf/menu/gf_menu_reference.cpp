#include "classes/gf/GfMenuReference.h"
#include "classes/gf/GfMenuEnemyList.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfMenuEnemyList.h"
#include "classes/gf/GfMenuItemList.h"
#include "classes/gf/GfMenuObjArtsPalette.h"
#include "classes/gf/GfMenuObjPartyStatus.h"
#include "classes/gf/GfMenuReference.h"
#include "classes/gf/GfMenuObjArtsPalette.h"
#include "classes/gf/GfMenuObjPartyStatus.h"
#include "classes/gf/GfMenuObjPartyGauge.h"
#include "classes/gf/GfMenuObjBladeChange.h"
#include "classes/gf/TUnk_B60E28.h"
#include "classes/gf/TUnk_B63AE0.h"
#include "gf/GfMenuObjUtil.h"

namespace gf {

void GfMenuReference::build(const GfSetupParam& param) {
#line 72
    new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfMenuReference(param);
}

void GfMenuReference::destroy() {
    GfMenuReference* menu = get();
    menu->finalize();
    delete menu;
}

bool GfMenuReference::isInitialized() {
    GfMenuReference* self = get();
    if (self) return self->m_initialized;
    return false;
}

void GfMenuReference::resetDriverVirtual() {
    GfMenuReference* self = get();
    if (self) {
        self->m_driverVirtualLevel = 0;
        self->m_driverVirtualBladeID = 0;
        self->m_driverVirtualBladeSlot = 0;
        self->m_driverVirtualEquipAcc = 0;
        self->m_driverVirtualEquipAccSlot = 0;
        self->m_driverAddIdeaLv[0] = 0;
        self->m_driverAddIdeaLv[1] = 0;
        self->m_driverAddIdeaLv[2] = 0;
        self->m_driverAddIdeaLv[3] = 0;
    }
}

void GfMenuReference::postReset() {
    GfMenuReference* self = get();
    if (self) {
        for (unsigned int i = 0; i < 4; i++) {
            self->m_reversePaletteBtnState[i].set(2, false);
        }
    }
}

int GfMenuReference::getArtsPaletteElementType(unsigned char slot) {
    GfMenuReference* self = get();
    if (self) {
        if (slot < 3) return self->m_artsPalette[slot].m_elementType;
        if (slot < 9) return self->m_artsPaletteEx[slot - 3].m_elementType;
    }
    return 0;
}

bool GfMenuReference::isArtsPaletteEnable(unsigned char slot) {
    GfMenuReference* self = get();
    if (self) {
        if (slot < 3) return self->m_artsPalette[slot].m_enable;
        if (slot < 9) return self->m_artsPaletteEx[slot - 3].m_enable;
    }
    return false;
}

unsigned int GfMenuReference::getArtsPaletteDisable(unsigned char slot) {
    GfMenuReference* self = get();
    if (self) {
        if (slot < 3) return self->m_artsPalette[slot].m_disable;
        if (slot < 9) return self->m_artsPaletteEx[slot - 3].m_disable;
    }
    return 0;
}

void GfMenuReference::setChainNum(unsigned int num) {
    GfMenuReference* self = get();
    if (self) self->m_chainNum = num;
}

int GfMenuReference::getChainNum() {
    GfMenuReference* self = get();
    if (self) return self->m_chainNum;
    return 0;
}

void GfMenuReference::setWeaponJustRange(bool range) {
    GfMenuReference* self = get();
    if (self) self->m_weaponJustRange = range;
}

bool GfMenuReference::isWeaponJustRange() {
    GfMenuReference* self = get();
    if (self) return self->m_weaponJustRange;
    return false;
}

void GfMenuReference::setAwakeningRestTimeRatio(float ratio) {
    GfMenuReference* self = get();
    if (self) self->m_awakeningRestTimeRatio = ratio;
}

float GfMenuReference::getAwakeningRestTimeRatio() {
    GfMenuReference* self = get();
    if (self) return self->m_awakeningRestTimeRatio;
    return 0.0f;
}

float GfMenuReference::getChainAttackActionRecast() {
    GfMenuReference* self = get();
    if (self) return self->m_chainAttackActionRecast;
    return 0.0f;
}

void GfMenuReference::setChainAttackActionPartyID(int party) {
    GfMenuReference* self = get();
    if (self) self->m_chainAttackActionPartyID = party;
}

int GfMenuReference::getChainAttackActionPartyID() {
    GfMenuReference* self = get();
    if (self) return self->m_chainAttackActionPartyID;
    return -1;
}

int GfMenuReference::getChainAttackActionCount() {
    GfMenuReference* self = get();
    if (self) return self->m_chainAttackActionCount;
    return 0;
}

void GfMenuReference::setChainAttackDamageRatio(float ratio) {
    GfMenuReference* self = get();
    if (self) self->m_chainAttackDamageRatio = ratio;
}

float GfMenuReference::getChainAttackDamageRatio() {
    GfMenuReference* self = get();
    if (self) return self->m_chainAttackDamageRatio;
    return 0.0f;
}

float GfMenuReference::getChainAttackExpRatio() {
    GfMenuReference* self = get();
    if (self) return self->m_chainAttackExpRatio;
    return 0.0f;
}

void GfMenuReference::setChainAttackTotalDamage(unsigned int damage) {
    GfMenuReference* self = get();
    if (self) self->m_chainAttackTotalDamage = damage;
}

int GfMenuReference::getChainAttackTotalDamage() {
    GfMenuReference* self = get();
    if (self) return self->m_chainAttackTotalDamage;
    return 0;
}

void GfMenuReference::setChainAttackBurstCount(unsigned int count) {
    GfMenuReference* self = get();
    if (self) self->m_chainAttackBurstCount = count;
}

int GfMenuReference::getChainAttackBurstCount() {
    GfMenuReference* self = get();
    if (self) return self->m_chainAttackBurstCount;
    return 0;
}

void GfMenuReference::fn_7100367360(unsigned int number) {
    GfMenuReference* self = get();
    if (self) self->m_chainAttackExtraNumber = number;
}

unsigned int GfMenuReference::fn_7100367380() {
    GfMenuReference* self = get();
    if (self) return self->m_chainAttackExtraNumber;
    return 0;
}

void GfMenuReference::fn_71003673A8(float seconds) {
    GfMenuReference* self = get();
    if (self) self->m_timeSeconds = seconds;
}

float GfMenuReference::fn_71003673C8() {
    GfMenuReference* self = get();
    if (self) return self->m_timeSeconds;
    return 0.0f;
}

float GfMenuReference::fn_710036742C() {
    GfMenuReference* self = get();
    if (self) return self->m_challengeRatio;
    return 0.0f;
}

void GfMenuReference::fn_7100367454(unsigned int value) {
    GfMenuReference* self = get();
    if (self) {
        if (self->m_bladeChangeValue != value) GfMenuObjBladeChange::fn_7100391CDC();
        self->m_bladeChangeValue = value;
    }
}

unsigned int GfMenuReference::fn_71003674A0() {
    GfMenuReference* self = get();
    if (self) return self->m_bladeChangeValue;
    return 0;
}

void GfMenuReference::setElementComboParty(unsigned int index, unsigned int party, float timeLeft) {
    if (index < 2) {
        GfMenuReference* self = get();
        if (self) {
            self->m_elementComboParty[index].m_party = party;
            self->m_elementComboParty[index].m_timeLeft = timeLeft;
        }
    }
}

int GfMenuReference::getElementComboParty(unsigned int index) {
    GfMenuReference* self = get();
    if (index < 2 && self) return self->m_elementComboParty[index].m_party;
    return 0;
}

float GfMenuReference::getElementComboPartyTimeLeft(unsigned int index) {
    if (index < 2) {
        GfMenuReference* self = get();
        if (self) return self->m_elementComboParty[index].m_timeLeft;
    }
    return 0.0f;
}

void GfMenuReference::setHomuraModeInBattle(HOMURA_MODE mode) {
    GfMenuReference* self = get();
    if (self) self->m_homuraModeInBattle = mode;
}

GfMenuReference::HOMURA_MODE GfMenuReference::getHomuraModeInBattle() {
    GfMenuReference* self = get();
    if (self) return self->m_homuraModeInBattle;
    return HOMURA_MODE(0);
}

void GfMenuReference::setPaletteModeReverse(bool reverse) {
    GfMenuReference* self = get();
    if (self) {
        if (self->m_paletteModeReverse != reverse) GfMenuObjArtsPalette::reverse(reverse);
        self->m_paletteModeReverse = reverse;
    }
}

const GfMenuReference::BladeOwner* GfMenuReference::fn_7100367BD8(unsigned int blade) {
    if (GfMenuObjUtil::fn_710048FD30(3)) {
        GfMenuReference* self = get();
        if (self) {
            for (const BladeOwner& owner : self->m_bladeOwner) {
                if (owner.m_gauge.m_type == blade) return &owner;
            }
        }
    }
    return nullptr;
}

const GfMenuReference::DriverGauge* GfMenuReference::fn_7100367C78(unsigned int driver) {
    if (GfMenuObjUtil::fn_710048FD30(3)) {
        GfMenuReference* self = get();
        if (self) {
            for (unsigned int i = 0; i < 3; i++) {
                if (self->m_bladeOwner[i].m_driver == driver) return &self->m_bladeOwner[i].m_gauge;
            }
        }
    }
    return nullptr;
}

void GfMenuReference::fn_7100367D1C() {
    if (GfMenuObjUtil::fn_710048FD30(3)) {
        GfMenuReference* self = get();
        if (self) {
            for (unsigned int i = 0; i < 3; i++) {
                self->m_bladeOwner[i].m_gauge.m_rate = 0.0f;
            }
        }
    }
}

int GfMenuReference::fn_7100367EF4(unsigned int driver) {
    if (GfMenuObjUtil::fn_710048FD30(3)) {
        GfMenuReference* self = get();
        if (self) {
            for (unsigned int i = 0; i < 3; i++) {
                if (self->m_bladeOwner[i].m_driver == driver) return self->m_bladeOwner[i].m_gauge.m_type;
            }
            return 0xFF;
        }
    }
    return -1;
}

void GfMenuReference::fn_7100367F98(float ratio) {
    if (GfMenuObjUtil::fn_710048FD30(3)) {
        GfMenuReference* self = get();
        if (self) self->m_layerRatio = ratio;
    }
}

float GfMenuReference::fn_7100367FDC() {
    if (GfMenuObjUtil::fn_710048FD30(3)) {
        GfMenuReference* self = get();
        if (self) return self->m_layerRatio;
    }
    return 0.0f;
}

void GfMenuReference::fn_7100368018(int index) {
    if (GfMenuObjUtil::fn_710048FD30(3)) {
        GfMenuReference* self = get();
        if (self) self->m_layerIndex = index;
    }
}

int GfMenuReference::fn_710036805C() {
    if (GfMenuObjUtil::fn_710048FD30(3)) {
        GfMenuReference* self = get();
        if (self) return self->m_layerIndex;
        return 0;
    }
    return 0;
}

unsigned int GfMenuReference::fn_71003680AC(unsigned int index) {
    if (GfMenuObjUtil::fn_710048FD30(3)) {
        GfMenuReference* self = get();
        if (index < 4 && self) return self->m_layerCommand[index].m_value;
        return 0;
    }
    return 0;
}

void GfMenuReference::fn_710036810C(bool flag) {
    if (GfMenuObjUtil::fn_710048FD30(3)) {
        GfMenuReference* self = get();
        if (self) {
            if (self->m_layerFlag != flag) TUnk_B60E28::fn_71003C3550(flag);
            self->m_layerFlag = flag;
        }
    }
}

bool GfMenuReference::fn_71003682D8(unsigned int index, unsigned int flag) {
    if (GfMenuObjUtil::fn_710048FD30(3)) {
        GfMenuReference* self = get();
        if (index < 4 && self) return self->m_layerCommand[index].m_flags.test(flag);
        return false;
    }
    return false;
}

void GfMenuReference::fn_7100368380(unsigned int bit, bool on) {
    if (GfMenuObjUtil::fn_710048FD30(3)) {
        GfMenuReference* self = get();
        if (self) self->m_layerBits.set(bit, on);
    }
}

bool GfMenuReference::fn_7100368418(unsigned int bit) {
    if (GfMenuObjUtil::fn_710048FD30(3)) {
        GfMenuReference* self = get();
        if (self) return self->m_layerBits.test(bit);
    }
    return false;
}

void GfMenuReference::fn_7100368498(float ratio, unsigned int index) {
    if (GfMenuObjUtil::fn_710048FD30(3)) {
        GfMenuReference* self = get();
        if (index < 2 && self) {
            float& value = self->m_layerGauge[index].m_ratio;
            value = ratio;
            if (ratio < 0.0f) {
                value = 0.0f;
            } else if (ratio > 1.0f) {
                value = 1.0f;
            }
        }
    }
}

void GfMenuReference::fn_710036851C(unsigned int index, unsigned char count) {
    if (GfMenuObjUtil::fn_710048FD30(3)) {
        GfMenuReference* self = get();
        if (index < 2 && self) self->m_layerGauge[index].m_count = count;
    }
}

void GfMenuReference::fn_7100368570(unsigned int index, bool on) {
    if (GfMenuObjUtil::fn_710048FD30(3)) {
        GfMenuReference* self = get();
        if (index < 2 && self) {
            LayerGauge& gauge = self->m_layerGauge[index];
            bool old = gauge.m_stateA;
            gauge.m_stateA = on;
            if (old != on) {
                if (index == 1) {
                    GfMenuObjPartyGauge::fn_7100456B60(on);
                } else if (index == 0) {
                    GfMenuObjPartyGauge::fn_7100456EA0(on);
                }
            }
        }
    }
}

void GfMenuReference::fn_7100368600(unsigned int index, bool on) {
    if (GfMenuObjUtil::fn_710048FD30(3)) {
        GfMenuReference* self = get();
        if (index < 2 && self) {
            LayerGauge& gauge = self->m_layerGauge[index];
            bool old = gauge.m_stateB;
            gauge.m_stateB = on;
            if (old != on) {
                if (index == 1) {
                    GfMenuObjPartyGauge::fn_7100456CB4(!on);
                } else if (index == 0) {
                    if (on) {
                        GfMenuObjPartyGauge::fn_7100456E00();
                    } else {
                        GfMenuObjPartyGauge::fn_7100456D60();
                    }
                }
            }
        }
    }
}

void GfMenuReference::fn_7100368744(unsigned int index, unsigned int gimmickId, float ratio) {
    if (GfMenuObjUtil::fn_710048FD30(3)) {
        GfMenuReference* self = get();
        if (index < 3 && self) {
            self->m_layerGimmick[index].m_gimmickId = gimmickId;
            self->m_layerGimmick[index].m_ratio = ratio;
        }
    }
}

const GfMenuReference::ComboRouteState* GfMenuReference::fn_71003689C0() {
    static ComboRouteState s_dummy;
    const ComboRouteState* state = &s_dummy;
    if (GfMenuObjUtil::fn_710048FD30(3)) {
        GfMenuReference* self = get();
        if (self) state = &self->m_comboRoute;
    }
    return state;
}

void GfMenuReference::fn_7100368A44() {
    TUnk_B63AE0::fn_7100448E58();
}

void GfMenuReference::fn_7100368A48() {
    TUnk_B63AE0::fn_7100448ED4();
}

void GfMenuReference::fn_7100368A4C(const LayerResult& result) {
    GfMenuReference* self = get();
    if (self) {
        LayerResult& current = self->m_layerResult;
        float ratio = current.m_ratio;
        current = result;
        if (current.m_number > 999) current.m_number = 999;
        for (int i = 0; i < 3; i++) {
            if (current.m_numbers[i] > 999) current.m_numbers[i] = 999;
        }
        if (current.m_ratio > 1.0f) current.m_ratio = 1.0f;
        if (result.m_ratio > ratio) TUnk_B63AE0::fn_7100448FFC();
    }
}

void GfMenuReference::fn_7100368BAC(GfMenuCallContext* context, const ResultPair& pair) {
    TUnk_B63AE0::fn_7100448F44(context, pair.m_first, pair.m_second);
}

void GfMenuReference::clearLinkList() {
    GfMenuReference* self = get();
    if (self) {
        if (self->m_enemyLinkList) self->m_enemyLinkList->clear();
        if (self->m_itemLinkList) self->m_itemLinkList->clear();
    }
}

void GfMenuReference::addEnemyLink(unsigned int enemy) {
    GfMenuReference* self = get();
    if (self && self->m_enemyLinkList) {
        MenuEnemyInfo info;
        info.m_enemyId = enemy;
        self->m_enemyLinkList->addContents(info);
    }
}

void GfMenuReference::addItemLink(const MenuItemInfo& item) {
    GfMenuReference* self = get();
    if (self && self->m_itemLinkList) self->m_itemLinkList->addContents(item);
}

GfMenuEnemyList* GfMenuReference::getEnemyLinkList() {
    GfMenuReference* self = get();
    if (self) return self->m_enemyLinkList;
    return nullptr;
}

GfMenuItemList* GfMenuReference::getItemLinkList() {
    GfMenuReference* self = get();
    if (self) return self->m_itemLinkList;
    return nullptr;
}

void GfMenuReference::setReferenceDriverID(unsigned int index, unsigned int driver) {
    if (index < 8) {
        GfMenuReference* self = get();
        if (self) self->m_referenceDriverID[index] = driver;
    }
}

void GfMenuReference::setReferenceBladeID(unsigned int index, unsigned int blade) {
    if (index < 8) {
        GfMenuReference* self = get();
        if (self) self->m_referenceBladeID[index] = blade;
    }
}

unsigned int GfMenuReference::getReferenceDriverID(unsigned int index) {
    GfMenuReference* self = get();
    if (index < 8 && self) return self->m_referenceDriverID[index];
    return 0;
}

unsigned int GfMenuReference::getReferenceBladeID(unsigned int index) {
    GfMenuReference* self = get();
    if (index < 8 && self) return self->m_referenceBladeID[index];
    return 0;
}

void GfMenuReference::setReferenceNumber(unsigned int index, int number) {
    if (index < 8) {
        GfMenuReference* self = get();
        if (self) self->m_referenceNumber[index].m_number = number;
    }
}

int GfMenuReference::getReferenceNumber(unsigned int index) {
    GfMenuReference* self = get();
    if (index < 8 && self) return self->m_referenceNumber[index].m_number;
    return 0;
}

int GfMenuReference::getReferenceNumberMin(unsigned int index) {
    GfMenuReference* self = get();
    if (index < 8 && self) return self->m_referenceNumber[index].m_min;
    return 0;
}

int GfMenuReference::getReferenceNumberMax(unsigned int index) {
    GfMenuReference* self = get();
    if (index < 8 && self) return self->m_referenceNumber[index].m_max;
    return 0;
}

void GfMenuReference::setReferenceTeamID(unsigned int team) {
    GfMenuReference* self = get();
    if (self) self->m_referenceTeamID = team > 3 ? 3 : team;
}

unsigned int GfMenuReference::getReferenceTeamID() {
    GfMenuReference* self = get();
    if (self) return self->m_referenceTeamID;
    return 0;
}

void GfMenuReference::setReferenceZoneID(unsigned int zone) {
    GfMenuReference* self = get();
    if (self) self->m_referenceZoneID = zone == 0 ? 1 : zone > 8 ? 8 : zone;
}

unsigned int GfMenuReference::getReferenceZoneID() {
    GfMenuReference* self = get();
    if (self) return self->m_referenceZoneID;
    return 0;
}

void GfMenuReference::setReferenceMissionID(unsigned int mission) {
    GfMenuReference* self = get();
    if (self) self->m_referenceMissionID = mission == 0 ? 1 : mission > 500 ? 500 : mission;
}

unsigned int GfMenuReference::getReferenceMissionID() {
    GfMenuReference* self = get();
    if (self) return self->m_referenceMissionID;
    return 0;
}

void GfMenuReference::setReferenceShopID(unsigned int shop) {
    GfMenuReference* self = get();
    if (self) self->m_referenceShopID = shop;
}

unsigned int GfMenuReference::getReferenceShopID() {
    GfMenuReference* self = get();
    if (self) return self->m_referenceShopID;
    return 0;
}

void GfMenuReference::setReferenceWorldMapID(unsigned int map) {
    GfMenuReference* self = get();
    if (self) self->m_referenceWorldMapID = map == 0 ? 1 : map > 59 ? 59 : map;
}

unsigned int GfMenuReference::getReferenceWorldMapID() {
    GfMenuReference* self = get();
    if (self) return self->m_referenceWorldMapID;
    return 0;
}

void GfMenuReference::fn_71003692E4(unsigned int mode) {
    GfMenuReference* self = get();
    if (self) self->m_challengeBattleMode = mode;
}

unsigned int GfMenuReference::fn_7100369304() {
    GfMenuReference* self = get();
    if (self) return self->m_challengeBattleMode;
    return 0;
}

void GfMenuReference::fn_710036932C(unsigned int type) {
    GfMenuReference* self = get();
    if (self) self->m_referenceItemType = type;
}

unsigned int GfMenuReference::fn_710036934C() {
    GfMenuReference* self = get();
    if (self) return self->m_referenceItemType;
    return 0;
}

void GfMenuReference::setDriverVirtualLevel(unsigned int value) {
    GfMenuReference* self = get();
    if (self) self->m_driverVirtualLevel = value;
}

unsigned int GfMenuReference::getDriverVirtualLevel() {
    GfMenuReference* self = get();
    if (self) return self->m_driverVirtualLevel;
    return 0;
}

void GfMenuReference::setDriverVirtualBladeID(unsigned int value) {
    GfMenuReference* self = get();
    if (self) self->m_driverVirtualBladeID = value;
}

unsigned int GfMenuReference::getDriverVirtualBladeID() {
    GfMenuReference* self = get();
    if (self) return self->m_driverVirtualBladeID;
    return 0;
}

void GfMenuReference::setDriverVirtualBladeSlot(unsigned int value) {
    GfMenuReference* self = get();
    if (self) self->m_driverVirtualBladeSlot = value;
}

unsigned int GfMenuReference::getDriverVirtualBladeSlot() {
    GfMenuReference* self = get();
    if (self) return self->m_driverVirtualBladeSlot;
    return 0;
}

void GfMenuReference::setDriverVirtualEquipAcc(unsigned int value) {
    GfMenuReference* self = get();
    if (self) self->m_driverVirtualEquipAcc = value;
}

unsigned int GfMenuReference::getDriverVirtualEquipAcc() {
    GfMenuReference* self = get();
    if (self) return self->m_driverVirtualEquipAcc;
    return 0;
}

void GfMenuReference::setDriverVirtualEquipAccSlot(unsigned int value) {
    GfMenuReference* self = get();
    if (self) self->m_driverVirtualEquipAccSlot = value;
}

unsigned int GfMenuReference::getDriverVirtualEquipAccSlot() {
    GfMenuReference* self = get();
    if (self) return self->m_driverVirtualEquipAccSlot;
    return 0;
}

void GfMenuReference::resetDriverAddIdeaLv() {
    GfMenuReference* self = get();
    if (self) {
        self->m_driverAddIdeaLv[0] = 0;
        self->m_driverAddIdeaLv[1] = 0;
        self->m_driverAddIdeaLv[2] = 0;
        self->m_driverAddIdeaLv[3] = 0;
    }
}

void GfMenuReference::setDriverAddIdeaLv(unsigned int index, int level) {
    if (index < 4) {
        GfMenuReference* self = get();
        if (self) self->m_driverAddIdeaLv[index] = level;
    }
}

int GfMenuReference::getDriverAddIdeaLv(unsigned int index) {
    GfMenuReference* self = get();
    if (index < 4 && self) return self->m_driverAddIdeaLv[index];
    return 0;
}

void GfMenuReference::setBladeVirtualEquipWpnChip(unsigned int value) {
    GfMenuReference* self = get();
    if (self) self->m_bladeVirtualEquipWpnChip = value;
}

unsigned int GfMenuReference::getBladeVirtualEquipWpnChip() {
    GfMenuReference* self = get();
    if (self) return self->m_bladeVirtualEquipWpnChip;
    return 0;
}

void GfMenuReference::setBladeVirtualEquipOrb(unsigned int value) {
    GfMenuReference* self = get();
    if (self) self->m_bladeVirtualEquipOrb = value;
}

unsigned int GfMenuReference::getBladeVirtualEquipOrb() {
    GfMenuReference* self = get();
    if (self) return self->m_bladeVirtualEquipOrb;
    return 0;
}

void GfMenuReference::setBladeVirtualEquipOrbSlot(unsigned int value) {
    GfMenuReference* self = get();
    if (self) self->m_bladeVirtualEquipOrbSlot = value;
}

unsigned int GfMenuReference::getBladeVirtualEquipOrbSlot() {
    GfMenuReference* self = get();
    if (self) return self->m_bladeVirtualEquipOrbSlot;
    return 0;
}

const ui::UIStr& GfMenuReference::getReferenceString(unsigned short index) {
    GfMenuReference* self = get();
    return self->m_referenceString[index];
}

void GfMenuReference::setReferenceString(ui::UIStr& text, unsigned short index) {
    get()->m_referenceString[index].copy(text);
}

void GfMenuReference::clearPartyStatusLock() {
    GfMenuReference* self = get();
    if (self) self->m_partyStatusLock = 0;
    GfMenuObjPartyStatus::lock(false);
}

}  // namespace gf
