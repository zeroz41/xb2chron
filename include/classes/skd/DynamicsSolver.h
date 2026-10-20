#ifndef CLASSES_SKD_DYNAMICSSOLVER_H
#define CLASSES_SKD_DYNAMICSSOLVER_H

namespace anm { class ThreadPool; }
namespace skd { class CollionArray; }
namespace skd { class Packet; }

namespace skd {
// table 0x7100B81688
class DynamicsSolver {
public:
    virtual ~DynamicsSolver();  // slot 0
    virtual void solve(float, skd::CollionArray const&, skd::Packet const&);  // slot 2
    virtual void solveMT(float, skd::CollionArray const&, skd::Packet const&, anm::ThreadPool&);  // slot 3
};
}  // namespace skd

#endif
