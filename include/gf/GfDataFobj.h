#ifndef GF_GFDATAFOBJ_H
#define GF_GFDATAFOBJ_H


namespace gf {

// the field objects' data helpers (functions; 2.0.0's symbols name the class)
class GfDataFobj {
public:
    // 2.0.0's symbols name it. What it does: the "mdo" string of the row of RSC_dropitemListIra (while
    // GfDataUtil::isIra's flag is set) or RSC_dropitemList, "" when there is none; GfObjUtil::addDebugName uses it.
    static const char* getFobjModelName(unsigned int id);
};

}  // namespace gf

#endif
