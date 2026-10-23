#ifndef CLASSES_GF_GFCOMIK_H
#define CLASSES_GF_GFCOMIK_H

#include "mm/mtl/RTTI.h"
#include "mm/mtl/IntrusivePtr.h"
#include "mm/mtl/UniquePtr.h"
#include "mm/mtl/Vector.h"
#include "classes/fw/IkSolver.h"
#include "classes/gf/GfComponent.h"
#include "fw/IkResolver.h"  // the tree: "fw/IkResolver.h" (new)
namespace fw { class Message; }
namespace fw { class MessageObject; }

namespace gf {
// table 0x7100B66300; a component (its m_rtti's base), and the IK resolver AnimationManager runs on its layer
class GfComIK : public ::gf::GfComponent, public ::fw::IkResolver {
public:
    class FootGround;
    class Ground;
    class ViewerListener {
    public:
        ViewerListener() : m_pOwner(nullptr) {}
        virtual void onWkStandbyLogout();  // slot 0 (table 0x7100B66338)

        GfComIK* m_pOwner;  // (the name is not the original's)
    };
    // what setup is given (its contents are not known: 3.0.1's setup reads none of it)
    struct SetupInfo {};

    GfComIK();
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfComIK();  // slot 1
    virtual void changeLayer(unsigned int, unsigned int);  // slot 3
    virtual bool recieveMessage(fw::MessageObject*, fw::Message&);  // slot 4
    void setup(const SetupInfo& info);
    void cleanup();

    // the solver at an index as a T, none when the index holds none or another kind (inline: the name is not the
    // original's; FootIkControllerPlugin finds the slope solver at 0, the placement or two-chara one at 2)
    template <typename T>
    T* getSolver(size_t index) const {
        fw::IkSolver* solver = m_solvers[index].get();
        if (solver == nullptr) {
            return nullptr;
        }
        return solver->getRTTI()->isKindOf(&T::m_rtti) ? static_cast<T*>(solver) : nullptr;
    }

    static mm::mtl::RTTI m_rtti;

    mm::mtl::Vector<mm::mtl::IntrusivePtr<fw::IkSolver> > m_solvers;  // the create*IK functions fill it
    // (the names below are not the original's)
    mm::mtl::UniquePtr<Ground> m_ground;  // setup makes it when the object's property has ground data
    unsigned int m_footCount;             // setup's: 6, 4, 2 or 0 by the foot labels the model's skeleton has
    ViewerListener m_viewerListener;
    void* m_pViewer;  // the viewer listener's onWkStandbyLogout clears it
};
}  // namespace gf

#endif
