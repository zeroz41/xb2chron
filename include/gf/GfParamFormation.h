#ifndef GF_GFPARAMFORMATION_H
#define GF_GFPARAMFORMATION_H

#include "classes/fw/ParamList.h"
#include "classes/fw/ParamManager.h"

namespace gf {

// 1.0.0's FormationParam (its createReflection names the fields player1OffsetX, player1OffsetZ ... player5OffsetZ):
// where players 1-5 stand from the one they follow, sideways and ahead in its frame. ParamManager's list 6 holds
// one per formation (GfGamePlayerFormation::m_formation).
struct FormationParam {
    struct Offset {
        float x;
        float z;
    };
    Offset playerOffset[5];
};

// 1.0.0's WarpForRandomTalkParam (its createReflection names the fields): how far a player may be from the leader,
// up or down and across, for a random talk (list 6's entry 2)
struct WarpForRandomTalkParam {
    float distVert;
    float distHorz;
};

// 1.0.0 has copies of both (gf_game_player_formation.cpp's); 3.0.1 none, its callers inline them
inline const FormationParam* getFormationParam(unsigned int index) {
    return fw::ParamManager::get()->m_paramLists[6]->getAdapter(index).get<FormationParam>();
}
inline const WarpForRandomTalkParam* getWarpForRandomTalkParam() {
    return fw::ParamManager::get()->m_paramLists[6]->getAdapter(2).get<WarpForRandomTalkParam>();
}

}  // namespace gf

#endif
