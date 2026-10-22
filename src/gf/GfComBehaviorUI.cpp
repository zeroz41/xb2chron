#include "mm/mtl/Delegate.h"
#include "classes/gf/GfComponent.h"
#include "classes/gf/GfAllocator.h"
#include "fw/Allocator.h"
#include "gf/CallBackCache.h"
#include "gf/PluginManager.h"
#include "gf/SoundVariable.h"
#include "classes/gf/GfComBehavior.h"
#include "classes/gf/GfComAnimation.h"
#include "classes/gf/GfComAsm.h"
#include "classes/gf/EyeBlinkPlugin.h"
#include "classes/gf/GfComBehaviorUI.h"
#include "classes/fw/UpdatableObject.h"
#include "string.h"

namespace gf {

static const char* sSoundVariableNames[] = {"material", "attribute", "wall", "water_depth", "move_status"};

const char* getSoundVariableName(SoundVariable variable) {
    return sSoundVariableNames[variable];
}

// The functions below are 1.0.0's (names from its symbols); 3.0.1's linker dropped them as unused, leaving only
// their strings in this file's .rodata.

int getSoundVariable(const char* name) {
    for (int i = 0; i < 5; i++) {
        if (strcmp(name, sSoundVariableNames[i]) == 0) {
            return i;
        }
    }
    return -1;
}

static const char* sMaterialNames[] = {"MAT_NONE", "MAT_WOOD", "MAT_GRASS", "MAT_SAND", "MAT_IRON",
                                       "MAT_SNOW", "MAT_SOIL", "MAT_WIRE_MESH", "MAT_GEL", "MAT_CARPET",
                                       "MAT_WATER", "MAT_CLOUD", "MAT_ICE"};

const char* getMaterialVariableName(int value) {
    if (value > 12) {
        return "invalid";
    }
    return sMaterialNames[value];
}

int getMaterialVariable(const char* name) {
    for (int i = 0; i < 13; i++) {
        if (strcmp(sMaterialNames[i], name) == 0) {
            return i;
        }
    }
    return -1;
}

// an attribute value and its name (the names are not the original's)
struct AttributeName {
    int value;
    const char* name;
};

static const AttributeName sAttributeNames[] = {{0, "ATR_NONE"}, {1, "ATR_FIRE"},  {2, "ATR_AQUA"},
                                                {3, "ATR_WIND"}, {4, "ATR_EARTH"}, {5, "ATR_VOLT"},
                                                {6, "ATR_ICE"},  {7, "ATR_LIGHT"}, {8, "ATR_DARK"}};

const char* getAttributeVariableName(int value) {
    for (int i = 0; i < 9; i++) {
        if (sAttributeNames[i].value == value) {
            return sAttributeNames[i].name;
        }
    }
    return "invalid";
}

int getAttrbiteVariable(const char* name) {
    for (int i = 0; i < 9; i++) {
        if (strcmp(sAttributeNames[i].name, name) == 0) {
            return sAttributeNames[i].value;
        }
    }
    return -1;
}

static const char* sWallNames[] = {"WALL_NORMAL", "WALL_LADER"};

const char* getWallVariableName(SoundVariableWall value) {
    if (value < 0) {
        return "invalid";
    }
    return sWallNames[value];
}

int getWallVariable(const char* name) {
    for (int i = 0; i < 2; i++) {
        if (strcmp(sWallNames[i], name) == 0) {
            return i;
        }
    }
    return -1;
}

static const char* sWaterDepthNames[] = {"WATER_DEPTH_LOW", "WATER_DEPTH_HIGH"};

const char* getWaterDepthVariableName(SoundVariableWaterDepth value) {
    if (value < 0) {
        return "invalid";
    }
    return sWaterDepthNames[value];
}

int getWaterDepthVariable(const char* name) {
    for (int i = 0; i < 2; i++) {
        if (strcmp(sWaterDepthNames[i], name) == 0) {
            return i;
        }
    }
    return -1;
}

static const char* sMoveStatusNames[] = {"MOVE_NORMAL", "MOVE_RUN"};

const char* getMoveStatusVariableName(SoundVarMoveStatus value) {
    if (value < 0) {
        return "invalid";
    }
    return sMoveStatusNames[value];
}

int getMoveStatusVariable(const char* name) {
    for (int i = 0; i < 2; i++) {
        if (strcmp(sMoveStatusNames[i], name) == 0) {
            return i;
        }
    }
    return -1;
}

GfComBehaviorUI::GfComBehaviorUI() {}

GfComBehaviorUI::~GfComBehaviorUI() {}

void GfComBehaviorUI::setup(const SetupInfo& info) {
    GfComAsm* asmCom = m_owner->getComponent<GfComAsm>(2);
    if (asmCom != nullptr) {
        asmCom->m_callbacks[0].name = "system";
        asmCom->m_callbacks[0].delegate.set(static_cast<GfComBehavior*>(this), &GfComBehavior::callbackAnim);
    }
    m_pluginManager.beginSetup(*this, 4);
    m_pluginManager.setCreator(1, &EyeBlinkPlugin::create, info.eyeBlink);
    m_pluginManager.endSetup();
    if (EyeBlinkPlugin* eyeBlink = getPlugin<EyeBlinkPlugin>(1)) {
        eyeBlink->setActivate(true);
    }
}

void GfComBehaviorUI::cleanup() {
    m_pluginManager.cleanup();
}

void GfComBehaviorUI::update(const fw::UpdateInfo& info) {
    GfComAsm* asmCom = m_owner->getComponent<GfComAsm>(2);
    EyeBlinkPlugin* eyeBlink = getPlugin<EyeBlinkPlugin>(1);
    if (asmCom != nullptr && eyeBlink != nullptr) {
        const char* state = asmCom->getStateName(AnimLayer(0));
        bool blink = true;
        if (state != nullptr && (strcmp(state, "S_hold_00") == 0 || strcmp(state, "S_hold_01") == 0)) {
            blink = false;  // none in the hold states
        }
        eyeBlink->setActivate(blink);
    }
    m_pluginManager.update(info);
}

mm::mtl::RTTI GfComBehaviorUI::m_rtti("GfComBehaviorUI", &GfComBehavior::m_rtti, nullptr);

}  // namespace gf
