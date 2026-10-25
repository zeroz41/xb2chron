#ifndef NVN_NVN_H
#define NVN_NVN_H

#include <stddef.h>

// NVN's C types as the SDK's nvn.h declares them: API objects are opaque structs of reserved bytes (the sizes are
// the SDK's), enumerations are 32-bit. Only the types the decompiled code uses are listed; no enumerator has a
// name yet.
typedef unsigned char NVNboolean;
typedef unsigned long NVNbufferAddress;
typedef unsigned long NVNtextureHandle;
typedef unsigned long NVNimageHandle;
typedef unsigned long uint64_t;

typedef enum NVNblendEquation { NVN_BLEND_EQUATION_LARGE = 0x7FFFFFFF } NVNblendEquation;
typedef enum NVNblendFunc { NVN_BLEND_FUNC_LARGE = 0x7FFFFFFF } NVNblendFunc;
typedef enum NVNdepthFunc { NVN_DEPTH_FUNC_LARGE = 0x7FFFFFFF } NVNdepthFunc;
typedef enum NVNdrawPrimitive { NVN_DRAW_PRIMITIVE_LARGE = 0x7FFFFFFF } NVNdrawPrimitive;
typedef enum NVNshaderStage { NVN_SHADER_STAGE_LARGE = 0x7FFFFFFF } NVNshaderStage;
typedef enum NVNlogicOp { NVN_LOGIC_OP_LARGE = 0x7FFFFFFF } NVNlogicOp;
typedef enum NVNsyncWaitResult { NVN_SYNC_WAIT_RESULT_LARGE = 0x7FFFFFFF } NVNsyncWaitResult;
typedef enum NVNtiledCacheAction { NVN_TILED_CACHE_ACTION_LARGE = 0x7FFFFFFF } NVNtiledCacheAction;
typedef enum NVNcounterType { NVN_COUNTER_TYPE_LARGE = 0x7FFFFFFF } NVNcounterType;

typedef struct NVNblendState { char reserved[8]; } NVNblendState;
typedef struct NVNchannelMaskState { char reserved[4]; } NVNchannelMaskState;
typedef struct NVNcolorState { char reserved[4]; } NVNcolorState;
typedef struct NVNcommandBuffer { char reserved[160]; } NVNcommandBuffer;
typedef struct NVNdevice { char reserved[12288]; } NVNdevice;
typedef struct NVNdepthStencilState { char reserved[8]; } NVNdepthStencilState;
typedef struct NVNmemoryPool { char reserved[256]; } NVNmemoryPool;
typedef struct NVNpolygonState { char reserved[4]; } NVNpolygonState;
typedef struct NVNprogram { char reserved[192]; } NVNprogram;
typedef struct NVNqueue { char reserved[8192]; } NVNqueue;
typedef struct NVNsync { char reserved[64]; } NVNsync;
typedef struct NVNtexture { char reserved[192]; } NVNtexture;
typedef struct NVNtextureView { char reserved[40]; } NVNtextureView;
typedef struct NVNvertexAttribState { char reserved[4]; } NVNvertexAttribState;
typedef struct NVNvertexStreamState { char reserved[8]; } NVNvertexStreamState;

#endif
