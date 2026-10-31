#ifndef ML_DRPIXLOCCQUERY_H
#define ML_DRPIXLOCCQUERY_H

namespace ml {
class DrResQueryObj;
class DrShdDataList;
class DrShdDataObj;

// DrPixlMan's pool of occlusion queries (DrPixlMan::m_occQuery). Only createObj is declared so far: it hands out
// a free DrResQueryObj, or nullptr (DrResUseQueryObj::begin tests it).
class DrPixlOccQuery {
public:
    DrResQueryObj* createObj();

    // the fields DrPixlMan::occRenderBegin sets up (the names are not the original's)
    unsigned char pad_0[0x10];
    DrShdDataList* m_shdList;  // 0x10, occRenderBegin binds its box vertices
    DrShdDataObj* m_shader;  // 0x18, occRenderBegin sets it up (fetch 0)
    unsigned char pad_20[0x4];
    int m_uniformOfs;  // 0x24, occRenderBegin: the shader's "U_POST" block offset
    int m_renderCount;  // 0x28, occRenderBegin clears it
};
}  // namespace ml

#endif
