#ifndef GF_GFDATANPC_H
#define GF_GFDATANPC_H

namespace gf {
// the NPCs' data, by their row id (functions, by its symbols)
class GfDataNpc {
public:
    static const char* getName(unsigned int npc);
    // the message table and row of the NPC's name
    static bool getName(unsigned char*& bdat, unsigned int& id, unsigned int npc);
    static const char* getModelName(unsigned int npc);
    // the BDAT file of the NPC's resources (GfObjFactory::createGmkNpc passes its row's "NpcID")
    static unsigned char* getRscBdatFp(int npc);
    static const char* getMotionName(unsigned int npc);
    static const char* getEffectName(unsigned int npc);
    static bool isNeedResourceEvent(unsigned int npc);
    static int getOffsetID(unsigned int npc);  // its menu offset id
    static bool getExtraParts(unsigned int npc, unsigned int part);
    static unsigned int getFootStep(unsigned int npc);
    static unsigned int getFootStepEffect(unsigned int npc);
    static unsigned int getEyeRotControl(unsigned int npc);
    static unsigned int getRace(unsigned int npc);
    static unsigned int getGender(unsigned int npc);
    static float getScale(unsigned int npc);
    static unsigned int getCollisionId(unsigned int npc);
    static const char* getAddMotionName(unsigned int npc);
};
}  // namespace gf

#endif
