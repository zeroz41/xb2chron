#ifndef CLASSES_FW_IKFADESOLVER_H
#define CLASSES_FW_IKFADESOLVER_H

#include "mm/mtl/RTTI.h"
namespace fw { class UpdateInfo; }

namespace fw {
// table 0x7100B41BA8
class IkFadeSolver {
public:
    virtual ~IkFadeSolver();  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual void solve(fw::UpdateInfo const&);  // slot 3
    virtual void isEnable() const;  // slot 4
    virtual void onEnable();  // slot 5
    virtual void onDisable();  // slot 6
    virtual void calcIK(fw::UpdateInfo const&) = 0;  // slot 7
    static mm::mtl::RTTI m_rtti;
};
}  // namespace fw

#endif
