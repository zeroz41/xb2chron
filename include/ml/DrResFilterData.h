#ifndef ML_DRRESFILTERDATA_H
#define ML_DRRESFILTERDATA_H

namespace ml {
// DrMan::m_filterData. Only what DrIniSys::loadFilterLutTexture calls is declared.
class DrResFilterData {
public:
    // takes the data of the filter LUT file DrIniSys::loadFilterLutTexture read
    void setFilterData(const void* data);
};
}  // namespace ml

#endif
