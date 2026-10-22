#include "classes/fw/ScriptManager.h"
#include "classes/fw/RenderResource.h"

namespace fw {

RenderResource::~RenderResource() {}

mm::mtl::FixStr<256> ScriptManager::m_rootPath("/script/jp/");

}  // namespace fw
