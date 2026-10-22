#ifndef GF_GFOBJFACTORY_H
#define GF_GFOBJFACTORY_H

namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class GfInitParamDriver; }

namespace gf {
// makes the game's objects (functions, by its symbols)
class GfObjFactory {
public:
    // the driver object param describes, -1 when none is made
    static GF_OBJ_HANDLE* createDriver(GfInitParamDriver& param);
};
}  // namespace gf

#endif
