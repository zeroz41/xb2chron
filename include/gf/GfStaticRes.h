#ifndef GF_GFSTATICRES_H
#define GF_GFSTATICRES_H

namespace fw { class CommonResource; }

namespace gf {
// the game's resident resources, loaded at start
class GfStaticRes {
public:
    // the loaded resource of that path (fw::CommonResource::search in GfStaticRes's memory), none if not loaded
    static fw::CommonResource* search(const char* path);
};
}  // namespace gf

#endif
