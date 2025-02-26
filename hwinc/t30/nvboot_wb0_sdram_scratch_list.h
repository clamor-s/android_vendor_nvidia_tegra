/*
 * Copyright (c) 2010 NVIDIA Corporation.  All rights reserved.
 *
 * NVIDIA Corporation and its licensors retain all intellectual property
 * and proprietary rights in and to this software and related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA Corporation is strictly prohibited.
 */

/**
 * @file nvboot_wb0_sdram_scratch_list.h
 *
 * List macro which defines the scratch register <-> NvBootSdramParams mapping.
 */

#ifndef INCLUDED_NVBOOT_WB0_SDRAM_SCRATCH_LIST_H
#define INCLUDED_NVBOOT_WB0_SDRAM_SCRATCH_LIST_H

#if defined(__cplusplus)
extern "C"
{
#endif

/**
 * SDRAM_PMC_FIELDS(_) - A list macro which defines the information needed
 *     when processing SDRAM parameters stored in PMC scratch registers.
 *
 * Each entry defines (n, d, r, f, p):
 *   @param n scratch register number
 *   @param d register domain (hardware block)
 *   @param r register name
 *   @param f register field
 *   @param p field name in NvBootSdramParams structure
 */

// SDRAM register field packing list generated by tool warmboot_code_gen
#define SDRAM_PMC_FIELDS(_) \
    _( 5, EMC, WARM_BOOT_EMR3, EMRS_ADR, EmcWarmBootEmr3) \
    _( 5, EMC, WARM_BOOT_EMR2, EMRS_ADR, EmcWarmBootEmr2) \
    _( 5, EMC, WARM_BOOT_EMR3, EMRS_BA, EmcWarmBootEmr3) \
    _( 5, EMC, WARM_BOOT_EMR2, EMRS_BA, EmcWarmBootEmr2) \
    _( 6, EMC, WARM_BOOT_MRS_EXTRA, MRS_ADR, EmcWarmBootMrsExtra) \
    _( 6, EMC, WARM_BOOT_MRS, MRS_ADR, EmcWarmBootMrs) \
    _( 6, EMC, WARM_BOOT_MRS_EXTRA, MRS_BA, EmcWarmBootMrsExtra) \
    _( 6, EMC, WARM_BOOT_MRS, MRS_BA, EmcWarmBootMrs) \
    _( 7, EMC, WARM_BOOT_EMRS, EMRS_ADR, EmcWarmBootEmrs) \
    _( 7, EMC, WARM_BOOT_EMRS, EMRS_BA, EmcWarmBootEmrs) \
    _( 7, EMC, WARM_BOOT_EMR3, USE_EMRS_LONG_CNT, EmcWarmBootEmr3) \
    _( 7, EMC, WARM_BOOT_EMR2, USE_EMRS_LONG_CNT, EmcWarmBootEmr2) \
    _( 7, EMC, WARM_BOOT_MRS_EXTRA, USE_MRS_LONG_CNT, EmcWarmBootMrsExtra) \
    _( 7, EMC, WARM_BOOT_MRS, USE_MRS_LONG_CNT, EmcWarmBootMrs) \
    _( 7, EMC, WARM_BOOT_EMRS, USE_EMRS_LONG_CNT, EmcWarmBootEmrs) \
    _( 7, EMC, ZQ_CAL_DDR3_WARM_BOOT, ZQ_CAL_CMD, EmcZqCalDdr3WarmBoot) \
    _( 7, EMC, ZQ_CAL_DDR3_WARM_BOOT, ZQ_CAL_LENGTH, EmcZqCalDdr3WarmBoot) \
    _( 7, EMC, RFC, RFC, EmcRfc) \
    _( 8, EMC, CFG_DIG_DLL, CFG_DLL_EN, EmcCfgDigDll) \
    _( 8, EMC, CFG_DIG_DLL, CFG_DLL_OVERRIDE_EN, EmcCfgDigDll) \
    _( 8, EMC, CFG_DIG_DLL, CFG_DLL_STALL_RW_UNTIL_LOCK, EmcCfgDigDll) \
    _( 8, EMC, CFG_DIG_DLL, CFG_DLL_LOWSPEED, EmcCfgDigDll) \
    _( 8, EMC, CFG_DIG_DLL, CFG_DLL_MODE, EmcCfgDigDll) \
    _( 8, EMC, CFG_DIG_DLL, CFG_DLL_UDSET, EmcCfgDigDll) \
    _( 8, EMC, CFG_DIG_DLL, CFG_DLL_OVERRIDE_VAL, EmcCfgDigDll) \
    _( 8, EMC, CFG_DIG_DLL, CFG_DLL_ALARM_DISABLE, EmcCfgDigDll) \
    _( 8, EMC, CFG_DIG_DLL, CFG_DLL_LOCK_LIMIT, EmcCfgDigDll) \
    _( 8, EMC, XM2CMDPADCTRL, EMC2TMC_CFG_XM2CMD_E_PREEMP, EmcXm2CmdPadCtrl) \
    _( 8, EMC, XM2CMDPADCTRL, CFG_XM2CMD_CAL_SELECT, EmcXm2CmdPadCtrl) \
    _( 8, EMC, XM2CMDPADCTRL, EMC2PMACRO_CFG_XM2CMD_DIGTRIM, EmcXm2CmdPadCtrl) \
    _( 9, EMC, DLL_XFORM_DQS0, XFORM_DQS0_MULT, EmcDllXformDqs0) \
    _( 9, EMC, DLL_XFORM_DQS0, XFORM_DQS0_OFFS, EmcDllXformDqs0) \
    _( 9, EMC, XM2CLKPADCTRL, EMC2PMACRO_CFG_DYN_PULLS_ON_CLKDIS, EmcXm2ClkPadCtrl) \
    _( 9, EMC, XM2CLKPADCTRL, EMC2TMC_CFG_XM2CLK_E_PREEMP, EmcXm2ClkPadCtrl) \
    _( 9, EMC, XM2CLKPADCTRL, EMC2PMACRO_CFG_XM2CLK_DRVDN, EmcXm2ClkPadCtrl) \
    _( 9, EMC, XM2CLKPADCTRL, EMC2PMACRO_CFG_XM2CLK_DRVUP, EmcXm2ClkPadCtrl) \
    _(10, EMC, DLL_XFORM_QUSE0, XFORM_QUSE0_MULT, EmcDllXformQUse0) \
    _(10, EMC, DLL_XFORM_QUSE0, XFORM_QUSE0_OFFS, EmcDllXformQUse0) \
    _(10, EMC, AUTO_CAL_CONFIG, AUTO_CAL_PU_OFFSET, EmcAutoCalConfig) \
    _(10, EMC, AUTO_CAL_CONFIG, AUTO_CAL_PD_OFFSET, EmcAutoCalConfig) \
    _(10, EMC, AUTO_CAL_CONFIG, AUTO_CAL_OVERRIDE, EmcAutoCalConfig) \
    _(10, EMC, CFG, PERIODIC_QRST, EmcCfg) \
    _(11, EMC, DLL_XFORM_DQ0, XFORM_TXDQ0_MULT, EmcDllXformDq0) \
    _(11, EMC, DLL_XFORM_DQ0, XFORM_TXDQ0_OFFS, EmcDllXformDq0) \
    _(11, EMC, SEL_DPD_CTRL, POP_CLK_SEL_DPD_EN, EmcSelDpdCtrl) \
    _(11, EMC, SEL_DPD_CTRL, POP_CA_SEL_DPD_EN, EmcSelDpdCtrl) \
    _(11, EMC, SEL_DPD_CTRL, CLK_SEL_DPD_EN, EmcSelDpdCtrl) \
    _(11, EMC, SEL_DPD_CTRL, CA_SEL_DPD_EN, EmcSelDpdCtrl) \
    _(11, EMC, SEL_DPD_CTRL, RESET_SEL_DPD_EN, EmcSelDpdCtrl) \
    _(11, EMC, SEL_DPD_CTRL, ODT_SEL_DPD_EN, EmcSelDpdCtrl) \
    _(11, EMC, SEL_DPD_CTRL, DATA_SEL_DPD_EN, EmcSelDpdCtrl) \
    _(11, EMC, SEL_DPD_CTRL, QUSE_SEL_DPD_EN, EmcSelDpdCtrl) \
    _(11, EMC, SEL_DPD_CTRL, SEL_DPD_DLY, EmcSelDpdCtrl) \
    _(11, EMC, ADR_CFG, EMEM_ROW_MSB_ON_CS1, EmcAdrCfg) \
    _(12, EMC, CFG_2, EARLY_TRFC_8_CLK, EmcCfg2) \
    _(12, EMC, CFG_2, PIN_CONFIG, EmcCfg2) \
    _(12, EMC, CFG_2, DONT_GEN_EARLY_TRFC_DONE, EmcCfg2) \
    _(12, EMC, CFG_2, ACPD_WAKEUP_NO_COND, EmcCfg2) \
    _(12, EMC, CFG_2, USE_PER_DEVICE_DLY_TRIM_IB, EmcCfg2) \
    _(12, EMC, CFG_2, USE_PER_DEVICE_DLY_TRIM_OB, EmcCfg2) \
    _(12, EMC, CFG_2, DONT_GEN_EARLY_MRS_DONE, EmcCfg2) \
    _(12, EMC, CFG_2, BYPASS_POP_PIPE1_STAGE, EmcCfg2) \
    _(12, EMC, CFG_2, BYPASS_POP_PIPE2_STAGE, EmcCfg2) \
    _(12, EMC, CFG_2, ISSUE_PCHGALL_AFTER_REF, EmcCfg2) \
    _(12, EMC, CFG_2, DONT_USE_REF_REQACK_IFC, EmcCfg2) \
    _(12, EMC, CFG_2, ALLOW_REF_DURING_CC_PRE_EXE, EmcCfg2) \
    _(12, EMC, CFG_2, DRAMC_WD_CHK_POLICY, EmcCfg2) \
    _(12, EMC, CFG_2, DONT_CLR_TIMING_COUNTER_WHEN_CLKCHANGE, EmcCfg2) \
    _(12, EMC, CFG_2, CLR_ACT_BANK_INUSE_WHEN_BANK_CLOSE, EmcCfg2) \
    _(12, EMC, CFG_2, IGNORE_MC_A_BUS, EmcCfg2) \
    _(12, EMC, TREFBW, TREFBW, EmcTRefBw) \
    _(13, EMC, ZCAL_MRW_CMD, ZQ_MRW_OP, EmcZcalMrwCmd) \
    _(13, EMC, ZCAL_MRW_CMD, ZQ_MRW_MA, EmcZcalMrwCmd) \
    _(13, EMC, DLL_XFORM_DQS1, XFORM_DQS1_OFFS, EmcDllXformDqs1) \
    _(13, MC, EMEM_ADR_CFG, EMEM_NUMDEV, McEmemAdrCfg) \
    _(14, EMC, DLL_XFORM_DQS2, XFORM_DQS2_OFFS, EmcDllXformDqs2) \
    _(14, EMC, DLL_XFORM_DQS3, XFORM_DQS3_OFFS, EmcDllXformDqs3) \
    _(15, EMC, DLL_XFORM_DQS4, XFORM_DQS4_OFFS, EmcDllXformDqs4) \
    _(15, EMC, DLL_XFORM_DQS5, XFORM_DQS5_OFFS, EmcDllXformDqs5) \
    _(16, EMC, DLL_XFORM_DQS6, XFORM_DQS6_OFFS, EmcDllXformDqs6) \
    _(16, EMC, DLL_XFORM_DQS7, XFORM_DQS7_OFFS, EmcDllXformDqs7) \
    _(16, MC, EMEM_ARB_MISC0, MC_EMC_SAME_FREQ, McEmemArbMisc0) \
    _(17, EMC, DLL_XFORM_QUSE1, XFORM_QUSE1_OFFS, EmcDllXformQUse1) \
    _(17, EMC, DLL_XFORM_QUSE2, XFORM_QUSE2_OFFS, EmcDllXformQUse2) \
    _(18, EMC, DLL_XFORM_QUSE3, XFORM_QUSE3_OFFS, EmcDllXformQUse3) \
    _(18, EMC, DLL_XFORM_QUSE4, XFORM_QUSE4_OFFS, EmcDllXformQUse4) \
    _(19, EMC, DLL_XFORM_QUSE5, XFORM_QUSE5_OFFS, EmcDllXformQUse5) \
    _(19, EMC, DLL_XFORM_QUSE6, XFORM_QUSE6_OFFS, EmcDllXformQUse6) \
    _(19, EMC, FBIO_CFG5, DRAM_TYPE, EmcFbioCfg5) \
    _(22, EMC, DLL_XFORM_QUSE7, XFORM_QUSE7_OFFS, EmcDllXformQUse7) \
    _(22, EMC, DLL_XFORM_DQ1, XFORM_TXDQ1_OFFS, EmcDllXformDq1) \
    _(22, EMC, FBIO_CFG5, DRAM_BURST, EmcFbioCfg5) \
    _(23, EMC, DLL_XFORM_DQ2, XFORM_TXDQ2_OFFS, EmcDllXformDq2) \
    _(23, EMC, DLL_XFORM_DQ3, XFORM_TXDQ3_OFFS, EmcDllXformDq3) \
    _(24, EMC, ZCAL_INTERVAL, ZCAL_INTERVAL_HI, EmcZcalInterval) \
    _(24, EMC, XM2DQSPADCTRL2, EMC2TMC_CFG_XM2DQS_E_RX_FT_REC, EmcXm2DqsPadCtrl2) \
    _(24, EMC, XM2DQSPADCTRL2, EMC2TMC_CFG_XM2DQS_E_PREEMP, EmcXm2DqsPadCtrl2) \
    _(24, EMC, XM2DQSPADCTRL2, EMC2TMC_CFG_XM2DQS_E_CTT_HIZ_DQ, EmcXm2DqsPadCtrl2) \
    _(24, EMC, XM2DQSPADCTRL2, EMC2TMC_CFG_XM2DQS_E_CTT_HIZ_DQS, EmcXm2DqsPadCtrl2) \
    _(24, EMC, XM2DQSPADCTRL2, EMC2TMC_CFG_XM2DQS_E_VREF_DQ, EmcXm2DqsPadCtrl2) \
    _(24, EMC, XM2DQSPADCTRL2, EMC2TMC_CFG_XM2DQS_RX_DLI_EN, EmcXm2DqsPadCtrl2) \
    _(24, EMC, XM2DQSPADCTRL2, EMC2TMC_CFG_XM2DQS_TXDQ_DLI_EN, EmcXm2DqsPadCtrl2) \
    _(24, EMC, XM2DQSPADCTRL2, EMC2TMC_CFG_XM2DQS_TXDQS_DLI_EN, EmcXm2DqsPadCtrl2) \
    _(24, EMC, XM2DQSPADCTRL2, EMC2TMC_CFG_XM2DQS_QUSE_DLI_EN, EmcXm2DqsPadCtrl2) \
    _(24, EMC, XM2DQSPADCTRL2, EMC2TMC_CFG_XM2DQS_E_SCHMT, EmcXm2DqsPadCtrl2) \
    _(24, EMC, XM2DQSPADCTRL2, EMC2TMC_CFG_XM2DQS_VREF_DQ, EmcXm2DqsPadCtrl2) \
    _(24, EMC, RRD, RRD, EmcRrd) \
    _(25, EMC, XM2VTTGENPADCTRL, EMC2TMC_CFG_XM2VTTGEN_SHORT, EmcXm2VttGenPadCtrl) \
    _(25, EMC, XM2VTTGENPADCTRL, EMC2TMC_CFG_XM2VTTGEN_VCLAMP_LEVEL, EmcXm2VttGenPadCtrl) \
    _(25, EMC, XM2VTTGENPADCTRL, EMC2TMC_CFG_XM2VTTGEN_VAUXP_LEVEL, EmcXm2VttGenPadCtrl) \
    _(25, EMC, XM2VTTGENPADCTRL, EMC2TMC_CFG_XM2VTTGEN_DRVDN, EmcXm2VttGenPadCtrl) \
    _(25, EMC, XM2VTTGENPADCTRL, EMC2TMC_CFG_XM2VTTGEN_DRVUP, EmcXm2VttGenPadCtrl) \
    _(25, MC, EMEM_ARB_OVERRIDE, ARB_EMEM_AP_OVERRIDE, McEmemArbOverride) \
    _(25, MC, EMEM_ARB_OVERRIDE, ARB_HUM_FIFO_OVERRIDE, McEmemArbOverride) \
    _(25, MC, EMEM_ARB_OVERRIDE, ARB_EMEM_COALESCE_OVERRIDE, McEmemArbOverride) \
    _(25, MC, EMEM_ARB_OVERRIDE, ALLOC_ONE_BQ_PER_CLIENT, McEmemArbOverride) \
    _(25, MC, EMEM_ARB_OVERRIDE, OBSERVED_DIRECTION_OVERRIDE, McEmemArbOverride) \
    _(25, MC, EMEM_ARB_OVERRIDE, OVERRIDE_RESERVED_BYTE0, McEmemArbOverride) \
    _(25, EMC, RAS, RAS, EmcRas) \
    _(26, EMC, REFRESH, REFRESH, EmcRefresh) \
    _(26, EMC, ZCAL_WAIT_CNT, ZCAL_WAIT_CNT, EmcZcalWaitCnt) \
    _(26, EMC, XM2VTTGENPADCTRL2, EMC2TMC_CFG_XM2VTTGEN_E_NO_VTTGEN, EmcXm2VttGenPadCtrl2) \
    _(26, EMC, XM2VTTGENPADCTRL2, EMC2TMC_CFG_XM2VTTGEN_MEMCLK_E_TEST_BIAS, EmcXm2VttGenPadCtrl2) \
    _(26, EMC, XM2VTTGENPADCTRL2, EMC2TMC_CFG_XM2VTTGEN_MEM_E_TEST_BIAS, EmcXm2VttGenPadCtrl2) \
    _(26, EMC, XM2VTTGENPADCTRL2, EMC2TMC_CFG_XM2VTTGEN_MEM2_E_TEST_BIAS, EmcXm2VttGenPadCtrl2) \
    _(26, EMC, FBIO_CFG6, CFG_QUSE_LATE, EmcFbioCfg6) \
    _(27, EMC, XM2QUSEPADCTRL, EMC2TMC_CFG_XM2QUSE_E_RX_FT_REC, EmcXm2QUsePadCtrl) \
    _(27, EMC, XM2QUSEPADCTRL, EMC2TMC_CFG_XM2QUSE_E_PREEMP, EmcXm2QUsePadCtrl) \
    _(27, EMC, XM2QUSEPADCTRL, EMC2TMC_CFG_XM2QUSE_E_CTT_HIZ, EmcXm2QUsePadCtrl) \
    _(27, EMC, XM2QUSEPADCTRL, EMC2TMC_CFG_XM2QUSE_E_IVREF, EmcXm2QUsePadCtrl) \
    _(27, EMC, XM2QUSEPADCTRL, EMC2TMC_CFG_XM2QUSE_E_SCHMT, EmcXm2QUsePadCtrl) \
    _(27, EMC, XM2QUSEPADCTRL, EMC2TMC_CFG_XM2QUSE_VREF, EmcXm2QUsePadCtrl) \
    _(27, MC, EMEM_ADR_CFG_DEV0, EMEM_DEV0_COLWIDTH, McEmemAdrCfgDev0) \
    _(27, MC, EMEM_ADR_CFG_DEV0, EMEM_DEV0_BANKWIDTH, McEmemAdrCfgDev0) \
    _(27, MC, EMEM_ADR_CFG_DEV0, EMEM_DEV0_DEVSIZE, McEmemAdrCfgDev0) \
    _(27, MC, EMEM_ADR_CFG_DEV1, EMEM_DEV1_COLWIDTH, McEmemAdrCfgDev1) \
    _(27, MC, EMEM_ADR_CFG_DEV1, EMEM_DEV1_BANKWIDTH, McEmemAdrCfgDev1) \
    _(27, MC, EMEM_ADR_CFG_DEV1, EMEM_DEV1_DEVSIZE, McEmemAdrCfgDev1) \
    _(27, EMC, R2W, R2W, EmcR2w) \
    _(28, EMC, FBIO_SPARE, CFG_FBIO_SPARE_3, EmcFbioSpare) \
    _(28, EMC, CFG_RSV, CFG_RESERVED_BYTE0, EmcCfgRsv) \
    _(28, EMC, XM2COMPPADCTRL, EMC2TMC_CFG_XM2COMP_VREF_SEL, EmcXm2CompPadCtrl) \
    _(28, EMC, XM2COMPPADCTRL, EMC2TMC_CFG_XM2COMP_BIAS_SEL, EmcXm2CompPadCtrl) \
    _(28, EMC, XM2COMPPADCTRL, CFG_XM2COMP_VREF_CAL_EN, EmcXm2CompPadCtrl) \
    _(28, MC, EMEM_ARB_RSV, EMEM_ARB_RESERVED_BYTE0, McEmemArbRsv) \
    _(30, EMC, RC, RC, EmcRc) \
    _(30, EMC, DLI_TRIM_TXDQS0, EMC2PMACRO_CFG_TXDQS0_DLI, EmcDliTrimTxDqs0) \
    _(30, EMC, DLI_TRIM_TXDQS1, EMC2PMACRO_CFG_TXDQS1_DLI, EmcDliTrimTxDqs1) \
    _(31, EMC, DLI_TRIM_TXDQS2, EMC2PMACRO_CFG_TXDQS2_DLI, EmcDliTrimTxDqs2) \
    _(31, EMC, DLI_TRIM_TXDQS3, EMC2PMACRO_CFG_TXDQS3_DLI, EmcDliTrimTxDqs3) \
    _(31, EMC, DLI_TRIM_TXDQS4, EMC2PMACRO_CFG_TXDQS4_DLI, EmcDliTrimTxDqs4) \
    _(31, EMC, DLI_TRIM_TXDQS5, EMC2PMACRO_CFG_TXDQS5_DLI, EmcDliTrimTxDqs5) \
    _(31, EMC, REXT, REXT, EmcRext) \
    _(32, EMC, DLI_TRIM_TXDQS6, EMC2PMACRO_CFG_TXDQS6_DLI, EmcDliTrimTxDqs6) \
    _(32, EMC, DLI_TRIM_TXDQS7, EMC2PMACRO_CFG_TXDQS7_DLI, EmcDliTrimTxDqs7) \
    _(32, EMC, RP, RP, EmcRp) \
    _(32, EMC, W2P, W2P, EmcW2p) \
    _(32, EMC, RD_RCD, RD_RCD, EmcRdRcd) \
    _(33, EMC, WR_RCD, WR_RCD, EmcWrRcd) \
    _(33, EMC, TFAW, TFAW, EmcTfaw) \
    _(33, EMC, TRPAB, TRPAB, EmcTrpab) \
    _(33, EMC, ODT_WRITE, ODT_WR_DELAY, EmcOdtWrite) \
    _(33, EMC, ODT_WRITE, DRIVE_BOTH_ODT, EmcOdtWrite) \
    _(33, EMC, ODT_WRITE, ODT_B4_WRITE, EmcOdtWrite) \
    _(33, EMC, ODT_WRITE, ENABLE_ODT_DURING_WRITE, EmcOdtWrite) \
    _(33, EMC, XM2DQSPADCTRL3, EMC2PMACRO_CFG_XM2DQS_E_STRPULL_DQS, EmcXm2DqsPadCtrl3) \
    _(33, EMC, XM2DQSPADCTRL3, EMC2PMACRO_CFG_XM2DQS_E_VREF_DQS, EmcXm2DqsPadCtrl3) \
    _(33, EMC, XM2DQSPADCTRL3, EMC2PMACRO_CFG_XM2DQS_VREF_DQS, EmcXm2DqsPadCtrl3) \
    _(33, EMC, FBIO_CFG5, DIFFERENTIAL_DQS, EmcFbioCfg5) \
    _(40, EMC, W2R, W2R, EmcW2r) \
    _(40, EMC, R2P, R2P, EmcR2p) \
    _(40, EMC, QUSE, QUSE, EmcQUse) \
    _(40, EMC, QRST, QRST, EmcQRst) \
    _(40, EMC, RDV, RDV, EmcRdv) \
    _(40, EMC, CTT, CTT, EmcCtt) \
    _(40, EMC, FBIO_CFG5, CTT_TERMINATION, EmcFbioCfg5) \
    _(40, EMC, FBIO_CFG5, DQS_PULLD, EmcFbioCfg5) \
    _(42, EMC, WDV, WDV, EmcWdv) \
    _(42, EMC, QSAFE, QSAFE, EmcQSafe) \
    _(42, EMC, WEXT, WEXT, EmcWext) \
    _(42, EMC, FBIO_CFG5, EMC2PMACRO_CFG_QUSE_MODE, EmcFbioCfg5) \
    _(42, EMC, FBIO_CFG5, CMD_2T_TIMING, EmcFbioCfg5) \
    _(42, EMC, QUSE_EXTRA, QUSE_EXTRA, EmcQUseExtra) \
    _(44, EMC, XM2CMDPADCTRL, EMC2TMC_CFG_XM2CMD_CLK_SEL, EmcXm2CmdPadCtrl) \
    _(44, EMC, XM2CMDPADCTRL, EMC2PMACRO_CFG_XM2CMD_PHASESHIFT, EmcXm2CmdPadCtrl) \
    _(44, EMC, AR2PDEN, AR2PDEN, EmcAr2Pden) \
    _(44, EMC, FBIO_SPARE, CFG_FBIO_SPARE_2, EmcFbioSpare) \
    _(44, EMC, CFG_RSV, CFG_RESERVED_BYTE1, EmcCfgRsv) \
    _(44, EMC, CTT_TERM_CTRL, TERM_OFFSET, EmcCttTermCtrl) \
    _(45, EMC, PCHG2PDEN, PCHG2PDEN, EmcPChg2Pden) \
    _(45, EMC, ACT2PDEN, ACT2PDEN, EmcAct2Pden) \
    _(45, EMC, RW2PDEN, RW2PDEN, EmcRw2Pden) \
    _(45, EMC, XM2CMDPADCTRL2, EMC2PMACRO_CFG_XM2CMD_DRVDN, EmcXm2CmdPadCtrl2) \
    _(45, EMC, XM2CMDPADCTRL2, EMC2PMACRO_CFG_XM2CMD_DRVUP, EmcXm2CmdPadCtrl2) \
    _(45, EMC, XM2CMDPADCTRL2, EMC2PMACRO_CFG_XM2CMD_DRVDN_SLWR, EmcXm2CmdPadCtrl2) \
    _(46, EMC, XM2DQSPADCTRL, EMC2PMACRO_CFG_XM2DQS_DRVDN_TERM, EmcXm2DqsPadCtrl) \
    _(46, EMC, XM2DQSPADCTRL, EMC2PMACRO_CFG_XM2DQS_DRVUP_TERM, EmcXm2DqsPadCtrl) \
    _(46, EMC, XM2DQSPADCTRL, EMC2PMACRO_CFG_XM2DQS_DRVDN, EmcXm2DqsPadCtrl) \
    _(46, EMC, XM2DQSPADCTRL, EMC2PMACRO_CFG_XM2DQS_DRVUP, EmcXm2DqsPadCtrl) \
    _(46, EMC, XM2DQPADCTRL, EMC2PMACRO_CFG_XM2DQ_DRVDN, EmcXm2DqPadCtrl) \
    _(46, EMC, XM2DQPADCTRL, EMC2PMACRO_CFG_XM2DQ_DRVUP, EmcXm2DqPadCtrl) \
    _(46, EMC, CFG_2, MRR_BYTESEL, EmcCfg2) \
    _(47, EMC, XM2CMDPADCTRL2, EMC2PMACRO_CFG_XM2CMD_DRVUP_SLWF, EmcXm2CmdPadCtrl2) \
    _(47, EMC, XM2DQSPADCTRL, EMC2PMACRO_CFG_XM2DQS_DRVDN_SLWR, EmcXm2DqsPadCtrl) \
    _(47, EMC, XM2DQSPADCTRL, EMC2PMACRO_CFG_XM2DQS_DRVUP_SLWF, EmcXm2DqsPadCtrl) \
    _(47, EMC, XM2DQPADCTRL, EMC2PMACRO_CFG_XM2DQ_DRVDN_SLWR, EmcXm2DqPadCtrl) \
    _(47, EMC, XM2DQPADCTRL, EMC2PMACRO_CFG_XM2DQ_DRVUP_SLWF, EmcXm2DqPadCtrl) \
    _(47, EMC, XM2CLKPADCTRL, EMC2PMACRO_CFG_XM2CLK_DRVDN_SLWR, EmcXm2ClkPadCtrl) \
    _(47, EMC, XM2CLKPADCTRL, EMC2PMACRO_CFG_XM2CLK_DRVUP_SLWF, EmcXm2ClkPadCtrl) \
    _(47, EMC, CTT_TERM_CTRL, TERM_SLOPE, EmcCttTermCtrl) \
    _(47, EMC, CFG, MAN_PRE_RD, EmcCfg) \
    _(48, EMC, XM2DQPADCTRL2, EMC2TMC_CFG_XM2DQ0_DLYIN_TRM, EmcXm2DqPadCtrl2) \
    _(48, EMC, XM2DQPADCTRL2, EMC2TMC_CFG_XM2DQ1_DLYIN_TRM, EmcXm2DqPadCtrl2) \
    _(48, EMC, XM2DQPADCTRL2, EMC2TMC_CFG_XM2DQ2_DLYIN_TRM, EmcXm2DqPadCtrl2) \
    _(48, EMC, XM2DQPADCTRL2, EMC2TMC_CFG_XM2DQ3_DLYIN_TRM, EmcXm2DqPadCtrl2) \
    _(48, EMC, XM2CLKPADCTRL, EMC2TMC_CFG_XM2CLK_DLY_TRM_P, EmcXm2ClkPadCtrl) \
    _(48, EMC, CFG_2, MRR_BYTESEL_X16, EmcCfg2) \
    _(48, EMC, CFG, MAN_PRE_WR, EmcCfg) \

// LPDDR2 only register field packing list
#define LPDDR2_PMC_FIELDS(_) \
    _( 5, EMC, MRW_LPDDR2_ZCAL_WARM_BOOT, MRW_MA, EmcMrwLpddr2ZcalWarmBoot) \
    _( 5, EMC, MRW_LPDDR2_ZCAL_WARM_BOOT, MRW_OP, EmcMrwLpddr2ZcalWarmBoot) \
    _( 5, EMC, WARM_BOOT_MRW1, MRW_MA, EmcWarmBootMrw1) \
    _( 5, EMC, WARM_BOOT_MRW1, MRW_OP, EmcWarmBootMrw1) \
    _( 6, EMC, WARM_BOOT_MRW3, MRW_MA, EmcWarmBootMrw3) \
    _( 6, EMC, WARM_BOOT_MRW3, MRW_OP, EmcWarmBootMrw3) \
    _( 6, EMC, WARM_BOOT_MRW2, MRW_MA, EmcWarmBootMrw2) \
    _( 6, EMC, WARM_BOOT_MRW2, MRW_OP, EmcWarmBootMrw2) \
    _( 7, EMC, WARM_BOOT_MRW_EXTRA, MRW_MA, EmcWarmBootMrwExtra) \
    _( 7, EMC, WARM_BOOT_MRW_EXTRA, MRW_OP, EmcWarmBootMrwExtra) \

// SDRAM value packing list generated by tool warmboot_code_gen
#define SDRAM_PMC_VALUES(_) \
    _(14, NvU32, EMC_DEV_SELN, EmcDevSelect) \
    _(15, NvU32, EMC_DIG_DLL_PERIOD_WARM_BOOT, EmcCfgDigDllPeriodWarmBoot) \
    _(16, NvU32, EMC_EXTRA_MODE_REG_WRITE_ENABLE, EmcWarmBootExtraModeRegWriteEnable) \
    _(17, NvU32, MC_CLK_EN_OVERRIDE_ALL_WARM_BOOT, McClkenOverrideAllWarmBoot) \
    _(17, NvU32, EMC_CLK_EN_OVERRIDE_ALL_WARM_BOOT, EmcClkenOverrideAllWarmBoot) \
    _(18, NvU32, EMC_MRS_WARM_BOOT_ENABLE, EmcMrsWarmBootEnable) \
    _(18, NvU32, EMC_ZCAL_WARM_BOOT_ENABLE, EmcZcalWarmBootEnable) \
    _(23, NvU32, CLK_RST_CONTROLLER_CLK_SOURCE_EMC_0_EMC_2X_CLK_SRC, EmcClockSource) \
    _(29, NvU32, EMC_TIMING_CONTROL_WAIT, EmcTimingControlWait) \
    _(29, NvU32, EMC_ZCAL_WARM_BOOT_WAIT, EmcZcalWarmBootWait) \
    _(29, NvU32, EMC_AUTO_CAL_TIME, EmcAutoCalWait) \
    _(29, NvU32, WARM_BOOT_WAIT, WarmBootWait) \
    _(30, NvU32, EMC_PIN_PROGRAM_WAIT, EmcPinProgramWait) \
    _(30, NvU32, EMC_EXTRA_REFRES_NUM, EmcExtraRefreshNum) \
    _(33, NvU32, AHB_ARBITRATION_XBAR_CTRL_0_MEM_INIT_DONE, AhbArbitrationXbarCtrlMemInitDone) \
    _(42, NvBootMemoryType, MEMORY_TYPE, MemoryType) \
    _(42, NvU32, CLK_RST_CONTROLLER_CLK_SOURCE_EMC_0_EMC_2X_CLK_DIVISOR, EmcClockDivider) \
    _(42, NvU32, CLK_RST_CONTROLLER_CLK_SOURCE_EMC_0_USE_PLLM_UD, EmcClockUsePllMUD) \

// End of generated code by warmboot_code_gen


#if defined(__cplusplus)
}
#endif

#endif // INCLUDED_NVBOOT_WB0_SDRAM_SCRATCH_LIST_H
