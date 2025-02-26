LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES :=     \
        assert.c          \
        ut/OpenSLESUT.c   \
        ut/slesutResult.c

LOCAL_C_INCLUDES:= \
        system/media/wilhelm/include

LOCAL_CFLAGS += -fvisibility=hidden -UNDEBUG

LOCAL_MODULE := libOpenSLESUT

include $(BUILD_STATIC_LIBRARY)

include $(CLEAR_VARS)

LOCAL_C_INCLUDES:= \
        system/media/wilhelm/include

LOCAL_CFLAGS += -Wno-override-init
# -Wno-missing-field-initializers
# optional, see comments in MPH_to.c: -DUSE_DESIGNATED_INITIALIZERS -S
LOCAL_CFLAGS += -DUSE_DESIGNATED_INITIALIZERS -UNDEBUG

LOCAL_SRC_FILES:=                     \
        assert.c \
        MPH_to.c \
        handlers.c

LOCAL_MODULE:= libopensles_helper

include $(BUILD_STATIC_LIBRARY)

include $(CLEAR_VARS)

# do not claim support for any OpenSL ES or OpenMAX AL profiles
LOCAL_CFLAGS += -DUSE_PROFILES=0

# enable API logging; details are set separately by SL_TRACE_DEFAULT below
LOCAL_CFLAGS += -DUSE_TRACE
# or -UUSE_TRACE to disable API logging

# enable mutex deadlock detection
LOCAL_CFLAGS += -DUSE_DEBUG
# or -UUSE_DEBUG for no mutex deadlock detection

# enable assert() to do runtime checking
LOCAL_CFLAGS += -UNDEBUG
# or -DNDEBUG for no runtime checking

# select the level of log messages
LOCAL_CFLAGS += -DUSE_LOG=SLAndroidLogLevel_Info
# or -DUSE_LOG=SLAndroidLogLevel_Verbose for verbose logging

# log all API entries and exits
# LOCAL_CFLAGS += -DSL_TRACE_DEFAULT=SL_TRACE_ALL
# (otherwise a warning log on error results only)

# API level
LOCAL_CFLAGS += -DPLATFORM_SDK_VERSION=$(PLATFORM_SDK_VERSION)

# Reduce size of .so and hide internal global symbols
LOCAL_CFLAGS += -fvisibility=hidden -DLI_API='__attribute__((visibility("default")))'

LOCAL_SRC_FILES:=                     \
        OpenSLES_IID.c                \
        assert.c                      \
        classes.c                     \
        data.c                        \
        devices.c                     \
        entry.c                       \
        handler_bodies.c              \
        trace.c                       \
        locks.c                       \
        sles.c                        \
        sl_iid.c                      \
        sllog.c                       \
        ThreadPool.c                  \
        xa_iid.c                      \
        android/AudioPlayer_to_android.cpp    \
        android/AudioRecorder_to_android.cpp  \
        android/MediaPlayer_to_android.cpp    \
        android/OutputMix_to_android.cpp      \
        android/VideoCodec_to_android.cpp     \
        android/BufferQueueSource.cpp         \
        android/CallbackProtector.cpp         \
        android/AacBqToPcmCbRenderer.cpp      \
        android/android_AudioSfDecoder.cpp    \
        android/android_AudioToCbRenderer.cpp \
        android/android_GenericMediaPlayer.cpp\
        android/android_GenericPlayer.cpp     \
        android/android_LocAVPlayer.cpp       \
        android/android_CameraPreviewPlayer.cpp \
        android/android_StreamPlayer.cpp      \
        android/android_Effect.cpp            \
        android/android_bufferqueuewriter.cpp \
        android/android_cameradevice.cpp      \
        android/android_mediarecorder.cpp     \
        android/android_nvsfrecorder.cpp      \
        android/android_datatap.cpp           \
        android/util/AacAdtsExtractor.cpp     \
        autogen/IID_to_MPH.c                  \
        objects/C3DGroup.c                    \
        objects/CAudioPlayer.c                \
        objects/CAudioRecorder.c              \
        objects/CEngine.c                     \
        objects/COutputMix.c                  \
        objects/CMediaPlayer.c                \
        objects/CCameraDevice.c               \
        objects/CMediaRecorder.c              \
        itf/IAndroidBufferQueue.c         \
        itf/IAndroidConfiguration.c       \
        itf/IAndroidEffect.cpp            \
        itf/IAndroidEffectCapabilities.c  \
        itf/IAndroidEffectSend.c          \
        itf/IAudioEncoder.c               \
        itf/IAudioEncoderCapabilities.c   \
        itf/IBassBoost.c                  \
        itf/IBufferQueue.c                \
        itf/IDynamicInterfaceManagement.c \
        itf/IEffectSend.c                 \
        itf/IEngine.c                     \
        itf/IEngineCapabilities.c         \
        itf/IEnvironmentalReverb.c        \
        itf/IEqualizer.c                  \
        itf/IMetadataExtraction.c         \
        itf/IMuteSolo.c                   \
        itf/IObject.c                     \
        itf/IOutputMix.c                  \
        itf/IPlay.c                       \
        itf/IPlaybackRate.c               \
        itf/IPrefetchStatus.c             \
        itf/IPresetReverb.c               \
        itf/IRecord.c                     \
        itf/ISeek.c                       \
        itf/IStreamInformation.cpp        \
        itf/IVideoDecoderCapabilities.cpp \
        itf/IVirtualizer.c                \
        itf/IVolume.c                     \
        itf/ICamera.c                           \
        itf/ICameraCapabilities.c               \
        itf/IImageControls.c                    \
        itf/IImageDecoderCapabilities.c         \
        itf/IImageEffect.c                      \
        itf/IImageEncoder.c                     \
        itf/IImageEncoderCapabilities.c         \
        itf/IMetadataInsertion.c                \
        itf/ISnapshot.c                         \
        itf/IVideoEncoder.c                     \
        itf/IVideoPostProcessing.c              \
        itf/IXARecord.c                         \
        itf/INvCameraExtCapabilities.c          \
        itf/INvVideoDecoder.c                   \
        itf/INvVideoDecoderExtCapabilities.c    \
        itf/INvVideoEncoderExt.c                \
        itf/INvVideoEncoderExtCapabilities.c    \
        itf/IVideoEncoderCapabilities.c         \
        itf/IGetCapabilitiesOfInterface.c       \
        itf/CNvDataTap.c                        \
        itf/INvDataTapApp.c                     \
        itf/INvBurstMode.c

