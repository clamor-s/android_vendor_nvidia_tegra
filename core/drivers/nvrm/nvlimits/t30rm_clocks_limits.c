/*
 * Copyright (c) 2011-2013, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited
 */

#include "nvcommon.h"
#include "nvassert.h"
#include "nvrm_drf.h"
#include "nvrm_hwintf.h"
#include "nvrm_clocks.h"
#include "t30rm_clocks_limits_private.h"
#include "t30/project_relocation_table.h"
#include "ap15rm_private.h"
#include "t30/arapb_misc.h"
#include "t30/arfuse.h"
#include "t30/arclk_rst.h"
#include "t30/arfuse.h"

/*
 * Core voltage levels SoC clock frequency limits were characterized at
 * for each process corner. Combined pointer table arranged in order of
 * process calibration settings
 */
static const NvU32 s_T30_SS_ShmooVoltages[] = { NV_T30SS_SHMOO_VOLTAGES };
static const NvU32 s_T30_ST_ShmooVoltages[] = { NV_T30ST_SHMOO_VOLTAGES };
static const NvU32 s_T30_FT_ShmooVoltages[] = { NV_T30FT_SHMOO_VOLTAGES };
static const NvU32 s_T30_FF_ShmooVoltages[] = { NV_T30FF_SHMOO_VOLTAGES };
NV_CT_ASSERT(NV_ARRAY_SIZE(s_T30_SS_ShmooVoltages) == NV_ARRAY_SIZE(s_T30_ST_ShmooVoltages));
NV_CT_ASSERT(NV_ARRAY_SIZE(s_T30_SS_ShmooVoltages) == NV_ARRAY_SIZE(s_T30_FT_ShmooVoltages));
NV_CT_ASSERT(NV_ARRAY_SIZE(s_T30_SS_ShmooVoltages) == NV_ARRAY_SIZE(s_T30_FF_ShmooVoltages));
NV_CT_ASSERT(NV_ARRAY_SIZE(s_T30_SS_ShmooVoltages) <= NVRM_VOLTAGE_STEPS);

static const NvU32* s_pT30_ShmooVoltages[] =
{
    &s_T30_SS_ShmooVoltages[0],     /* Calibration setting 0 - SS corner */
    &s_T30_ST_ShmooVoltages[0],     /* Calibration setting 1 - ST corner */
    &s_T30_FT_ShmooVoltages[0],     /* Calibration setting 2 - FT corner */
    &s_T30_FF_ShmooVoltages[0]      /* Calibration setting 3 - FF corner */
};
NV_CT_ASSERT(NV_ARRAY_SIZE(s_pT30_ShmooVoltages) == NV_T30_PROCESS_CORNERS);

/*
 * Module clock frequency limits table generated by h/w characterization for
 * each process corner (each table entry includes h/w device id and applies
 * to all instances of the respective device). Combined pointer table arranged
 * in order of process calibration settings
 */
static const NvRmScaledClkLimits s_T30_SS_ScaledClkLimits[] = { NV_T30SS_SCALED_CLK_LIMITS };
static const NvRmScaledClkLimits s_T30_ST_ScaledClkLimits[] = { NV_T30ST_SCALED_CLK_LIMITS };
static const NvRmScaledClkLimits s_T30_FT_ScaledClkLimits[] = { NV_T30FT_SCALED_CLK_LIMITS };
static const NvRmScaledClkLimits s_T30_FF_ScaledClkLimits[] = { NV_T30FF_SCALED_CLK_LIMITS };
NV_CT_ASSERT(NV_ARRAY_SIZE(s_T30_SS_ScaledClkLimits) == NV_ARRAY_SIZE(s_T30_ST_ScaledClkLimits));
NV_CT_ASSERT(NV_ARRAY_SIZE(s_T30_SS_ScaledClkLimits) == NV_ARRAY_SIZE(s_T30_FT_ScaledClkLimits));
NV_CT_ASSERT(NV_ARRAY_SIZE(s_T30_SS_ScaledClkLimits) == NV_ARRAY_SIZE(s_T30_FF_ScaledClkLimits));

static const NvRmScaledClkLimits* s_pT30_ScaledClkLimits[] =
{
    &s_T30_SS_ScaledClkLimits[0],     /* Calibration setting 0 - SS corner */
    &s_T30_ST_ScaledClkLimits[0],     /* Calibration setting 1 - ST corner */
    &s_T30_FT_ScaledClkLimits[0],     /* Calibration setting 2 - FT corner */
    &s_T30_FF_ScaledClkLimits[0]      /* Calibration setting 3 - FF corner */
};
NV_CT_ASSERT(NV_ARRAY_SIZE(s_pT30_ScaledClkLimits) == NV_T30_PROCESS_CORNERS);

