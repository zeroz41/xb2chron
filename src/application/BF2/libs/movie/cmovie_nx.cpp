#include "arc/CArcData.h"
#include "classes/StreamReader.h"
#include "classes/CMovieNX/CMovie.h"
#include "classes/MovieDecoderPlayer.h"
#include "classes/mm/mtl/IAllocator.h"
#include "mtl/MemManager.h"
#include "nn/os.h"
#include "mm/mtl/Hash.h"
#include <string.h>

namespace arc {

CArcData::CArcData(void* data) : m_data(nullptr), m_contents(nullptr) {
    setData(data);
}

void CArcData::setData(void* data) {
    if (data != nullptr) {
        m_data = static_cast<Header*>(data);
        m_contents = reinterpret_cast<File*>(reinterpret_cast<char*>(data) + m_data->m_contentsOffset);
    }
}

unsigned int CArcData::getFiles() const {
    if (m_data == nullptr) {
        return 0;
    }
    return m_data->m_files;
}

const char* CArcData::getStr() const {
    if (m_data == nullptr) {
        return "";
    }
    return m_data->m_str;
}

void* CArcData::getFileAdr(unsigned int index) const {
    if (m_data == nullptr) {
        return nullptr;
    }
    if (index >= m_data->m_files) {
        return nullptr;
    }
    if (m_contents[index].m_size == 0) {
        return nullptr;
    }
    return reinterpret_cast<char*>(m_data) + m_contents[index].m_offset;
}

void* CArcData::getFileAdr(const char* name) const {
    int index = find(name);
    if (index == -1) {
        return nullptr;
    }
    return getFileAdr(static_cast<unsigned int>(index));
}

int CArcData::find(const char* name) const {
    if (name == nullptr || m_data == nullptr) {
        return -1;
    }
    if (m_data->m_version >= 0x102) {
        unsigned int hash = mm::mtl::hashStrCrc(name);
        int lo = 0;
        int hi = getFiles();
        while (lo <= hi) {
            int mid = (lo + hi) >> 1;
            const File& file = m_contents[mid];
            if (hash == file.m_hash) {
                int cmp = strcmp(name, file.m_name);
                if (cmp == 0) {
                    return mid;
                }
                if (cmp > 0) {
                    lo = mid + 1;
                } else {
                    hi = mid - 1;
                }
            } else if (hash > file.m_hash) {
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }
    } else {
        unsigned int files = m_data->m_files;
        for (unsigned int i = 0; i < files; i++) {
            if (strcmp(getFileName(i), name) == 0) {
                return i;
            }
        }
    }
    return -1;
}

unsigned int CArcData::getFileSize(unsigned int index) const {
    if (m_data == nullptr) {
        return 0;
    }
    if (index >= m_data->m_files) {
        return 0;
    }
    return m_contents[index].m_size;
}

const char* CArcData::getFileName(unsigned int index) const {
    if (m_data == nullptr) {
        return "";
    }
    if (index >= m_data->m_files) {
        return "";
    }
    return m_contents[index].m_name;
}

}  // namespace arc

StreamReader::~StreamReader() {}

bool StreamReader::Open(char const* path, void** handle) {
    m_fileHandle = new nn::fs::FileHandle;
    m_fileHandle->handle = nullptr;
    if (nn::fs::OpenFile(m_fileHandle, path, nn::fs::OpenMode_Read).IsFailure()) {
        return false;
    }
    *handle = m_fileHandle;
    nn::fs::GetFileSize(&m_fileSize, *m_fileHandle);
    return true;
}

unsigned long StreamReader::ReadAt(void* handle, long offset, void* buffer, unsigned long size) {
    unsigned long readSize = 0;
    nn::fs::FileHandle* fileHandle = static_cast<nn::fs::FileHandle*>(handle);
    if (fileHandle->handle != m_fileHandle->handle) {
        return 0;
    }
    nn::fs::ReadFile(&readSize, *fileHandle, offset, buffer, size);
    return readSize;
}

bool StreamReader::Close(void* handle) {
    nn::fs::FileHandle* fileHandle = static_cast<nn::fs::FileHandle*>(handle);
    if (fileHandle->handle != m_fileHandle->handle) {
        return false;
    }
    nn::fs::CloseFile(*fileHandle);
    delete m_fileHandle;
    return true;
}

void StreamReader::GetSize(void* handle, long* size) {
    nn::fs::FileHandle* fileHandle = static_cast<nn::fs::FileHandle*>(handle);
    if (fileHandle->handle == m_fileHandle->handle) {
        *size = m_fileSize;
    }
}

// Proposed names, not the original's: the symbols leave them unnamed (lbl_7100EB7E10, lbl_7100EB7E14)
static bool s_pause;
static bool s_homeMenu;

void AudioOutRendererThreadFunction(void* arg) {
    AudioOutRenderer* renderer = static_cast<AudioOutRenderer*>(arg);
    while (!renderer->m_exit) {
        if (renderer->m_started && !s_pause && !s_homeMenu) {
            renderer->Render();
        }
        nn::os::SleepThread(nn::TimeSpan::FromMilliSeconds(renderer->m_sleepMs));
    }
}

void AudioOutRenderer::OnOutputAvailable(int index, long presentationTimeUs, unsigned int flags) {
    audioData data;
    data.m_index = index;
    data.m_presentationTimeUs = presentationTimeUs;
    data.m_flags = flags;
    nn::os::LockMutex(&m_outputMutex);
    m_outputBuffers.push_back(data);
    nn::os::UnlockMutex(&m_outputMutex);
    GenerateFixedSizeAudioFrame();
    if (m_startTimeUs == -1) {
        MediaClock* clock = m_mediaClock;
        nn::os::LockMutex(&clock->m_mutex);
        clock->m_anchorTimeUs = presentationTimeUs;
        nn::os::UnlockMutex(&clock->m_mutex);
        m_startTimeUs = presentationTimeUs;
    }
}

void* MultimediaAllocate(unsigned long size, unsigned long alignment, void* userPtr) {
    CMovieNX::CMovie* movie = static_cast<CMovieNX::CMovie*>(ICMovie::get());
    if (movie == nullptr) {
        return nullptr;
    }
    return movie->m_allocator->allocate(size, alignment);
}

void MultimediaFree(void* address, void* userPtr) {
    CMovieNX::CMovie* movie = static_cast<CMovieNX::CMovie*>(ICMovie::get());
    if (movie == nullptr) {
        return;
    }
    movie->m_allocator->deallocate(address);
}

void* MultimediaReallocate(void* address, unsigned long size, void* userPtr) {
    return mtl::MemManager::reallocate(address, size, false);
}

void VideoInputReadThreadFunction(void* arg) {
    MovieDecoderPlayer* player = static_cast<MovieDecoderPlayer*>(arg);
    for (;;) {
        unsigned long message;
        nn::os::ReceiveMessageQueue(&message, &player->m_videoInputQueue);
        if (message == 1) {
            player->CheckForInputBuffersAndReadVideoInputData();
        } else if (message == 2) {
            break;
        }
    }
    player->m_videoInputThreadDone = true;
}

void AudioInputReadThreadFunction(void* arg) {
    MovieDecoderPlayer* player = static_cast<MovieDecoderPlayer*>(arg);
    for (;;) {
        unsigned long message;
        nn::os::ReceiveMessageQueue(&message, &player->m_audioInputQueue);
        if (message == 3) {
            player->CheckForInputBuffersAndReadAudioInputData();
        } else if (message == 4) {
            break;
        }
    }
    player->m_audioInputThreadDone = true;
}

namespace CMovieNX {

void CMovie::finalize() {
    if (m_frame != nullptr) {
        m_allocator->deallocate(m_frame);
        m_frame = nullptr;
    }
}

float CMovie::get_length() {
    return 0.0f;
}

float CMovie::pos() {
    return 0.0f;
}

void CMovie::play() {
    if (s_pause == true) {
        s_pause = false;
    }
}

void CMovie::pause() {
    if (!s_pause) {
        s_pause = true;
    }
}

bool CMovie::isstandby() {
    if (m_player == nullptr) {
        return false;
    }
    if (m_player->m_videoRenderer == nullptr) {
        return false;
    }
    return m_player->m_videoRenderer->m_started;
}

bool CMovie::ispause() {
    return s_pause;
}

bool CMovie::isplaying() {
    MovieDecoderPlayer* player = m_player;
    if (player == nullptr) {
        return false;
    }
    bool audioDone = player->m_audioOutRenderer != nullptr ? player->m_audioOutRenderer->m_eos : true;
    bool videoDone = player->m_videoRenderer != nullptr ? player->m_videoRenderer->m_eos : true;
    if (videoDone && audioDone) {
        player->m_done = true;
    }
    return !player->m_done;
}

void CMovie::doHomeMenu(bool homeMenu) {
    s_homeMenu = homeMenu;
}

}  // namespace CMovieNX
