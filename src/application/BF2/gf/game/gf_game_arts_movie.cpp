#include "classes/gf/GfArtsMovie.h"
#include "classes/gf/GfMovieManager.h"
#include "classes/gf/GfArtsMovie.h"
#include "classes/gf/GfMovieManager.h"
#include "classes/gf/GfAllocator.h"
#include "gf/GfPlayFactory.h"
#include "mm/mtl/FixStr.h"

namespace gf {

GfArtsMovie::~GfArtsMovie() {}

void GfArtsMovie::startSetup(const char* name) {
    mm::mtl::FixStr<128> path;
    path.format("/stream/movie/%s.webm", name);
    GfMovieManager::get()->open(getAllocator(ALLOCATOR(10)));
    if (GfMovieManager::get()->set_file(path.m_str)) {
        m_waitCount = 0;
        m_state = 1;
        m_update.set(this, &GfArtsMovie::updateForSetup);
    } else {
        m_update.set(this, &GfArtsMovie::updateForMemorySafe);
    }
}

void GfArtsMovie::updateForMemorySafe(const fw::UpdateInfo& info) {
    GfMovieManager::get()->close();
    m_state = 3;
    m_update.m_invoker = nullptr;
}

void GfArtsMovie::updateForSetup(const fw::UpdateInfo& info) {
    if (GfMovieManager::get()->isstandby()) {
        m_waitCount = 0;
        GfMovieManager::get()->play();
        m_state = 2;
        m_update.set(this, &GfArtsMovie::updateForPlay);
    } else if (++m_waitCount >= 90) {
        m_update.set(this, &GfArtsMovie::updateForMemorySafe);
        m_waitCount = 0;
    }
}

void GfArtsMovie::updateForPlay(const fw::UpdateInfo& info) {
    if (!GfMovieManager::get()->isplaying()) {
        m_update.set(this, &GfArtsMovie::updateForMemorySafe);
    }
}

void GfArtsMovie::update(const fw::UpdateInfo& info) {
    if (m_update.isValid()) {
        m_update(info);
    }
}

GfArtsMovie* GfArtsMovie::createSiren() {
    if (!GfPlayFactory::createArtsMovie("bf99000001")) {
        return nullptr;
    }
    GfArtsMovie* movie = get();
    if (movie == nullptr) {
#line 116
        movie = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfArtsMovie();
    }
    return movie;
}

void GfArtsMovie::destroy() {
    if (GfArtsMovie* movie = get()) {
        delete movie;
    }
}

int GfArtsMovie::getState() const {
    return m_state;
}

void GfArtsMovie::gevPause(unsigned int, unsigned int) {}

}  // namespace gf
