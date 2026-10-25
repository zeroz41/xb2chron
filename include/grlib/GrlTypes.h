#ifndef GRLIB_GRLTYPES_H
#define GRLIB_GRLTYPES_H

// grlib's enumerations as its functions' symbols spell them (all global but GrlMrtType, GrlUtilVertFetch and GrlUtilSampler); no value has a name yet
enum GrlTexClamp {};
enum GrlTexMagFilterType {};
enum GrlTexMinFilterType {};
enum GrlTexTexAnisoRatio {};
enum GrlTexCompare {};
enum GrlTexBorderType {};
enum GrlPrimitiveType {};
enum GrlIndexFormat {};
enum GrlLogicType {};
enum GrlBlendFunc {};
enum GrlBlendCombine {};
enum GrlSurfaceFormat {};
enum GrlCompare {};
enum GrlStencil {};
enum GrlClaerMask {};
enum GrlTiledCacheAction {};

namespace grlib {
enum GrlMrtType {};
enum GrlUtilVertFetch {};
enum GrlUtilSampler {};
// a cube map face (0..5)
enum GrlCubeMapFace {};
}  // namespace grlib

#endif
