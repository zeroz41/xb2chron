#ifndef CLASSES_GF_GFINITPARAMENEMY_H
#define CLASSES_GF_GFINITPARAMENEMY_H

#include "classes/gf/GfInitParam.h"
#include "classes/gf/SubViewCamera.h"

namespace gf {
// table 0x7100B3FB98
class GfInitParamEnemy : public ::gf::GfInitParam {
public:
    // a setup to use instead of the factory's own (the name is not the original's). A member of each kind,
    // not of GfInitParam: the copy assignments copy it with the kind's own fields, apart from the base's
    // (GfInitParamDriver::operator=, GfObjSetupBlade's constructor)
    GfAssetSetup* m_assetSetup;
    virtual unsigned int getBladeID() const { return m_bladeId; }  // slot 1
    virtual unsigned int getEnArrangeID() const { return m_arrangeId; }  // slot 2
    void setupForEvent(unsigned int arrangeId);
    void setupBlade(const GfInitParamEnemy& param);
    void setupForUi(unsigned int arrangeId, VIEWCAM camera);

    // inline: no copy of it exists (event::ModelObj::setupModel builds one on the stack)
    GfInitParamEnemy() : GfInitParam(5), pad_90(), m_paramId(0), m_arrangeId(0), m_bladeId(0), pad_a4(0) {
        m_assetSetup = nullptr;
        pad_a8 = 0;
        pad_ac = 1;
        pad_ae = 0;
        pad_af = 0;
        pad_b0 = 0;
        m_createType = 4;
        pad_82 = 1;
    }
    unsigned char pad_90[0x98 - 0x90];
    // the enemy's CHR_EnParam row: setupForEvent and setupForUi read it from its CHR_EnArrange row (the name is not
    // the original's)
    unsigned int m_paramId;
    // the enemy's CHR_EnArrange row (setupForEvent, setupForUi; the name is not the original's)
    unsigned int m_arrangeId;
    // what getBladeID returns: setupBlade reads it from the CHR_EnArrange row (the name is not the original's)
    unsigned int m_bladeId;
    // setupForEvent: the CHR_EnParam row's resource id again
    unsigned int pad_a4;
    // setupBlade sets it to 1; createSetupParam copies it to the setup's m_actMoveId when set
    unsigned int pad_a8;
    // createSetupParam passes it to SDataEnemy's constructor
    unsigned short pad_ac;
    // GfObjFactory::createGmkEnemy stores its level offset argument here
    signed char pad_ae;
    unsigned char pad_af;
    unsigned int pad_b0;
};
}  // namespace gf

#endif