/*
 * CPU voltage levels used for CPU frequency limits characterization and the
 * respective characterization results for all CPU process corners (arranged
 * in order of process calibration settings)
 */
static const NvU32 s_T30_SS_CpuVoltages[] = { NV_T30SS_CPU_VOLTAGES };
static const NvU32 s_T30_ST_CpuVoltages[] = { NV_T30ST_CPU_VOLTAGES };
static const NvU32 s_T30_FT_CpuVoltages[] = { NV_T30FT_CPU_VOLTAGES };
static const NvU32 s_T30_FF_CpuVoltages[] = { NV_T30FF_CPU_VOLTAGES };
NV_CT_ASSERT(NV_ARRAY_SIZE(s_T30_SS_CpuVoltages) == NV_ARRAY_SIZE(s_T30_ST_CpuVoltages));
NV_CT_ASSERT(NV_ARRAY_SIZE(s_T30_SS_CpuVoltages) == NV_ARRAY_SIZE(s_T30_FT_CpuVoltages));
NV_CT_ASSERT(NV_ARRAY_SIZE(s_T30_SS_CpuVoltages) == NV_ARRAY_SIZE(s_T30_FF_CpuVoltages));
NV_CT_ASSERT(NV_ARRAY_SIZE(s_T30_SS_CpuVoltages) <= NVRM_VOLTAGE_STEPS);

static const NvU32* s_pT30_CpuVoltages[] =
{
    &s_T30_SS_CpuVoltages[0],     /* Calibration setting 0 - SS CPU corner */
    &s_T30_ST_CpuVoltages[0],     /* Calibration setting 1 - ST CPU corner */
    &s_T30_FT_CpuVoltages[0],     /* Calibration setting 2 - FT CPU corner */
    &s_T30_FF_CpuVoltages[0],     /* Calibration setting 3 - FF CPU corner */
};
NV_CT_ASSERT(NV_ARRAY_SIZE(s_pT30_CpuVoltages) == NV_T30_PROCESS_CORNERS);

static const NvRmScaledClkLimits s_T30_ScaledCpuClkLimits[] =
{
    NV_T30SS_SCALED_CPU_CLK_LIMITS,
    NV_T30ST_SCALED_CPU_CLK_LIMITS,
    NV_T30FT_SCALED_CPU_CLK_LIMITS,
    NV_T30FF_SCALED_CPU_CLK_LIMITS,
};
NV_CT_ASSERT(NV_ARRAY_SIZE(s_T30_ScaledCpuClkLimits) == NV_T30_PROCESS_CORNERS);

/*
 * For Automotive
 */

static const NvU32 s_T30_SS_Auto_CpuVoltages[] = { NV_T30SS_AUTOMOTIVE_CPU_VOLTAGES };
static const NvU32 s_T30_ST_Auto_CpuVoltages[] = { NV_T30ST_AUTOMOTIVE_CPU_VOLTAGES };
static const NvU32 s_T30_FT_Auto_CpuVoltages[] = { NV_T30FT_AUTOMOTIVE_CPU_VOLTAGES };
static const NvU32 s_T30_FF_Auto_CpuVoltages[] = { NV_T30FF_AUTOMOTIVE_CPU_VOLTAGES };
NV_CT_ASSERT(NV_ARRAY_SIZE(s_T30_SS_Auto_CpuVoltages) == NV_ARRAY_SIZE(s_T30_ST_Auto_CpuVoltages));
NV_CT_ASSERT(NV_ARRAY_SIZE(s_T30_SS_Auto_CpuVoltages) == NV_ARRAY_SIZE(s_T30_FT_Auto_CpuVoltages));
NV_CT_ASSERT(NV_ARRAY_SIZE(s_T30_SS_Auto_CpuVoltages) == NV_ARRAY_SIZE(s_T30_FF_Auto_CpuVoltages));
NV_CT_ASSERT(NV_ARRAY_SIZE(s_T30_SS_Auto_CpuVoltages) <= NVRM_VOLTAGE_STEPS);

static const NvU32* s_pT30_Auto_CpuVoltages[] =
{
    &s_T30_SS_Auto_CpuVoltages[0],     /* Calibration setting 0 - SS CPU corner */
    &s_T30_ST_Auto_CpuVoltages[0],     /* Calibration setting 1 - ST CPU corner */
    &s_T30_FT_Auto_CpuVoltages[0],     /* Calibration setting 2 - FT CPU corner */
    &s_T30_FF_Auto_CpuVoltages[0],     /* Calibration setting 3 - FF CPU corner */
};
NV_CT_ASSERT(NV_ARRAY_SIZE(s_pT30_Auto_CpuVoltages) == NV_T30_PROCESS_CORNERS);