EXCLUDE_SRC :=                            \
        sync.c                            \
        itf/I3DCommit.c                   \
        itf/I3DDoppler.c                  \
        itf/I3DGrouping.c                 \
        itf/I3DLocation.c                 \
        itf/I3DMacroscopic.c              \
        itf/I3DSource.c                   \
        itf/IAudioDecoderCapabilities.c   \
        itf/IAudioIODeviceCapabilities.c  \
        itf/IDeviceVolume.c               \
        itf/IDynamicSource.c              \
        itf/ILEDArray.c                   \
        itf/IMIDIMessage.c                \
        itf/IMIDIMuteSolo.c               \
        itf/IMIDITempo.c                  \
        itf/IMIDITime.c                   \
        itf/IMetadataTraversal.c          \
        itf/IPitch.c                      \
        itf/IRatePitch.c                  \
        itf/IThreadSync.c                 \
        itf/IVibra.c                      \
        itf/IVisualization.c

LOCAL_C_INCLUDES:=                                                  \
        system/media/wilhelm/include                                \
        frameworks/base/media/libstagefright                        \
        frameworks/base/media/libstagefright/include                \
        frameworks/base/include/media/stagefright/openmax           \
        system/media/audio_effects/include                          \
        vendor/nvidia/tegra/multimedia-partner/openmax/include/openmax/al                 \
        vendor/nvidia/tegra/multimedia-partner/openmax/include/openmax/il                 \
        frameworks/base/media/libstagefright/rtsp                   \
        vendor/nvidia/tegra/core/include

# __pthread_gettid
LOCAL_C_INCLUDES += bionic/libc/private

LOCAL_CFLAGS += -x c++ -Wno-multichar -Wno-invalid-offsetof

LOCAL_STATIC_LIBRARIES += \
        libopensles_helper        \
        libOpenSLESUT             \
        libstagefright_rtsp

LOCAL_SHARED_LIBRARIES :=         \
        libutils                  \
        libmedia                  \
        libbinder                 \
        libandroid                \
        libstagefright            \
        libstagefright_foundation \
        libcutils                 \
        libgui                    \
        libdl                     \
        libcamera_client

LOCAL_MODULE := libwilhelm
LOCAL_MODULE_TAGS := optional

ifeq ($(TARGET_BUILD_VARIANT),userdebug)
        LOCAL_CFLAGS += -DUSERDEBUG_BUILD=1
endif

LOCAL_PRELINK_MODULE := false
include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_SRC_FILES := sl_entry.c sl_iid.c assert.c
LOCAL_C_INCLUDES:=                                                  \
        system/media/wilhelm/include                                \
        frameworks/base/media/libstagefright                        \
        frameworks/base/media/libstagefright/include                \
        frameworks/base/include/media/stagefright/openmax           \
        vendor/nvidia/tegra/multimedia-partner/openmax/include/openmax/al



LOCAL_MODULE := libOpenSLES
LOCAL_PRELINK_MODULE := false
LOCAL_MODULE_TAGS := optional
LOCAL_CFLAGS += -x c++ -DLI_API= -fvisibility=hidden -UNDEBUG \
                -DSL_API='__attribute__((visibility("default")))'
LOCAL_SHARED_LIBRARIES := libwilhelm
include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_SRC_FILES := xa_entry.c xa_iid.c assert.c
LOCAL_C_INCLUDES:=                                                  \
        system/media/wilhelm/include                                \
        frameworks/base/media/libstagefright                        \
        frameworks/base/media/libstagefright/include                \
        frameworks/base/include/media/stagefright/openmax           \
        vendor/nvidia/tegra/multimedia-partner/openmax/include/openmax/al

LOCAL_MODULE := libOpenMAXAL
LOCAL_PRELINK_MODULE := false
LOCAL_MODULE_TAGS := optional
LOCAL_CFLAGS += -x c++ -DLI_API= -fvisibility=hidden -UNDEBUG \
                -DXA_API='__attribute__((visibility("default")))'
LOCAL_SHARED_LIBRARIES := libwilhelm
include $(BUILD_SHARED_LIBRARY)
