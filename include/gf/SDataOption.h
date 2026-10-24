#ifndef GF_SDATAOPTION_H
#define GF_SDATAOPTION_H

namespace gf {
// the option settings, as GfDataManager::getDataOption hands them out (1.0.0's GfMenuObjOption::initOptionData
// takes one)
class SDataOption {
public:
    unsigned char pad_0[0x66];
    // 0..255: GfMenuManager::applyOptionData divides it by 255 for applyGammaCorrectValue (the name is not the original's)
    unsigned short m_gamma;
    // the event subtitles' option: GfMenuObjEventSubtitle shows a first line that is not vertical only when it is
    // set (the name is not the original's)
    bool m_eventSubtitle;
};
}  // namespace gf

#endif
