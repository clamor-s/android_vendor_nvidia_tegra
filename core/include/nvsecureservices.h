/*
 * Copyright (c) 2011-2013 NVIDIA Corporation.  All rights reserved.
 *
 * NVIDIA Corporation and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA Corporation is strictly prohibited.
 */

/**
 * @file nvsecureservices.h
 * @brief <b> Nv Secure Framework.</b>
 *
 * @b Description: This file declares the services offered by the
 *    secure framework.
 */

#ifndef INCLUDED_NVSECURE_SERVICES_H
#define INCLUDED_NVSECURE_SERVICES_H

#include "nverror.h"
#include "nvrm_init.h"

#ifdef __cplusplus
extern "C" {
#endif


/**
 * Defines the header corresponding to the binary file generated by
 * generateheader.py file. Modifications, if any, to this structure
 * shall be reflected in generateheader.py as well.
 */
typedef struct SecureImageHeaderRec {
    /** The load address of the secure binary */
    NvU32 LoadAddress;
    /** The execution address of the secure binary */
    NvU32 ExecutionAddress;
    /** This member is added by the python script while generating the binary
      * file corresponding to this header. If any member needs to be added, add
      * it before this element.
      */
    NvU8 LineFeedChar;
}SecureImageHeader;



/**
 * Disables the specified engine.  No further operations can be performed
 * using the AES engine until the entire chip is reset.
 *
 * @param Engine the engine to be disabled
 *
 * @retval NV_TRUE if the engine is disabled
 * @retval NV_FALSE if the engine cannot be disabled
 */
NvBool NvSecureServiceAesDisableEngine(NvU32 Engine);

/**
 * Queries whether the engine is disabled or not.
 *
 * @param Engine the queried engine
 *
 * @retval NV_TRUE if the engine is disabled
 * @retval NV_FALSE if the engine is not disabled
 */
NvBool NvSecureServiceAesIsEngineDisabled(NvU32 Engine);

/**
 * Queries the status of the engine.
 *
 * @param Engine the engine for which status is required
 *
 * @retval NV_TRUE if the engine is busy
 * @retval NV_FALSE if the engine is not busy
 */
NvBool NvSecureServiceAesIsEngineBusy(NvU32 Engine);

/**
 * Waits till the engine is idle.
 *
 * @param Engine the engine which needs to be in idle state
 *
 */
void NvSecureServiceAesWaitTillEngineIdle(NvU32 Engine);


/**
 * Sets up the key table.
 *
 * @param KeyTablePhyAddr the physical address of the keytable
 * @param Engine the AES engine to setup the Key table
 * @param Slot For which AES Key slot to use for setting up the key table
 *
 */
void
NvSecureServiceAesSetupTable(
    NvU32 KeyTablePhyAddr,
    NvU32 Engine,
    NvU32 Slot);

/**
 * Select the Key slot for updating the IV vectors.
 *
 * @param Engine the AES engine to be used
 * @param Slot the slot to be selected
 *
 */
void NvSecureServiceAesSelectKeyIvSlot(NvU32 Engine, NvU32 Slot);

/**
 * Gets the IV .
 *
 * @param Engine the AES engine to be used
 * @param Slot the slot of the engine to be used
 * @param Start the start location within the keytable
 * @param end the end location of keytable
 * @param pIvAddress the pointer to the location where the IV will be stored
 *
 */
void
NvSecureServiceAesGetIv(
    NvU32 Engine,
    NvU32 Slot,
    NvU32 Start,
    NvU32 End,
    NvU32 *pIvAddress);


/**
 * Enables/Disables the key schedule generation in hardware .
 *
 * @param Engine the engine for which the key generation neds to be disabled
 * @param Enable NV_TRUE to enable the key schedule generation, NV_FALSE otherwise
 *
 */
void NvSecureServiceAesControlKeyScheduleGeneration(NvU32 Engine, NvBool Enable);

/**
 * Lock down the permissions for SSK.
 *
 * @param Engine the engine which needs to be locked
 *
 */
void NvSecureServiceAesLockSskReadWrites(NvU32 Engine);

/**
 * Encrypts/Decrypts blocks of data
 *
 * @param Engine the engine to be used
 * @param SrcPhyAddress the physical address of source buffer
 * @param DstPhyAddress the physical address of destination buffer
 * @param NumBlocks Number of blocks in Source buffer
 * @param IsEncryption NV_TRUE if encryption else NV_FALSE
 * @param OpMode Operational mode
 *
 */
void
NvSecureServiceAesProcessBuffer(
    AesHwEngine Engine,
    NvU32 SrcPhyAddress,
    NvU32 DstPhyAddress,
    NvU32 NumBlocks,
    NvBool IsEncryption,
    NvU32 OpMode);

/**
 * Loads the SSK key into secure scratch resgister and disables the
 * write permissions
 *
 * @param pPmicBaseAddr Pointer to the PMIC base address
 * @param pKey pointer to the key
 * @param Size length of the aperture in bytes
 *
 */
void
NvSecureServiceAesLoadSskToSecureScratchAndLock(
    NvU32 PmicBaseAddr,
    NvU32 *pKey,
    size_t Size);

/**
 * This function configures the L2 cache
 *
 */
void NvSecureServiceL2CacheConfigure(void);

/**
 * This function enables/disables the L2 cache
 *
 * @param Enable NV_TRUE to enable the cache, NV_FALSE otherwise
 *
 * @return the value of the parameter passed
 */
NvBool NvSecureServiceL2CacheEnable(NvBool Enable);


/**
 * Puts the system in LP0 state.
 *
 * @param IsSimulation NV_TRUE if the binary is running on simulator
 * @param PowerState Power state to enter
 * @param pContextMemoryPA the PA of the context pointer
 * @param pRecoveryPointerPA the PA of the recovery code
 * @param NumberOfSlaves the total number of slaves active.
 *
 */
void
NvSecureServicePowerEnterLP0(
    NvBool IsSimulation,
    NvU32 PowerState,
    NvU32 *pContextMemoryPA,
    NvU32 *pRecoveryPointerPA,
    NvU32 *NumberOfSlaves);

/**
 * Puts the system in LP1 state.
 *
 * @param IsSimulation NV_TRUE if the binary is running on simulator
 * @param PowerState Power state to enter
 * @param pContextMemoryPA the PA of the context pointer
 * @param NumberOfSlaves the total number of slaves active.
 *
 */
void
NvSecureServicePowerEnterLP1(
    NvBool IsSimulation,
    NvU32 PowerState,
    NvU32 *pContextMemoryPA,
    NvU32 *NumberOfSlaves);

/**
 * Queries the size of the recovery code so as to allocate taht much of
 * buffer in non secure memory.
 *
 * @retval The size of the recovery code
 */
NvU32 NvSecureServicePowerGetRecoveryCodeSize(void);


/**
 * Test API which sets some predifined addresses with predifined values
 *
 */
void NvSecureServiceTestInitMemory(void);

/**
 * Test API to check the accessiblity of memory set by non secure binary
 *
 */
NvError NvSecureServiceTestCheckAccessiblityFromSecureBinary(void);

/**
 * Disables read access to the given key slot
 *
 * @param Engine Engine for which read access needs to be disabled
 *               for the given key slot
 * @param Slot Key slot number for which read access needs to be disabled.
 *
 * @retval None
 */
void NvSecureServiceAesKeyReadDisable(NvU32 Engine, NvU32 Slot);

/**
 * Sets the updated IV in key table.
 *
 * @param KeyTablePhyAddr the physical address of the keytable
 * @param Engine the AES engine to setup the Key table
 * @param Slot For which AES Key slot to use for setting up the Updated IV
 *
 */
void
NvSecureServiceAesSetUpdatedIv(
    NvU32 KeyTablePhyAddr,
    NvU32 Engine,
    NvU32 Slot);

/**
 * Sets the Original IV in key table.
 *
 * @param KeyTablePhyAddr the physical address of the keytable
 * @param Engine the AES engine to setup the Key table
 * @param Slot For which AES Key slot to use for setting up the original IV
 *
 */
void
NvSecureServiceAesSetOriginalIv(
    NvU32 KeyTablePhyAddr,
    NvU32 Engine,
    NvU32 Slot);

/**
 * Sets the key in key table.
 *
 * @param KeyTablePhyAddr the physical address of the keytable
 * @param Engine the AES engine to setup the Key table
 * @param Slot For which AES Key slot to use for setting up the key
 *
 */
void
NvSecureServiceAesSetKey(
    NvU32 KeyTablePhyAddr,
    NvU32 Engine,
    NvU32 Slot);

/**
 * Sets the key size.
 *
 * @param Engine the AES engine to setup the Key table
 * @param KeySize key length specified in bytes
 *
 */
void
NvSecureServiceAesSetKeySize(
    NvU32 Engine,
    NvU32 KeySize);

/**
 * Decrypts blocks of data into key slot
 *
 * @param Engine The engine to be used
 * @param SrcPhyAddress The physical address of source buffer
 * @param DestKeySlot Destination key slot where the decrypted data is stored
 * @param NumBlocks Number of blocks in Source buffer
 *
 */
void
NvSecureServiceAesDecryptToSlot(
    AesHwEngine Engine,
    NvU32 SrcPhyAddress,
    NvU32 DestKeySlot,
    NvU32 NumBlocks);

#ifdef __cplusplus
};
#endif

#endif /* INCLUDED_NVSECURE_SERVICES_H */
