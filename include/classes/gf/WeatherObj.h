#ifndef CLASSES_GF_WEATHEROBJ_H
#define CLASSES_GF_WEATHEROBJ_H

namespace fw { class UpdateInfo; }
namespace gf { enum WEATYPE : int; }

namespace gf {
// table none (its derived classes')
class WeatherObj {
public:
    virtual ~WeatherObj();  // slot 0
    virtual void create(gf::WEATYPE) = 0;  // slot 2
    virtual void destroy() = 0;  // slot 3
    virtual void fadeout() = 0;  // slot 4
    virtual void update(fw::UpdateInfo const&, float, bool) = 0;  // slot 5
    virtual void isPlay() const = 0;  // slot 6
    virtual void setForceName(char const*) {}  // slot 7
};
}  // namespace gf

#endif
