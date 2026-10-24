#ifndef CLASSES_GMK_WEATHERCOND_H
#define CLASSES_GMK_WEATHERCOND_H

namespace gmk {
// table 0x7100B524C8; GfFieldMapGimmick::BdatInfo holds one (its row's OP_weather)
class WeatherCond {
public:
    WeatherCond() : m_weather(0xff) {}
    bool isMatch() const;
    virtual ~WeatherCond() {}  // slot 0
    unsigned char m_weather;  // the row's OP_weather, 0xFF for none (the name is not the original's)
};
}  // namespace gmk

#endif
