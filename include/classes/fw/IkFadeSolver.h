#ifndef CLASSES_FW_IKFADESOLVER_H
#define CLASSES_FW_IKFADESOLVER_H

#include "mm/mtl/RTTI.h"
#include "classes/fw/IkSolver.h"
namespace fw { class UpdateInfo; }

namespace fw {
// table 0x7100B41BA8; its destructor adds nothing to IkSolver's, so clang emits IkSolver's in its place (slot 0)
class IkFadeSolver : public ::fw::IkSolver {
public:
    IkFadeSolver();
    virtual ~IkFadeSolver() {}  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual void solve(fw::UpdateInfo const&);  // slot 3
    virtual bool isEnable() const { return m_weight > 0.0f; }  // slot 4
    virtual void onEnable() {}  // slot 5
    virtual void onDisable() {}  // slot 6
    virtual void calcIK(fw::UpdateInfo const&) = 0;  // slot 7
    static mm::mtl::RTTI m_rtti;

    float m_weight;  // solve fades it to 1 or to 0; isEnable while above 0; calcIK scales its effect by it
    unsigned char pad_24[0x10];
};
}  // namespace fw

#endif
