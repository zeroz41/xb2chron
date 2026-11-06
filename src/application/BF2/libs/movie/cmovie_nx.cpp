#include "arc/CArcData.h"
#include "classes/StreamReader.h"
#include "classes/CMovieNX/CMovie.h"
#include "classes/MovieDecoderPlayer.h"
#include "classes/mm/mtl/IAllocator.h"
#include "mtl/MemManager.h"
#include "nn/os.h"
#include "mm/mtl/Hash.h"
#include <math.h>
#include <stdlib.h>
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

AudioOutRenderer::~AudioOutRenderer() {}

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

int AudioOutRenderer::Finalize() {
    nn::os::FinalizeMutex(&m_outputMutex);
    if (m_threadStack != nullptr) {
        MultimediaFree(m_threadStack, nullptr);
    }
    for (int i = 0; i < 3; i++) {
        if (m_audioOutBufferData[i] != nullptr) {
            MultimediaFree(m_audioOutBufferData[i], nullptr);
            m_audioOutBufferData[i] = nullptr;
        }
    }
    if (m_pcmBuffer != nullptr) {
        MultimediaFree(m_pcmBuffer, nullptr);
        m_pcmBuffer = nullptr;
    }
    if (m_frameBuffer != nullptr) {
        delete m_frameBuffer;
        m_frameBuffer = nullptr;
    }
    m_outputBuffers.clear();
    m_emptyBuffers.clear();
    m_filledBuffers.clear();
    return 0;
}

int AudioOutRenderer::Start() {
    m_startRealTimeUs = -1;
    MediaClock* clock = m_mediaClock;
    nn::os::LockMutex(&clock->m_mutex);
    clock->m_anchorTimeUs = -1;
    nn::os::UnlockMutex(&clock->m_mutex);
    int channelCount = nn::audio::GetAudioOutChannelCount(&m_audioOut);
    int sampleRate = nn::audio::GetAudioOutSampleRate(&m_audioOut);
    nn::audio::SampleFormat sampleFormat = nn::audio::GetAudioOutSampleFormat(&m_audioOut);
    for (int i = 0; i < 3; i++) {
        m_audioOutBufferData[i] = MultimediaAllocate(m_audioOutBufferSize, 0x1000, nullptr);
        memset(m_audioOutBufferData[i], 0, 0x400);
        nn::audio::SetAudioOutBufferInfo(&m_audioOutBuffers[i], m_audioOutBufferData[i], m_audioOutBufferSize, 0x400);
        nn::audio::AppendAudioOutBuffer(&m_audioOut, &m_audioOutBuffers[i]);
    }
    int status;
    if (nn::audio::StartAudioOut(&m_audioOut).IsSuccess()) {
        status = 0;
        m_started = true;
    } else {
        status = 0x1000;
    }
    nn::os::StartThread(&m_thread);
    m_threadStarted = true;
    return status;
}

