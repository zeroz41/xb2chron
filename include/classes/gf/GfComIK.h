#ifndef CLASSES_GF_GFCOMIK_H
#define CLASSES_GF_GFCOMIK_H

#include "mm/mtl/RTTI.h"
#include "mm/mtl/IntrusivePtr.h"
#include "mm/mtl/Vector.h"
#include "classes/fw/IkSolver.h"
#include "classes/gf/GfComponent.h"
namespace fw { class Message; }
namespace fw { class MessageObject; }

namespace gf {
// table 0x7100B66300; a component (its m_rtti's base)
class GfComIK : public ::gf::GfComponent {
public:
    class FootGround;
    class Ground;
    class ViewerListener;
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfComIK();  // slot 1
    virtual void changeLayer(unsigned int, unsigned int);  // slot 3
    virtual bool recieveMessage(fw::MessageObject*, fw::Message&);  // slot 4

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

    unsigned char pad_10[0x10];
    mm::mtl::Vector<mm::mtl::IntrusivePtr<fw::IkSolver> > m_solvers;  // the create*IK functions fill it
};
}  // namespace gf

#endif