static const NvRmScaledClkLimits s_T30_Auto_ScaledCpuClkLimits[] =
{
    NV_T30SS_AUTOMOTIVE_SCALED_CPU_CLK_LIMITS,
    NV_T30ST_AUTOMOTIVE_SCALED_CPU_CLK_LIMITS,
    NV_T30FT_AUTOMOTIVE_SCALED_CPU_CLK_LIMITS,
    NV_T30FF_AUTOMOTIVE_SCALED_CPU_CLK_LIMITS,
};
NV_CT_ASSERT(NV_ARRAY_SIZE(s_T30_Auto_ScaledCpuClkLimits) == NV_T30_PROCESS_CORNERS);

/*
 * Maximum frequency limits table for clocks depended on SoC SKU;
 * ordered by SKU number
 */
static const struct
{
    NvRmSKUedLimits limits;
    NvU32 sku;
} s_T30_SKUedLimits[] =
{
    NV_T30_SKUED_LIMITS
};

/**
 * OSC Doubler tap delays for each supported frequency in order
 * of process calibration settings
 */
static const NvRmOscDoublerConfig s_T30_OscDoublerConfigurations[] =
{
    NV_T30_OSC_DOUBLER_CONFIGURATIONS
};

/**
 * EMC DQSIB offsets in order of process calibration settings
 */
static const NvU32 s_T30_DqsibOffsets[] =
{
    NV_T30_DQSIB_OFFSETS
};
NV_CT_ASSERT(NV_ARRAY_SIZE(s_T30_DqsibOffsets) == NV_T30_PROCESS_CORNERS);
NV_CT_ASSERT(NV_T30_PROCESS_CORNERS <= NVRM_PROCESS_CORNERS);

/*
 * Combined SoC characterization data record
 */
static NvRmSocShmoo s_T30_SocShmoo = {0};
static NvRmCpuShmoo s_T30_CpuShmoo = {0};