int AudioOutRenderer::Render() {
    GenerateFixedSizeAudioFrame();
    nn::os::LockMutex(&m_outputMutex);
    if (m_filledBuffers.size() == 0) {
        nn::os::UnlockMutex(&m_outputMutex);
        return 0;
    }
    movie::Buffer* buffer = &m_filledBuffers.front();
    short* data = static_cast<short*>(buffer->Base());
    int size = buffer->Size();
    unsigned int flags = buffer->GetUint32Data();
    long presentationTimeUs = buffer->GetInt64Data();
    void* base = buffer->Base();
    unsigned long capacity = buffer->Capacity();
    nn::os::UnlockMutex(&m_outputMutex);
    if (data == nullptr || size == 0) {
        if (flags == 4) {
            m_eos = true;
        }
        return 0;
    }
    nn::audio::AudioOutBuffer* outBuffer = nn::audio::GetReleasedAudioOutBuffer(&m_audioOut);
    if (outBuffer == nullptr) {
        return 0;
    }
    short* out = static_cast<short*>(nn::audio::GetAudioOutBufferDataPointer(outBuffer));
    nn::audio::GetAudioOutBufferDataSize(outBuffer);
    m_presentationTimeUs = presentationTimeUs;
    if (m_startTimeUs >= 0 && m_mediaClock != nullptr) {
        long nowUs = nn::os::ConvertToTimeSpan(nn::os::GetSystemTick()).GetMicroSeconds();
        long startTimeUs = m_startTimeUs;
        if (m_startRealTimeUs == -1) {
            m_startRealTimeUs = nowUs;
        }
        long elapsedUs = nowUs - m_startRealTimeUs;
        long playedUs = m_playedFrames * 1000000 / m_sampleRate;
        if (elapsedUs <= playedUs) {
            playedUs = elapsedUs;
        }
        m_mediaClock->updateAnchor(startTimeUs + playedUs, nowUs, m_presentationTimeUs);
        if (m_startRealTimeUs == -1) {
            m_startRealTimeUs = nn::os::ConvertToTimeSpan(nn::os::GetSystemTick()).GetMicroSeconds();
            m_mediaClock->setStartingTimeMedia(m_startTimeUs);
        }
    }
    unsigned long outSize = size;
    if (m_decoderChannelCount < m_channelCount) {
        int samples = outSize / 2;
        short* dst = out;
        for (int i = 0; i < samples; i++) {
            short sample = data[i];
            for (int c = 0; c < m_channelCount; c++) {
                *dst++ = sample;
            }
        }
        outSize = m_channelCount * outSize;
    } else {
        memcpy(out, data, outSize);
    }
    m_playedFrames += outSize / m_bytesPerSample;
    int durationMs = outSize * 1000 / m_bytesPerSample / m_sampleRate;
    m_sleepMs = durationMs / static_cast<int>(ceil(durationMs / 8.3333));
    nn::audio::SetAudioOutBufferInfo(outBuffer, out, m_audioOutBufferSize, outSize);
    nn::audio::AppendAudioOutBuffer(&m_audioOut, outBuffer);
    if (flags == 4) {
        m_eos = true;
    }
    movie::Buffer emptyBuffer(base, capacity);
    nn::os::LockMutex(&m_outputMutex);
    m_emptyBuffers.push_back(emptyBuffer);
    m_filledBuffers.erase(m_filledBuffers.begin());
    nn::os::UnlockMutex(&m_outputMutex);
    return 0;
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

void VideoRendererThreadFunction(void* arg) {
    VideoRenderer* renderer = static_cast<VideoRenderer*>(arg);
    while (!renderer->m_exit) {
        bool render = !renderer->m_started || (!s_pause && !s_homeMenu);
        if (render) {
            renderer->Render();
        }
        if (renderer->m_sleepUs < 2000) {
            renderer->m_sleepUs = 2000;
        } else if (renderer->m_sleepUs > 300000) {
            renderer->m_sleepUs = 300000;
        }
        nn::os::SleepThread(nn::TimeSpan::FromMicroSeconds(renderer->m_sleepUs));
    }
}

bool VideoRenderer::AVSync(long presentationTimeUs) {
    m_presentationTimeUs = presentationTimeUs;
    if (m_firstFrame) {
        m_firstFrame = false;
        m_startRealTimeUs = nn::os::ConvertToTimeSpan(nn::os::GetSystemTick()).GetMicroSeconds();
        m_mediaClock->updateAnchor(m_presentationTimeUs, m_startRealTimeUs, 0x7FFFFFFFFFFFFFFF);
    }
    long nowUs = nn::os::ConvertToTimeSpan(nn::os::GetSystemTick()).GetMicroSeconds();
    long lateUs = nowUs - GetRealTimeUs(m_presentationTimeUs, nowUs);
    m_lastPresentationTimeUs = m_presentationTimeUs;
    m_sleepUs = -lateUs;
    bool drop = false;
    if (lateUs > 40000) {
        m_droppedFrames++;
        drop = true;
    }
    if (lateUs > 0) {
        m_sleepUs = 0;
    }
    return drop;
}

long VideoRenderer::GetRealTimeUs(long mediaTimeUs, long nowUs) {
    long realUs;
    if (m_mediaClock->getRealTimeFor(mediaTimeUs, &realUs) != 0) {
        realUs = nowUs + (mediaTimeUs - m_lastPresentationTimeUs);
    }
    return realUs;
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

int MovieDecoderPlayer::Initialize(unsigned long coreMask) {
    movie::SetAllocator(MultimediaAllocate, MultimediaFree, MultimediaReallocate, nullptr);
    m_inputEos = false;
    m_loopCount = 0;
    m_inputQueueSize = 0x80;
    m_done = false;
    m_clearedLong1 = 0;
    m_clearedLong0 = 0;
    if (coreMask != 0) {
        movie::SetCoreMask(coreMask);
    }
    nn::os::InitializeEvent(&m_workerExitEvent, false, nn::os::EventClearMode_ManualClear);
    nn::os::InitializeMultiWaitHolder(&m_workerExitHolder, &m_workerExitEvent);
    nn::os::InitializeMultiWait(&m_multiWait);

    // per decoder, one event set and then its holders: the original computes each set's start address ahead of the
    // set's first call (an inlined helper's argument); the helpers' names are inferred
    auto initializeEvents = [](DecoderEventTypes* types, DecoderEvents* events) {
        nn::os::InitializeEvent(&types->m_errorEvent, false, nn::os::EventClearMode_ManualClear);
        nn::os::InitializeEvent(&types->m_formatChangedEvent, false, nn::os::EventClearMode_ManualClear);
        nn::os::InitializeEvent(&types->m_inputBufferAvailableEvent, false, nn::os::EventClearMode_ManualClear);
        nn::os::InitializeEvent(&types->m_outputBufferAvailableEvent, false, nn::os::EventClearMode_ManualClear);
        events->m_errorEvent = &types->m_errorEvent;
        events->m_formatChangedEvent = &types->m_formatChangedEvent;
        events->m_inputBufferAvailableEvent = &types->m_inputBufferAvailableEvent;
        events->m_outputBufferAvailableEvent = &types->m_outputBufferAvailableEvent;
    };
    auto initializeHolders = [](DecoderMultiWaitHolders* holders, DecoderEventTypes* types) {
        nn::os::InitializeMultiWaitHolder(&holders->m_errorHolder, &types->m_errorEvent);
        nn::os::InitializeMultiWaitHolder(&holders->m_formatChangedHolder, &types->m_formatChangedEvent);
        nn::os::InitializeMultiWaitHolder(&holders->m_inputBufferAvailableHolder, &types->m_inputBufferAvailableEvent);
        nn::os::InitializeMultiWaitHolder(&holders->m_outputBufferAvailableHolder, &types->m_outputBufferAvailableEvent);
    };
    initializeEvents(&m_audioDecoderEventTypes, &m_audioDecoderEvents);
    initializeHolders(&m_audioDecoderHolders, &m_audioDecoderEventTypes);
    initializeEvents(&m_videoDecoderEventTypes, &m_videoDecoderEvents);
    initializeHolders(&m_videoDecoderHolders, &m_videoDecoderEventTypes);

    m_videoInputQueueBuffer =
        static_cast<unsigned long*>(MultimediaAllocate(m_inputQueueSize * sizeof(unsigned long), 0x1000, nullptr));
    if (m_videoInputQueueBuffer == nullptr) {
        return 0x1002;
    }
    m_audioInputQueueBuffer =
        static_cast<unsigned long*>(MultimediaAllocate(m_inputQueueSize * sizeof(unsigned long), 0x1000, nullptr));
    if (m_audioInputQueueBuffer == nullptr) {
        return 0x1002;
    }
    nn::os::InitializeMessageQueue(&m_videoInputQueue, m_videoInputQueueBuffer, m_inputQueueSize);
    nn::os::InitializeMessageQueue(&m_audioInputQueue, m_audioInputQueueBuffer, m_inputQueueSize);

    int status = 0x1002;
    m_videoInputThreadStack = aligned_alloc(0x1000, m_threadStackSize);
    if (m_videoInputThreadStack != nullptr) {
        m_videoInputThreadDone = false;
        if (nn::os::CreateThread(&m_videoInputThread, VideoInputReadThreadFunction, this, m_videoInputThreadStack,
                                 m_threadStackSize, 15)
                .IsFailure()) {
            status = 0x100D;
        } else {
            nn::os::SetThreadName(&m_videoInputThread, "VideoInputReadThread");
            m_videoInputThreadCreated = true;
            m_audioInputThreadStack = aligned_alloc(0x1000, m_threadStackSize);
            if (m_audioInputThreadStack != nullptr) {
                m_audioInputThreadDone = false;
                if (nn::os::CreateThread(&m_audioInputThread, AudioInputReadThreadFunction, this,
                                         m_audioInputThreadStack, m_threadStackSize, 15)
                        .IsFailure()) {
                    status = 0x100D;
                } else {
                    nn::os::SetThreadName(&m_audioInputThread, "AudioInputReadThread");
                    m_audioInputThreadCreated = true;
                    m_workerThreadStack = aligned_alloc(0x1000, m_threadStackSize);
                    if (m_workerThreadStack != nullptr) {
                        m_workerThreadDone = false;
                        if (nn::os::CreateThread(&m_workerThread, AudioVideoWorkerThreadFunction, this,
                                                 m_workerThreadStack, m_threadStackSize, 15)
                                .IsFailure()) {
                            status = 0x100D;
                        } else {
                            nn::os::SetThreadName(&m_workerThread, "AudioVideoWorkerThread");
                            status = 0;
                            m_workerThreadCreated = true;
                        }
                    }
                }
            }
        }
    }
    m_mediaClock = new MediaClock();
    return status;
}

void MovieDecoderPlayer::Finalize() {
    if (m_workerThreadCreated) {
        m_workerThreadDone = true;
        nn::os::SignalEvent(&m_workerExitEvent);
        nn::os::WaitThread(&m_workerThread);
        nn::os::DestroyThread(&m_workerThread);
        m_workerThreadCreated = false;
    }
    if (m_workerThreadStack != nullptr) {
        MultimediaFree(m_workerThreadStack, nullptr);
        m_workerThreadStack = nullptr;
    }
    if (m_videoInputThreadStack != nullptr) {
        MultimediaFree(m_videoInputThreadStack, nullptr);
        m_videoInputThreadStack = nullptr;
    }
    if (m_audioInputThreadStack != nullptr) {
        MultimediaFree(m_audioInputThreadStack, nullptr);
        m_audioInputThreadStack = nullptr;
    }
    nn::os::FinalizeEvent(&m_workerExitEvent);
    // per decoder (video first), as in Initialize: inlined helpers, names inferred
    auto finalizeEvents = [](DecoderEventTypes* types) {
        nn::os::FinalizeEvent(&types->m_errorEvent);
        nn::os::FinalizeEvent(&types->m_formatChangedEvent);
        nn::os::FinalizeEvent(&types->m_inputBufferAvailableEvent);
        nn::os::FinalizeEvent(&types->m_outputBufferAvailableEvent);
    };
    auto finalizeHolders = [](DecoderMultiWaitHolders* holders) {
        nn::os::FinalizeMultiWaitHolder(&holders->m_errorHolder);
        nn::os::FinalizeMultiWaitHolder(&holders->m_formatChangedHolder);
        nn::os::FinalizeMultiWaitHolder(&holders->m_inputBufferAvailableHolder);
        nn::os::FinalizeMultiWaitHolder(&holders->m_outputBufferAvailableHolder);
    };
    finalizeEvents(&m_videoDecoderEventTypes);
    finalizeHolders(&m_videoDecoderHolders);
    finalizeEvents(&m_audioDecoderEventTypes);
    finalizeHolders(&m_audioDecoderHolders);
    nn::os::FinalizeMultiWait(&m_multiWait);
    nn::os::FinalizeMutex(&m_videoInputMutex);
    nn::os::FinalizeMutex(&m_audioInputMutex);
    nn::os::FinalizeMessageQueue(&m_videoInputQueue);
    if (m_videoInputQueueBuffer != nullptr) {
        MultimediaFree(m_videoInputQueueBuffer, nullptr);
    }
    nn::os::FinalizeMessageQueue(&m_audioInputQueue);
    if (m_audioInputQueueBuffer != nullptr) {
        MultimediaFree(m_audioInputQueueBuffer, nullptr);
    }
    if (m_mediaClock != nullptr) {
        delete m_mediaClock;
        m_mediaClock = nullptr;
    }
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

void MovieDecoderPlayer::DestroypAudioVideoRenderer() {
    if (m_audioOutRenderer != nullptr) {
        delete m_audioOutRenderer;
        m_audioOutRenderer = nullptr;
    }
    if (m_videoRenderer != nullptr) {
        delete m_videoRenderer;
        m_videoRenderer = nullptr;
    }
}

namespace CMovieNX {

// the frame starts as noise: random luma (the C library's linear congruential step after one rand()), grey chroma
void CMovie::initialize(mm::mtl::IAllocator* allocator) {
    m_player = nullptr;
    m_frameSize = 1280 * 720 * 3 / 2;
    m_allocator = allocator;
    m_frame = static_cast<unsigned char*>(allocator->allocate(m_frameSize, 0x1000));
    unsigned char* frame = m_frame;
    unsigned int seed = rand();
    for (unsigned char* p = frame; p < frame + 1280 * 720; p++) {
        *p = seed >> 8;
        seed = seed * 1103515245 + 12345;
    }
    *reinterpret_cast<unsigned int*>(m_frame) = 0xDEADBEEF;
    memset(frame + 1280 * 720, 0x80, 1280 * 720 / 2);
    nn::os::FlushDataCache(m_frame, m_frameSize);
    s_pause = false;
    s_homeMenu = false;
}

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

// VideoRenderer::OnOutputAvailable's growth path (its caller, MovieDecoderPlayer::VideoOutputBufferAvailableEvent, is not written yet)
template void std::vector<VideoRenderer::VideoData>::__push_back_slow_path<const VideoRenderer::VideoData&>(const VideoRenderer::VideoData&);
