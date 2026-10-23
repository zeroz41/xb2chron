#ifndef GF_GFASSETPATH_H
#define GF_GFASSETPATH_H

namespace gf {

// the folders an asset's files load from; each is a function-local static the setups read through (its static
// is kept in gf_asset_setup's data, so it is not a constant)
class GfAssetPath {
public:
    static const char* getMdoModel() {
        static const char* s_szMdo = "/model/";
        return s_szMdo;
    }
    static const char* getEvt() {
        static const char* s_szEvt = "/event/mot/";
        return s_szEvt;
    }
    static const char* getEff() {
        static const char* s_szEff = "/effect/";
        return s_szEff;
    }
    static const char* getStp() {
        static const char* s_szStp = "/sound/tag/trigger/";
        return s_szStp;
    }
    static const char* getSePack() {
        static const char* s_szSe = "/sound/se/";
        return s_szSe;
    }
};

}  // namespace gf

#endif
