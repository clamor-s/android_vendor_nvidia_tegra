/*
 * Copyright (c) 2012-2013 NVIDIA Corporation.  All rights reserved.
 * 
 * NVIDIA Corporation and its licensors retain all intellectual property
 * and proprietary rights in and to this software and related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA Corporation is strictly prohibited.
 */

/**
 * @file nvboot_fuse_int.h
 *
 * Fuse interface for NvBoot
 *
 * NvBootFuse is NVIDIA's interface for fuse query and programming.
 *
 * Note that fuses have a value of zero in the unburned state; burned
 * fuses have a value of one.
 *
 */

#ifndef INCLUDED_NVBOOT_FUSE_INT_H
#define INCLUDED_NVBOOT_FUSE_INT_H

#include "nvcommon.h"
#include "t11x/nvboot_error.h"
#include "t11x/nvboot_fuse.h"
#include "nvboot_sku_int.h"

#if defined(__cplusplus)
extern "C"
{
#endif

/*
 * NvBootFuseOperatingMode -- The chip's current operating mode
 */
typedef enum
{
    NvBootFuseOperatingMode_None = 0,
    NvBootFuseOperatingMode_Preproduction,
    NvBootFuseOperatingMode_FailureAnalysis,
    NvBootFuseOperatingMode_NvProduction,
    NvBootFuseOperatingMode_OdmProductionNonSecure,
    NvBootFuseOperatingMode_OdmProductionNonsecure =
    NvBootFuseOperatingMode_OdmProductionNonSecure,
    NvBootFuseOperatingMode_OdmProductionSecureSBK,
    NvBootFuseOperatingMode_OdmProductionSecure =
    NvBootFuseOperatingMode_OdmProductionSecureSBK,
    NvBootFuseOperatingMode_OdmProductionSecurePKC,
    NvBootFuseOperatingMode_Max, /* Must appear after the last legal item */
    NvBootFuseOperatingMode_Force32 = 0x7fffffff
} NvBootFuseOperatingMode;

/**
 * Reports chip's operating mode
 *
 * The Decision Tree is as follows --
 * 1. if Failure Analysis (FA) Fuse burned, then Failure Analysis Mode
 * 2. if ODM Production Fuse burned and ..
 *    a.if PKC disable fuse is not burnt,then ODM Production Mode Secure PKC
 *    b. if PKC diasbale fuse burnt and SBK Fuses are NOT all zeroes,
 *    then ODM Production Mode SecureSBK mode
 *    c. if SBK Fuses are all zeroes, then ODM Production Mode Non-Secure
 * 3. if NV Production Fuse burned, then NV Production Mode
 * 4. else, Preproduction Mode
 *
 *                                  Fuse Value*
 *                             ----------------------
 * Operating Mode              FA    NV    ODM    SBK  PKC
 * --------------              --    --    ---    ---  ---
 * Failure Analysis            1     x     x      x    x
 * ODM Production SecurePKC    0     x     1      <>0  0
 * ODM Production SecureSBK    0     x     1      <>0  1
 * ODM Production Non-Secure   0     x     1      ==0  1
 * NV Production               0     1     0      x    x
 * Preproduction               0     0     0      x    x

 * * where 1 = burned, 0 = unburned, x = don't care
 * * for PKC ,it is PKC disable fuse
 * @param pMode pointer to buffer where operating mode is to be stored
 *
 * @return void, table is complete decode and so cannot fail
 */
void
NvBootFuseGetOperatingMode(NvBootFuseOperatingMode *pMode);

/**
 * Reports whether chip is in Failure Analysis (FA) Mode
 *
 * Failure Analysis Mode means all of the following are true --
 * 1. Failure Analysis Fuse is burned
 *
 * @return NvTrue if chip is in Failure Analysis Mode; else NvFalse
 */
NvBool
NvBootFuseIsFailureAnalysisMode(void);

/**
 * Reports whether chip is in ODM Production Mode
 *
 * Production Mode means all of the following are true --
 * 1. FA Fuse is not burned
 * 2. ODM Production Fuse is burned
 *
 * @return NvTrue if chip is in ODM Production Mode; else NvFalse
 */
NvBool
NvBootFuseIsOdmProductionMode(void);

/**
 * Reports whether chip is in ODM Production Mode Secure
 *
 * Production Mode means all of the following are true --
 * 1. chip is in ODM Production Mode
 * 2. Secure Boot Key is not all zeroes
 *
 * @return NvTrue if chip is in ODM Production Mode Secure; else NvFalse
 */
NvBool
NvBootFuseIsOdmProductionModeSecure(void);

/**
 * Reports whether chip is in ODM Production Mode Non-Secure
 *
 * Production Mode means all of the following are true --
 * 1. chip is in ODM Production Mode
 * 2. Secure Boot Key is all zeroes
 *
 * @return NvTrue if chip is in ODM Production Mode Non-Secure; else NvFalse
 */
NvBool
NvBootFuseIsOdmProductionModeNonsecure(void);

/**
 * Reports whether chip is in NV Production Mode
 *
 * Production Mode means all of the following are true --
 * 1. FA Fuse is not burned
 * 2. NV Production Fuse is burned
 * 3. ODM Production Fuse is not burned
 *
 * @return NvTrue if chip is in NV Production Mode; else NvFalse
 */
NvBool
NvBootFuseIsNvProductionMode(void);

/**
 * Reports whether chip is in Preproduction Mode
 *
 * Pre-production Mode means all of the following are true --
 * 1. FA Fuse is not burned
 * 2. ODM Production Fuse is not burned
 * 3. NV Production Fuse is not burned
 *
 * @return NvTrue if chip is in Preproduction Mode; else NvFalse
 */
NvBool
NvBootFuseIsPreproductionMode(void);

/**
 * Reports whether chip is in PKC secure boot mode or
 * symmetric key based secure boot mode.
 * If burned, pkc_disable disables the use of PKC secure boot, and
 * the BR reverts back to symmetric key based secure boot infrastructure.
 * Note: The pkc_disable fuse has no effect if the security_mode fuse
 * (i.e. ODM production mode fuse) has not been burned. In this case
 * the pkc_disable fuse is always 0.
 *
 * @return NvTrue if pkc_disable bit is 0; else NvFalse
 */
NvBool
NvBootFuseIsPkcBootMode(void);

/**
 * Reads Secure Boot Key (SBK) from fuses
 *
 * User must guarantee that the buffer can hold 16 bytes
 *
 * @param pKey pointer to buffer where SBK value will be placed
 *
 * @return void (assume trusted caller, no parameter validation)
 */
void
NvBootFuseGetSecureBootKey(NvU8 *pKey);

/**
 * Reads Device Key (DK) from fuses
 *
 * User must guarantee that the buffer can hold 4 bytes
 *
 * @param pKey pointer to buffer where DK value will be placed
 *
 * @return void (assume trusted caller, no parameter validation)
 */
void
NvBootFuseGetDeviceKey(NvU8 *pKey);

/**
 * Hide SBK and DK
 *
 */
void
NvBootFuseHideKeys(void);

/**
 * Reads the SHA-256 Hash of the public key modulus
 * from fuses.
 *
 * User must guarantee that the buffer can hold 32 bytes
 *
 * @param pKey pointer to buffer where public key modulus will be placed
 *
 * @return void (assume trusted caller, no parameter validation)
 */
void
NvBootFuseGetPublicKeyHash(NvU8 *pKey);

/**
 * Reads Chip's Unique 128-bit Id (UID) from fuses
 *
 * @param pId pointer to NvBootECID where chip's Unique Id number is to be stored
 *
 * @return void (assume trusted caller, no parameter validation)
 */
void
NvBootFuseGetUniqueId(NvBootECID *pId);

/**
 * Get the SkipDevSelStraps value from fuses
 *
 * @return The SKipDevSelStraps() value.
 */
NvBool
NvBootFuseSkipDevSelStraps(void);

/**
 * Get the EnableChargerDetect value from fuses
 *
 * @return The EnableChargerDetect value.
 */
NvBool
NvBootFuseIsUsbChargerDetectionEnabled(void);

/**
 * Get Boot Device Id from fuses
 *
 * @param pDev pointer to buffer where ID of boot device is to be stored
 *
 * @return void (assume trusted caller, no parameter validation)
 */
void
NvBootFuseGetBootDevice(NvBootFuseBootDevice *pDev);

/**
 * Get Boot Device Configuration Index from fuses
 *
 * @param pConfigIndex pointer to NvU32 where boot device configuration 
 *        index is to be stored
 *
 * @return void ((assume trusted caller, no parameter validation) 
 */
void
NvBootFuseGetBootDeviceConfiguration(NvU32 *pConfigIndex);

/**
 * Get SW reserved field from fuses
 *
 * @param pSwReserved pointer to NvU32 where SwReserved field to be stored 
 *        note this is only 8 bits at this time, but could grow
 */
void
NvBootFuseGetSwReserved(NvU32 *pSwReserved); 

/**
 * Get Marketing-defined SKU ID information from fuses
 *
 * SKU ID is a subset of the full SKU field
 *
 * @param pSkuId pointer to SkuId variable
 *
 * @return void ((assume trusted caller, no parameter validation) 
 */
void
NvBootFuseGetSku(NvBootSku_SkuId *pSkuId); 

/**
 * Get SKU field from fuses
 *
 * @param pSku pointer to NvU32 variable
 *
 * @return void ((assume trusted caller, no parameter validation) 
 */
void
NvBootFuseGetSkuRaw(NvU32 *pSku); 

/**
 * Alias the fuses from the PMC scratch registers.
 */
void
NvBootFuseAliasFuses(void);

/**
 * Get Watchdog enable info from fuse
 */
NvBool
NvBootFuseIsWatchdogEnabled(void);

#if defined(__cplusplus)
}
#endif

#endif // INCLUDED_NVBOOT_FUSE_INT_H