NvError NvRmPrivChipShmooDataInit(
    NvRmDeviceHandle hRmDevice,
    NvRmChipFlavor* pChipFlavor)
{
    NvU32 i;
    NvU32 auto_skus[] = NV_T30_AUTOMOTIVE_SKUS;

    // Read chip ID
    NvRmChipId ChipId;
    NvU32 reg = NV_REGR(hRmDevice, NVRM_MODULE_ID(NvRmModuleID_Misc, 0),
        APB_MISC_GP_HIDREV_0);
    ChipId.Id = (NvU16)NV_DRF_VAL(APB_MISC_GP, HIDREV, CHIPID, reg );
    ChipId.Major = (NvU8)NV_DRF_VAL(APB_MISC_GP, HIDREV, MAJORREV, reg );
    ChipId.Minor = (NvU8)NV_DRF_VAL(APB_MISC_GP, HIDREV, MINORREV, reg );

    if (ChipId.Major != 0)
    {
        pChipFlavor->sku = (NvU16)NV_DRF_VAL(FUSE, SKU_INFO, SKU_INFO,
            NV_REGR(hRmDevice, NVRM_MODULE_ID( NvRmModuleID_Fuse, 0 ),
                FUSE_SKU_INFO_0));

        for (i = 0; i < NV_ARRAY_SIZE(s_T30_SKUedLimits); i++)
        {
            if (s_T30_SKUedLimits[i].sku == pChipFlavor->sku)
                break;
        }
        if (i == NV_ARRAY_SIZE(s_T30_SKUedLimits))
            pChipFlavor->sku = 0;

        pChipFlavor->corner = 0;
        pChipFlavor->CpuCorner = 0;
    }
    else
    {
        /* FPGA/Simulation */
        pChipFlavor->sku = 0;
        pChipFlavor->corner = 0;
        pChipFlavor->CpuCorner = 0;
    }
    NV_ASSERT(pChipFlavor->corner < NV_T30_PROCESS_CORNERS);
    NV_ASSERT(pChipFlavor->CpuCorner < NV_T30_PROCESS_CORNERS);
    NvOsMemset((void*)&s_T30_SocShmoo, 0, sizeof(s_T30_SocShmoo));
    NvOsMemset((void*)&s_T30_CpuShmoo, 0, sizeof(s_T30_CpuShmoo));

    // Fill in SKUed limits for the chip at hand
    for (i = 0; i < NV_ARRAY_SIZE(s_T30_SKUedLimits); i++)
    {
        if (s_T30_SKUedLimits[i].sku == pChipFlavor->sku)
            break;
    }
    NV_ASSERT(i < NV_ARRAY_SIZE(s_T30_SKUedLimits));
    s_T30_SocShmoo.pSKUedLimits = &s_T30_SKUedLimits[i].limits;

    // Fill in core rail characterization data for the chip at hand
    s_T30_SocShmoo.ShmooVoltages = s_pT30_ShmooVoltages[pChipFlavor->corner];
    for (i = 0; i < NV_ARRAY_SIZE(s_T30_SS_ShmooVoltages); i++)
    {
        if (s_T30_SocShmoo.ShmooVoltages[i] ==
            s_T30_SocShmoo.pSKUedLimits->NominalCoreMv)
            break;
    }
    if(i >= NV_ARRAY_SIZE(s_T30_SS_ShmooVoltages))
    {
        NV_ASSERT(!"Nominal voltage not found");
        i = NV_ARRAY_SIZE(s_T30_SS_ShmooVoltages) - 1;  // use max shmoo volt
    }
    s_T30_SocShmoo.ShmooVmaxIndex = i;

    s_T30_SocShmoo.ScaledLimitsList =
        s_pT30_ScaledClkLimits[pChipFlavor->corner];
    s_T30_SocShmoo.ScaledLimitsListSize =
        NV_ARRAY_SIZE(s_T30_SS_ScaledClkLimits);

    s_T30_SocShmoo.OscDoublerCfgList =
        &s_T30_OscDoublerConfigurations[0];
    s_T30_SocShmoo.OscDoublerCfgListSize =
        NV_ARRAY_SIZE(s_T30_OscDoublerConfigurations);

    NV_ASSERT(pChipFlavor->corner < NV_ARRAY_SIZE(s_T30_DqsibOffsets));
    s_T30_SocShmoo.DqsibOffset = s_T30_DqsibOffsets[pChipFlavor->corner];

    s_T30_SocShmoo.SvopLowVoltage = NV_T30_SVOP_LOW_VOLTAGE;
    s_T30_SocShmoo.SvopLowSetting = NV_T30_SVOP_LOW_SETTING;
    s_T30_SocShmoo.SvopHighSetting = NV_T30_SVOP_HIGH_SETTING;

    pChipFlavor->pSocShmoo = &s_T30_SocShmoo;

    //identify if its an Automotive SKU.
    for (i = 0; i < NV_ARRAY_SIZE(auto_skus); i++)
    {
        if (pChipFlavor->sku == auto_skus[i])
            break;
    }

    // Fill in dedicated CPU rail characterization data for the chip at hand
    if (i < NV_ARRAY_SIZE(auto_skus))
    {
        s_T30_CpuShmoo.ShmooVoltages = s_pT30_Auto_CpuVoltages[pChipFlavor->CpuCorner];
        s_T30_CpuShmoo.pScaledCpuLimits =
            &s_T30_Auto_ScaledCpuClkLimits[pChipFlavor->CpuCorner];
        s_T30_CpuShmoo.ShmooVmaxIndex = (NV_ARRAY_SIZE(s_T30_SS_Auto_CpuVoltages) -1);
    } else
    {
        s_T30_CpuShmoo.ShmooVoltages = s_pT30_CpuVoltages[pChipFlavor->CpuCorner];
        s_T30_CpuShmoo.pScaledCpuLimits =
            &s_T30_ScaledCpuClkLimits[pChipFlavor->CpuCorner];
        s_T30_CpuShmoo.ShmooVmaxIndex = (NV_ARRAY_SIZE(s_T30_SS_CpuVoltages) -1);
    }

    for (i = 0; i < s_T30_CpuShmoo.ShmooVmaxIndex; i++)
    {
        if ((s_T30_CpuShmoo.pScaledCpuLimits->MaxKHzList[i + 1] == 0) ||
            (s_T30_CpuShmoo.pScaledCpuLimits->MaxKHzList[i] >=
             s_T30_SocShmoo.pSKUedLimits->CpuMaxKHz))
            break;
    }
    s_T30_CpuShmoo.ShmooVmaxIndex = i;
    NV_ASSERT(s_T30_CpuShmoo.ShmooVoltages[i] <=
              s_T30_SocShmoo.pSKUedLimits->NominalCpuMv);
    NV_ASSERT(s_T30_CpuShmoo.pScaledCpuLimits->MaxKHzList[i] >=
              s_T30_SocShmoo.pSKUedLimits->CpuMaxKHz);

    pChipFlavor->pCpuShmoo = &s_T30_CpuShmoo;
    return NvSuccess;
}
