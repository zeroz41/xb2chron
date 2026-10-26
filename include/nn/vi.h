#ifndef NN_VI_H
#define NN_VI_H

#include "nn/result.h"

namespace nn { namespace vi {

// the SDK's video interface: a display (the default one) and a layer on it whose native window NVN renders to
class Display;
class Layer;
typedef void* NativeWindowHandle;
// the SDK's layer scaling: 2 is preserve aspect ratio
enum ScalingMode {};

void Initialize();
void Finalize();
Result OpenDefaultDisplay(Display** pOutDisplay);
void CloseDisplay(Display* pDisplay);
Result CreateLayer(Layer** pOutLayer, Display* pDisplay);
void DestroyLayer(Layer* pLayer);
Result SetLayerScalingMode(Layer* pLayer, ScalingMode mode);
Result GetNativeWindow(NativeWindowHandle* pOutWindow, Layer* pLayer);

}}  // namespace nn::vi

#endif
