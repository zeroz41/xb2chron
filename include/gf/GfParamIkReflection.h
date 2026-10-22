#ifndef GF_GFPARAMIKREFLECTION_H
#define GF_GFPARAMIKREFLECTION_H

namespace gf {

// the game's param lists built from the resident param archives (GfManager::initialize)
void createGfParameter();
// and released (GfManager::finalize)
void destroyGfParameter();

}  // namespace gf

#endif
