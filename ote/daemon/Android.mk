#
# Copyright (c) 2013-2014, NVIDIA CORPORATION. All rights reserved
#
# Permission is hereby granted, free of charge, to any person obtaining
# a copy of this software and associated documentation files
# (the "Software"), to deal in the Software without restriction,
# including without limitation the rights to use, copy, modify, merge,
# publish, distribute, sublicense, and/or sell copies of the Software,
# and to permit persons to whom the Software is furnished to do so,
# subject to the following conditions:
#
# The above copyright notice and this permission notice shall be
# included in all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
# IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
# CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
# TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
# SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#

ifeq (tlk,$(SECURE_OS_BUILD))

LOCAL_PATH:= $(call my-dir)

include $(NVIDIA_DEFAULTS)
LOCAL_C_INCLUDES:= $(LOCAL_PATH) \
	$(TOP)/3rdparty/ote/lib/include \
	$(TEGRA_TOP)/core/include
LOCAL_SRC_FILES:= tlk_daemon.c
LOCAL_MODULE:= tlk_daemon
LOCAL_STATIC_LIBRARIES:= \
		libc \
		liblog \
		libtlk_common \
		libtlk_client

LOCAL_FORCE_STATIC_EXECUTABLE := true

include $(NVIDIA_EXECUTABLE)

endif # SECURE_OS_BUILD == tlk
