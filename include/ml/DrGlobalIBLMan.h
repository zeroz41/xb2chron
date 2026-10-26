#ifndef ML_DRGLOBALIBLMAN_H
#define ML_DRGLOBALIBLMAN_H
namespace ml {
class DrGlobalIBLPack;
// a view's global IBL manager (DrMan::m_iblMan): ScnObjIBLDr and DrMdoCtlSeamAll make their packs with it
class DrGlobalIBLMan {
public:
    DrGlobalIBLPack* createObj(const void* resource);
    // marks the pack for release (DrGlobalIBLPack::FLAG_RELEASE shifted by DrMan::s_nDblStockIdx)
    void releaseObj(DrGlobalIBLPack* pack);
};
}  // namespace ml
#endif
