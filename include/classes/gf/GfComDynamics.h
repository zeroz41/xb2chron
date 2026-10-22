#ifndef CLASSES_GF_GFCOMDYNAMICS_H
#define CLASSES_GF_GFCOMDYNAMICS_H

#include "mm/mtl/IntrusivePtr.h"
#include "mm/mtl/RTTI.h"
#include "classes/fw/DynamicsColObjUpdater.h"
#include "classes/fw/DynamicsUpdater.h"
#include "classes/fw/ForceCalculator.h"
#include "classes/gf/GfComponent.h"
namespace fw { class Message; }
namespace fw { class MessageObject; }
namespace skd { class CollisionObject; }
namespace skd { class ResDynamics; }

namespace gf {
// table 0x7100B662B0; an object's dynamics (skd's swaying bones), stepped by the DyanmicsManager on the
// object's layer, on its model's pose and frame
class GfComDynamics : public ::gf::GfComponent {
public:
    class ViewerListener {
    public:
        ViewerListener() : m_pOwner(nullptr) {}
        virtual void onWkStandbyLogout();  // slot 0 (table 0x7100B662E8)

        GfComDynamics* m_pOwner;  // (the name is not the original's)
    };
    // what setup makes the dynamics from (the field names are not the original's)
    struct SetupInfo {
        skd::ResDynamics* res;  // none: setup does nothing
        skd::CollisionObject* colObj;  // none: setup makes one from the resource and updates it itself
        mm::mtl::IntrusivePtr<fw::ForceCalculator> force;  // none: a wind one when the object has a GfComWind
        int level;  // the dynamics' value at 0x188: its maker's default 6, 30 when asked
    };

    GfComDynamics();
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfComDynamics();  // slot 1
    virtual void changeLayer(unsigned int, unsigned int);  // slot 3
    virtual bool recieveMessage(fw::MessageObject*, fw::Message&);  // slot 4
    void setup(const SetupInfo& info);
    void applyAttribute();
    void cleanup();
    void resetMovement();
    unsigned int getSolverCount() const;
    void setSolverBlendWeight(unsigned int index, float weight);
    static mm::mtl::RTTI m_rtti;

    // (the field names are not the original's)
    fw::DynamicsUpdater m_updater;
    fw::DynamicsColObjUpdater m_colUpdater;  // bound only to a collision object setup made itself
    mm::mtl::IntrusivePtr<fw::ForceCalculator> m_force;
    int m_level;  // the setup info's; applyAttribute uses 30 instead when m_forceHighLevel is set
    bool m_forceHighLevel;
    ViewerListener m_viewerListener;
    void* m_pViewer;  // the viewer listener's onWkStandbyLogout clears it
};
}  // namespace gf

#endif
