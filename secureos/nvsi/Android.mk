# NVIDIA development system
#
# Copyright (c) 2012-2013, NVIDIA CORPORATION.  All rights reserved.
#
# !!! PLEASE DO NOT EDIT THIS FILE WITHOUT CONSULTING NVIDIA !!!

LOCAL_PATH := $(call my-dir)

# figure out correct XML file to use
include $(LOCAL_PATH)/helper.mk

include $(NVIDIA_DEFAULTS)

LOCAL_MODULE := com.nvidia.nvsi.xml
LOCAL_MODULE_CLASS := etc
LOCAL_MODULE_PATH := $(TARGET_OUT_ETC)/permissions
LOCAL_SRC_FILES := $(NVSI_XML_FILE)

include $(NVIDIA_PREBUILT)
