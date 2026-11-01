#ifndef ML_DRIRRVOLMAN_H
#define ML_DRIRRVOLMAN_H

namespace ml {
class DrMan;
namespace irrvol {
struct SGlobalInfo;
class DrIrrVolCascade;
}  // namespace irrvol

// The irradiance volume manager. Only what its destructor uses is declared; the field names are not the original's.
class DrIrrVolMan {
public:
    ~DrIrrVolMan();
    // deletes the cascades and forgets the settings (1.0.0 has it out of line; 3.0.1's destructor inlines it)
    void release();

    DrMan* m_drMan;  // 0x0, the constructor's
    const irrvol::SGlobalInfo* m_globalInfo;  // 0x8
    unsigned char pad_10[0x88];
    irrvol::DrIrrVolCascade** m_cascades;  // 0x98, m_globalInfo->m_cascadeNum of them
};
}  // namespace ml

#endif
