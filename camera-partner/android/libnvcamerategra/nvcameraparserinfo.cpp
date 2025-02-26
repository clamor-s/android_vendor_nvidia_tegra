/*
 * Copyright (c) 2012-2013 NVIDIA Corporation.  All rights reserved.
 *
 * NVIDIA Corporation and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA Corporation is strictly prohibited.
 */

#include "nvcameraparserinfo.h"

namespace android {

// when adding entries to this table, make sure you add a sane default!
// otherwise the fields they correspond to may not be initialized, and that
// can lead to some odd stability bugs where something may be set to "0" 95% of
// the time, and some odd value like "1053148932" the other 5% of the time.
ParserInfoTableEntry ParserInfoTable[] =
{

// ANDROID CAMERA PARAMETERS
// include these from CameraParameters object just to increase readability,
// though they could just as easily be accessed through the NvCameraParameters
// object
{
    CameraParameters::KEY_PREVIEW_FORMAT,
    "yuv420sp",
    CameraParameters::KEY_SUPPORTED_PREVIEW_FORMATS,
    "yuv420p,yuv420sp",
    ECSType_PreviewFormat,
    ACCESS_RW,
    ECSSubstring
},
{
    CameraParameters::KEY_PREVIEW_SIZE,
    "960x720",
    CameraParameters::KEY_SUPPORTED_PREVIEW_SIZES,
    "176x144,320x240,352x288,480x480,640x480,720x408,720x480,"\
        "720x576,800x448,960x720,1280x720,1360x720,1920x1080",
    ECSType_PreviewSize,
    ACCESS_RW,
    ECSResolution
},
{
    CameraParameters::KEY_PREVIEW_FRAME_RATE,
    "30",
    CameraParameters::KEY_SUPPORTED_PREVIEW_FRAME_RATES,
    "5,8,10,15,20,24,25,30",
    ECSType_PreviewRate,
    ACCESS_RW,
    ECSSubstring
},
{
    CameraParameters::KEY_PREVIEW_FPS_RANGE,
    "1000,120000",
    CameraParameters::KEY_SUPPORTED_PREVIEW_FPS_RANGE,
    "(1000,120000)",
    ECSType_PreviewFpsRange,
    ACCESS_RW,
    ECSNumberRange
},
{
    CameraParameters::KEY_PICTURE_FORMAT,
    "jpeg",
    CameraParameters::KEY_SUPPORTED_PICTURE_FORMATS,
    "jpeg,jfif,exif,yuv420p,yuv420sp",
    ECSType_PictureFormat,
    ACCESS_RW,
    ECSSubstring
},
{
    CameraParameters::KEY_PICTURE_SIZE,
    "2592x1944",
    CameraParameters::KEY_SUPPORTED_PICTURE_SIZES,
    "320x240,480x480,640x480,800x600,1024x768,1280x720,1280x960,1600x1200,"\
        "2048x1536,2592x1920,2592x1944",
    ECSType_PictureSize,
    ACCESS_RW,
    ECSResolution
},
// The image rotation entry has to come before the thumbnail width/height in the
// ParserInfoTable because there is logic in extractChanges() to detect when the
// rotation has changed and force an update of the thumbnail width/height in
// that case.
{
    CameraParameters::KEY_ROTATION,
    "0",
    KEY_ROTATION_VALUES,
    "0,90,180,270",
    ECSType_PictureRotation,
    ACCESS_RW,
    ECSSubstring
},
{
    CameraParameters::KEY_JPEG_THUMBNAIL_WIDTH,
    "320",
    NULL,
    NULL,
    ECSType_ThumbnailWidth,
    ACCESS_RW,
    ECSResolutionDimension
},
{
    CameraParameters::KEY_JPEG_THUMBNAIL_HEIGHT,
    "240",
    NULL,
    NULL,
    ECSType_ThumbnailHeight,
    ACCESS_RW,
    ECSResolutionDimension
},
{
    CameraParameters::KEY_SUPPORTED_JPEG_THUMBNAIL_SIZES,
    "0x0,320x240,240x320",
    NULL,
    NULL,
    ECSType_ThumbnailSize,
    ACCESS_RO,
    ECSInvalid
},
{
    CameraParameters::KEY_JPEG_THUMBNAIL_QUALITY,
    "90",
    NULL,
    NULL,
    ECSType_ThumbnailQuality,
    ACCESS_RW,
    ECSPercent
},
{
    CameraParameters::KEY_JPEG_QUALITY,
    "95",
    NULL,
    NULL,
    ECSType_ImageQuality,
    ACCESS_RW,
    ECSPercent
},
{
    CameraParameters::KEY_FLASH_MODE,
    "off",
    CameraParameters::KEY_SUPPORTED_FLASH_MODES,
    FLASH_MODE_VALUES,
    ECSType_FlashMode,
    ACCESS_RW,
    ECSSubstring
},
{
    CameraParameters::KEY_SCENE_MODE,
    "auto",
    CameraParameters::KEY_SUPPORTED_SCENE_MODES,
    "auto,action,portrait,landscape,beach,fireworks,night,"\
        "night-portrait,snow,sports,steadyphoto,sunset,theatre,barcode,hdr",
    ECSType_SceneMode,
    ACCESS_RW,
    ECSSubstring
},
{
    CameraParameters::KEY_EFFECT,
    "none",
    CameraParameters::KEY_SUPPORTED_EFFECTS,
    "mono,negative,none,posterize,sepia,aqua,solarize,nv-vivid,nv-emboss",
    ECSType_ColorEffect,
    ACCESS_RW,
    ECSSubstring
},
{
    CameraParameters::KEY_WHITE_BALANCE,
    "auto",
    CameraParameters::KEY_SUPPORTED_WHITE_BALANCE,
    WHITE_BALANCE_VALUES,
    ECSType_WhiteBalanceMode,
    ACCESS_RW,
    ECSSubstring
},
{
    CameraParameters::KEY_ANTIBANDING,
    "auto",
    CameraParameters::KEY_SUPPORTED_ANTIBANDING,
    "off,auto,50hz,60hz",
    ECSType_LightFreqMode,
    ACCESS_RW,
    ECSSubstring
},

// TODO fix exp-comp to do real min/max compare,
// next 4 params seem kind of hacky for now (but same as old HAL)
{
    CameraParameters::KEY_EXPOSURE_COMPENSATION,
    NULL,
    NULL,
    NULL,
    ECSType_ExposureCompensation,
    ACCESS_RW,
    ECSFloat
},
{
    NULL,
    NULL,
    CameraParameters::KEY_MAX_EXPOSURE_COMPENSATION,
    EXP_COMPENSATION_MAX,
    ECSType_MaxExpComp,
    ECSAccess_NS,
    ECSSubstring
},
{
    NULL,
    NULL,
    CameraParameters::KEY_MIN_EXPOSURE_COMPENSATION,
    EXP_COMPENSATION_MIN,
    ECSType_MinExpComp,
    ECSAccess_NS,
    ECSSubstring
},
{
    NULL,
    NULL,
    CameraParameters::KEY_EXPOSURE_COMPENSATION_STEP,
    EXP_COMPENSATION_STEP,
    ECSType_ExpCompStep,
    ECSAccess_NS,
    ECSSubstring
},

{
    NULL,
    NULL,
    CameraParameters::KEY_MAX_NUM_DETECTED_FACES_HW,
#if USE_NV_FD
    "10",
#else
    "0",
#endif
    ECSType_FDLimit,
    ACCESS_RO,
    ECSSubstring
},
{
    CameraParameters::KEY_VIDEO_STABILIZATION,
    "false",
    KEY_VIDEO_STABILIZATION_VALUES,
    "false,true",
    ECSType_VideoStabEn,
    ACCESS_RW,
    ECSSubstring
},
{
    CameraParameters::KEY_FOCUS_MODE,
    NULL,
    CameraParameters::KEY_SUPPORTED_FOCUS_MODES,
    FOCUS_MODE_VALUES,
    ECSType_FocusMode,
    ACCESS_RW,
    ECSSubstring
},
{
    CameraParameters::KEY_FOCAL_LENGTH,
    NULL,
    NULL,
    NULL,
    ECSType_FocalLength,
    ACCESS_RO,
    ECSFloat
},
{
    CameraParameters::KEY_HORIZONTAL_VIEW_ANGLE,
    NULL,
    NULL,
    NULL,
    ECSType_HorizontalViewAngle,
    ACCESS_RO,
    ECSFloat
},
{
    CameraParameters::KEY_VERTICAL_VIEW_ANGLE,
    NULL,
    NULL,
    NULL,
    ECSType_VerticalViewAngle,
    ACCESS_RO,
    ECSFloat
},
{
    CameraParameters::KEY_ZOOM,
    NULL,
    CameraParameters::KEY_MAX_ZOOM,
    MAX_ZOOM_LEVEL,
    ECSType_ZoomValue,
    ACCESS_RW,
    ECSNumberMax
},
{
    NULL,
    NULL,
    CameraParameters::KEY_ZOOM_SUPPORTED,
    "true",
    ECSType_Invalid,
    ECSAccess_NS,
    ECSSubstring
},
{
    NULL,
    NULL,
    CameraParameters::KEY_ZOOM_RATIOS,
    ZOOM_RATIOS,
    ECSType_Invalid,
    ECSAccess_NS,
    ECSSubstring
},
{
    NULL,
    NULL,
    CameraParameters::KEY_SMOOTH_ZOOM_SUPPORTED,
    "true",
    ECSType_Invalid,
    ECSAccess_NS,
    ECSSubstring
},
{
    CameraParameters::KEY_GPS_LATITUDE,
    NULL,
    NULL,
    NULL,
    ECSType_GpsLatitude,
    ACCESS_RW,
    ECSFloat
},
{
    CameraParameters::KEY_GPS_LONGITUDE,
    NULL,
    NULL,
    NULL,
    ECSType_GpsLongitude,
    ACCESS_RW,
    ECSFloat
},
{
    CameraParameters::KEY_GPS_ALTITUDE,
    NULL,
    NULL,
    NULL,
    ECSType_GpsAltitude,
    ACCESS_RW,
    ECSFloat
},
{
    CameraParameters::KEY_GPS_TIMESTAMP,
    NULL,
    NULL,
    NULL,
    ECSType_GpsTimestamp,
    ACCESS_RW,
    ECSFloat
},
{
    CameraParameters::KEY_GPS_PROCESSING_METHOD,
    NULL,
    NULL,
    NULL,
    ECSType_GpsProcMethod,
    ACCESS_RW,
    ECSString
},
{
    CameraParameters::KEY_FOCUS_AREAS,
    "(0,0,0,0,0)",
    CameraParameters::KEY_MAX_NUM_FOCUS_AREAS,
    MAX_FOCUS_WINDOWS_STR,
    ECSType_AreasToFocus,
    ACCESS_RW,
    ECSRectangles
},
{
    CameraParameters::KEY_METERING_AREAS,
    "(0,0,0,0,0)",
    CameraParameters::KEY_MAX_NUM_METERING_AREAS,
    MAX_EXPOSURE_WINDOWS_STR,
    ECSType_AreasToMeter,
    ACCESS_RW,
    ECSRectangles
},
{
    NULL,
    NULL,
    CameraParameters::KEY_VIDEO_STABILIZATION_SUPPORTED,
#if defined(__ARM_NEON__)
    "true",
#else
    "false",
#endif
    ECSType_VideoStabSupported,
    ECSAccess_NS,
    ECSSubstring
},
{
    NULL,
    NULL,
    CameraParameters::KEY_VIDEO_SNAPSHOT_SUPPORTED,
    "true",
    ECSType_VideoSnapSupported,
    ECSAccess_NS,
    ECSSubstring
},
{
    CameraParameters::KEY_VIDEO_SIZE,
    "1280x720",
    CameraParameters::KEY_SUPPORTED_VIDEO_SIZES,
    "176x144,320x240,352x288,640x480,720x480,720x576,1280x720,1920x1080",
    ECSType_VideoSize,
    ACCESS_RW,
    ECSResolution
},
{
    CameraParameters::KEY_VIDEO_FRAME_FORMAT,
    "yuv420p",
    KEY_VIDEO_FRAME_FORMAT_VALUES,
    "yuv420p",
    ECSType_VideoFrameFormat,
    ACCESS_RO,
    ECSSubstring
},
{
   /*
    * The value for preferred preview size is determined based on two factors:
    *
    * 1. It should not cause performance or memory bandwidth issue
    *    for HD video recording. In other words, it should not be
    *    too large.
    *
    * 2. It should not lead to incorrect preview aspect ratio issue.
    *    In other words, a smaller resolution video recording should
    *    be able to just use the video size as the preview size.
    *
    * The algorithm for determining the actual preview size during
    * video recording is documented in Camera.java class.
    */
    CameraParameters::KEY_PREFERRED_PREVIEW_SIZE_FOR_VIDEO,
    "1920x1080",
    NULL,
    NULL,
    ECSType_PreferredPreviewSize,
    ACCESS_RO,
    ECSResolution
},
{
    CameraParameters::KEY_RECORDING_HINT,
    "false",
    KEY_RECORDING_HINT_VALUES,
    "false,true",
    ECSType_RecordingHint,
    ACCESS_RW,
    ECSNone
},
{
    CameraParameters::KEY_AUTO_WHITEBALANCE_LOCK,
    "false",
    KEY_AUTO_WHITEBALANCE_LOCK_VALUES,
    "false,true",
    ECSType_AWBLock,
    ACCESS_RW,
    ECSSubstring
},
{
    NULL,
    NULL,
    CameraParameters::KEY_AUTO_WHITEBALANCE_LOCK_SUPPORTED,
    "true",
    ECSType_AWBLockSupport,
    ECSAccess_NS,
    ECSSubstring
},
{
    CameraParameters::KEY_AUTO_EXPOSURE_LOCK,
    "false",
    KEY_AUTO_EXPOSURE_LOCK_VALUES,
    "false,true",
    ECSType_AELock,
    ACCESS_RW,
    ECSSubstring
},
{
    NULL,
    NULL,
    CameraParameters::KEY_AUTO_EXPOSURE_LOCK_SUPPORTED,
    "true",
    ECSType_AELockSupport,
    ECSAccess_NS,
    ECSSubstring
},
{
    CameraParameters::KEY_FOCUS_DISTANCES,
    "0.95,1.9,Infinity",
    NULL,
    NULL,
    ECSType_FocusDistances,
    ACCESS_RO,
    ECSSubstring
},

// NV CAMERA PARAMETERS

{
    NV_FLIP_PREVIEW,
    "off",
    NV_FLIP_PREVIEW_VALUES,
    "off,vertical,horizontal,both",
    ECSType_FlipPreview,
    ACCESS_RW_NONSTD,
    ECSSubstring
},
{
    NV_FLIP_STILL,
    "off",
    NV_FLIP_STILL_VALUES,
    "off,vertical,horizontal,both",
    ECSType_FlipStill,
    ACCESS_RW_NONSTD,
    ECSSubstring
},
{
    NV_FOCUS_POSITION,
    NULL,
    NV_FOCUS_POSITION_VALUES,
    "0",
    ECSType_FocusPosition,
    ACCESS_RW_NONSTD,
    ECSNumberMin
},
{
    NV_CUSTOM_POSTVIEW,
    "off",
    NV_CUSTOM_POSTVIEW_VALUES,
    "off",
    ECSType_CustomPostviewEn,
    (ACCESS_RW_NONSTD | ECSAccess_Old),
    ECSSubstring
},
{
    NV_TIMESTAMP_MODE,
    "off",
    NV_TIMESTAMP_MODE_VALUES,
    "off,on",
    ECSType_TimestampEn,
    ACCESS_RW_NONSTD,
    ECSSubstring
},
{
    NV_ZOOM_STEP,
    "0.5",
    NV_CONTINUOUS_ZOOM_STEP_VALUES,
    "1,0.5,0.25",
    ECSType_ZoomStep,
    ACCESS_RW_NONSTD,
    ECSSubstring
},
{
    NV_ZOOM_SPEED,
    "99",
    NULL,
    NULL,
    ECSType_ZoomSpeed,
    ACCESS_RW_NONSTD,
    ECSPercent
},
{
    NV_NSL_NUM_BUFFERS,
    "0",
    NV_NSL_NUM_BUFFERS_MAX,
    "9",
    ECSType_NSLNumBuffers,
    ACCESS_RW_NONSTD,
    ECSNumberMax
},
{
    NV_VIDEO_SPEED,
    "1.0",
    NV_VIDEO_SPEED_VALUES,
    "0.25,0.5,1.0,2.0,3.0,4.0",
    ECSType_VideoSpeed,
    ACCESS_RW_NONSTD,
    ECSFloat
},
{
    NV_VIDEO_HIGHSPEED_RECORDING,
    "false",
    NV_VIDEO_HIGHSPEED_RECORDING_VALUES,
    "false,true",
    ECSType_VideoHighSpeedRecording,
    ACCESS_RW_NONSTD,
    ECSSubstring
},
{
    NV_NSL_SKIP_COUNT,
    "0",
    NV_NSL_SKIP_COUNT_MAX,
    "100",
    ECSType_NSLSkipCount,
    ACCESS_RW_NONSTD,
    ECSNumberMax
},
{
    NV_NSL_BURST_PICTURE_COUNT,
    "0",
    NV_NSL_BURST_PICTURE_COUNT_MAX,
    "9",
    ECSType_NSLBurstCount,
    ACCESS_RW_NONSTD,
    ECSNumberMax
},
{
    NV_SKIP_COUNT,
    "0",
    NV_SKIP_COUNT_MAX,
    "100",
    ECSType_SkipCount,
    ACCESS_RW_NONSTD,
    ECSNumberMax
},
{
    NV_BURST_PICTURE_COUNT,
    "1",
    NV_BURST_PICTURE_COUNT_MAX,
    "999999",
    ECSType_BurstCount,
    ACCESS_RW_NONSTD,
    ECSNumberMax
},
{
    NV_EV_BRACKET_CAPTURE,
    " ",
    NULL,
    NULL,
    ECSType_BracketCapture,
    ACCESS_RW_NONSTD,
    ECSString
},
{
    NV_STILL_HDR,
    "false",
    NV_STILL_HDR_VALUES,
    "false,true",
    ECSType_StillHDR,
    ACCESS_RW_NONSTD_DEP,
    ECSSubstring
},
{
    NV_STILL_HDR_ENCODE_SOURCE_FRAMES,
    // there must be enough entries here to match the
    // value of NV_STILL_HDR_SOURCE_FRAME_COUNT
    "false,false,false",
    NULL,
    NULL,
    ECSType_StillHDREncodeSourceFrames,
    ACCESS_RW_NONSTD,
    ECSNone
},
{
    NV_STILL_HDR_SOURCE_FRAME_COUNT,
    // if you change this, make sure to change the defaults of
    // NV_STILL_HDR_ENCODE_SOURCE_FRAMES to match it
    "3",
    NULL,
    NULL,
    ECSType_StillHDRSourceFrameCount,
    ACCESS_RO_NONSTD,
    ECSNone
},
{
    NV_STILL_HDR_ENCODE_COUNT,
    "1", // only output final frame *unless* app says otherwise
    NULL,
    NULL,
    ECSType_StillHDREncodeCount,
    ACCESS_RW_NONSTD, // isn't parsed by HAL, but may change as app sets other things
    ECSNone
},
{
    NV_STILL_HDR_EXPOSURE_VALUES,
    NULL,
    NULL,
    NULL,
    ECSType_StillHDRExposureVals,
    ACCESS_RO_NONSTD,
    ECSNone
},
{
    NV_RAW_DUMP_FLAG,
    "0",
    NV_RAW_DUMP_FLAG_VALUES,
    "0,1,5,7,13",
    ECSType_RawDumpFlag,
    ACCESS_RW_NONSTD,
    ECSSubstring
},
{
    NV_EXIF_MAKE,
    "NVIDIA",
    NULL,
    NULL,
    ECSType_ExifMake,
    ACCESS_RW_NONSTD,
    ECSString
},
{
    NV_EXIF_MODEL,
    "Development Platform",
    NULL,
    NULL,
    ECSType_ExifModel,
    ACCESS_RW_NONSTD,
    ECSString
},
{
    NV_GPS_MAP_DATUM,
    NULL,
    NULL,
    NULL,
    ECSType_GpsMapDatum,
    ACCESS_RW_NONSTD,
    ECSString
},
{
    NV_USER_COMMENT,
    NULL,
    NULL,
    NULL,
    ECSType_UserComment,
    ACCESS_RW_NONSTD,
    ECSString
},
{
    NV_PICTURE_ISO,
    "auto",
    NV_PICTURE_ISO_VALUES,
    "auto,100,1600",
    ECSType_PictureIso,
    ACCESS_RW_NONSTD,
    ECSIso
},
{
    NV_CONTRAST,
    "normal",
    NV_CONTRAST_VALUES,
    "lowest,low,normal,high,highest",
    ECSType_Contrast,
    ACCESS_RW_NONSTD,
    ECSSubstring
},
{
    NV_SATURATION,
    NULL,
    NV_SATURATION_VALUES,
    "-100,100",
    ECSType_Saturation,
    ACCESS_RW_NONSTD,
    ECSNumberMinMax
},
{
    NV_EDGE_ENHANCEMENT,
    "-1",
    NV_EDGE_ENHANCEMENT_VALUES,
    "-101,100",
    ECSType_EdgeEnhancement,
    ACCESS_RW_NONSTD,
    ECSNumberMinMax
},
{
    NV_CAPABILITY_FOR_VIDEO_SIZE,
    NULL,
    NV_CAPABILITY_FOR_VIDEO_SIZE_VALUES,
    "640x480:640x480:30",
    ECSType_VideoPreviewSizefps,
    ACCESS_RW_NONSTD,
    ECSSubstring
},
{
    NV_USE_NVBUFFER,
    NULL,
    NULL,
    NULL,
    ECSType_UseNvBuffers,
    ACCESS_RW_NONSTD,
    ECSNone
},
{
    NV_SENSOR_MODE,
    "0x0x0",
    NV_SENSOR_MODE_VALUES,
    "0x0x0",
    ECSType_SensorMode,
    (ACCESS_RW_NONSTD | ECSAccess_Old),
    ECSSubstring
},
{
    NV_CAMERA_RENDERER,
    "on",
    NV_CAMERA_RENDERER_VALUES,
    "off,on",
    ECSType_CameraRenderer,
    ACCESS_RW_NONSTD,
    ECSSubstring
},
{
    NV_STEREO_MODE,
    NULL,
    NV_STEREO_MODE_VALUES,
    "left,right,stereo",
    ECSType_CameraStereoMode,
    ACCESS_RW_NONSTD,
    ECSSubstring
},
#ifdef FRAMEWORK_HAS_MACRO_MODE_SUPPORT
{
    NV_LOWLIGHT_THRESHOLD,
    "0",
    NV_LOWLIGHT_THRESHOLD_VALUES,
    "-1",
    ECSType_LowLightThreshold,
    ACCESS_RW_NONSTD,
    ECSNumberMin
},
{
    NV_MACROMODE_THRESHOLD,
    "0",
    NV_MACROMODE_THRESHOLD_VALUES,
    "-1,100",
    ECSType_MacroModeThreshold,
    ACCESS_RW_NONSTD,
    ECSNumberMinMax
},
#endif // FRAMEWORK_HAS_MACRO_MODE_SUPPORT
{
    NV_FD_LIMIT,
    "0",
    NV_FD_LIMIT_VALUES,
    "20",
    ECSType_NVFDLimit,
    ACCESS_RW_NONSTD,
    ECSNumberMax
},
{
    NV_FD_RESULT,
    NULL,
    NULL,
    NULL,
    ECSType_FDResult,
    ACCESS_RO_NONSTD,
    ECSString
},
{
    NV_FD_DEBUG,
    "off",
    NV_FD_DEBUG_VALUES,
    "off,on",
    ECSType_FDDebug,
    ACCESS_RW_NONSTD,
    ECSSubstring
},
{
    NV_AUTO_ROTATION,
    "true",
    NV_AUTO_ROTATION_VALUES,
    "true,false",
    ECSType_AutoRotation,
    ACCESS_RW_NONSTD,
    ECSSubstring
},
{
    NV_CAPTURE_MODE,
    "normal",
    NV_CAPTURE_MODE_VALUES,
    "normal,shot2shot",
    ECSType_CaptureMode,
    ACCESS_RW_NONSTD,
    ECSSubstring
},
{
    NV_DATATAP_FMT,
    "yuv420sp",
    NV_DATATAP_FMT_VALUES,
    "yuv420p,yuv420sp,yuv422p,yuv422sp,argb8888,rgb565,luma8",
    ECSType_DataTapFormat,
    ACCESS_RW_NONSTD,
    ECSSubstring
},
{
    NV_DATATAP_SIZE,
    NULL,
    NV_DATATAP_SIZE_VALUES,
    "176x144,320x240,352x288,480x480,640x480,720x408,720x480,720x576,800x448,"\
        "1280x720,1360x720,1920x1080",
    ECSType_DataTapSize,
    ACCESS_RW_NONSTD,
    ECSResolution
},
{
    NV_DATATAP,
    "off",
    NV_DATATAP_VALUES,
    "off,on",
    ECSType_DataTap,
    ACCESS_RW_NONSTD,
    ECSSubstring
},
{
    // the precision is microsecond, 0 means auto
    NV_EXPOSURE_TIME,
    NULL,
    NV_EXPOSURE_TIME_VALUES,
    "0",
    ECSType_ExposureTime,
    ACCESS_RW_NONSTD,
    ECSNumberMin
},
{
    NV_COLOR_CORRECTION,
    NULL,
    NULL,
    NULL,
    ECSType_ColorCorrection,
    ACCESS_RW_NONSTD,
    ECSMatrix4x4
},
{
    NV_FOCUS_MOVE_MSG,
    "true",
    NV_FOCUS_MOVE_MSG_VALUES,
    "false,true",
    ECSType_FocusMoveMsg,
    ACCESS_RW_NONSTD,
    ECSSubstring
},
{
    NV_ANR_MODE,
    "auto",
    NV_ANR_MODE_VALUES,
    "auto,off,force_on",
    ECSType_ANRMode,
    ACCESS_RW_NONSTD,
    ECSSubstring
},
{
    NV_EXPOSURE_STATUS,
    "1.0,0.033333,1.0,1.0,0.0,1.0,100",
    NULL,
    NULL,
    ECSType_ExposureStatus,
    ACCESS_RW_NONSTD,
    ECSNone
},
{
    NV_DISABLE_PREVIEW_PAUSE,
    "false",
    NV_DISABLE_PREVIEW_PAUSE_VALUES,
    "false,true",
    ECSType_DisablePreviewPause,
    ACCESS_RW_NONSTD,
    ECSSubstring
},
{
    NV_PREVIEW_CALLBACK_SIZE_ENABLE,
    "false",
    NV_PREVIEW_CALLBACK_SIZE_ENABLE_VALUES,
    "false,true",
    ECSType_PreviewCallbackSizeEnable,
    ACCESS_RW_NONSTD,
    ECSSubstring
},
{
    NV_PREVIEW_CALLBACK_SIZE,
    "320x240",
    NV_SUPPORTED_PREVIEW_CALLBACK_SIZES,
    "176x144,320x240,352x288,480x480,640x480,720x408,720x480,"\
    "720x576,800x448,960x720,1280x720,1360x720,1920x1080",
    ECSType_PreviewCallbackSize,
    ACCESS_RW_NONSTD,
    ECSResolution
},
// END
{
    NULL,
    NULL,
    NULL,
    NULL,
    ECSType_Invalid,
    ECSAccess_NS,
    ECSInvalid
}
};

} //namespace android
