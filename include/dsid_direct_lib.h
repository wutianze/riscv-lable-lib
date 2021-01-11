#ifndef DSID_DIRECT_LIB_H
#define DSID_DIRECT_LIB_H
//#include <linux/slab.h>
//#include <linux/kernel.h>
//#include <linux/smp.h>
//#include <linux/io.h>
#include <stdio.h>

static volatile uint32_t *cpbase;
uint32_t cp_reg_r(uint32_t dm_reg);
void cp_reg_w(uint32_t dm_reg, uint32_t val);
void register_cp_mmio(void);
void unregister_cp_mmio(void);

enum {
	/* Access current dsid */
	CP_HART_DSID            = 0x41,

	/* Access dsid selector */
	CP_HART_SEL             = 0x42,

	/* Read total dsid count */
	CP_DSID_COUNT           = 0x43,

	/* Access mem base with current dsid */
	CP_MEM_BASE_LO          = 0x44,

	CP_MEM_BASE_HI          = 0x45,

	/* Access mem mask with current dsid */
	CP_MEM_MASK_LO          = 0x46,

	CP_MEM_MASK_HI          = 0x47,

	CP_BUCKET_FREQ          = 0x48,

	CP_BUCKET_SIZE          = 0x49,

	CP_BUCKET_INC           = 0x4a,

	CP_TRAFFIC              = 0x4b,

	CP_WAYMASK              = 0x4c,

	CP_L2_CAPACITY          = 0x4d,

	CP_DSID_SEL             = 0x4e,

	CP_LIMIT_INDEX          = 0x4f,

	CP_LIMIT                = 0x50,

	CP_LOW_THRESHOLD        = 0x51,

	CP_HIGH_THRESHOLD       = 0x52,

	CP_MAX_QUOTA            = 0x53,

	CP_MIN_QUOTA            = 0x54,

	CP_QUOTA_STEP           = 0x55,

	CP_TIMER_LO             = 0x56,

	CP_TIMER_HI             = 0x57,

	CP_AUTOCAT_EN           = 0x58,

	CP_AUTOCAT_BIN_POWER    = 0x59,

	CP_AUTOCAT_WAYMASK      = 0x5a,

	CP_AUTOCAT_WATCH_DSID   = 0x5b,

	CP_AUTOCAT_SET          = 0x5c,

	CP_AUTOCAT_GAP          = 0x5d,

	CORE_PC_HI              = 0x70,

	CORE_PC_LO              = 0x71,

	CORE_PC_SNAP            = 0x72,

	CORE_PC_READ_DONE       = 0x73,

	CORE_PC_READ            = 0x74,

	CORE_INT_DEBUG          = 0x75,

	CORE_N_INT_DEBUG        = 0x76,

	CORE_N_INT_DEBUG_LOCAL  = 0x77,

	CORE_CSR_INT_VALID      = 0x78,

	CORE_CSR_PENDING_INT_LO = 0x79,

	CORE_CSR_PENDING_INT_HI = 0x7a,

	CP_HART_ID              = 0x7b,

	CP_L2_REQ_EN            = 0x7f,

	CP_L2_REQ_MISS          = 0x7c,

	CP_L2_REQ_TOTAL         = 0x7d,

	CP_L2_STAT_RESET        = 0x7e,
};

const char *cp_reg_name[] = {
	/* Access current dsid */
	[CP_HART_DSID            - CP_HART_DSID] = "hart_dsid",

	/* Access dsid selector */
	[CP_HART_SEL             - CP_HART_DSID] = "hart_sel",

	/* Read total dsid count */
	[CP_DSID_COUNT           - CP_HART_DSID] = "dsid_count",

	/* Access mem base with current dsid */
	[CP_MEM_BASE_LO          - CP_HART_DSID] = "mem_base",

	[CP_MEM_BASE_HI          - CP_HART_DSID] = "mem_base",

	/* Access mem mask with current dsid */
	[CP_MEM_MASK_LO          - CP_HART_DSID] = "mem_mask",

	[CP_MEM_MASK_HI          - CP_HART_DSID] = "mem_mask",

	[CP_BUCKET_FREQ          - CP_HART_DSID] = "bucket_freq",

	[CP_BUCKET_SIZE          - CP_HART_DSID] = "bucket_size",

	[CP_BUCKET_INC           - CP_HART_DSID] = "bucket_inc",

	[CP_TRAFFIC              - CP_HART_DSID] = "l1_traffic",

	[CP_WAYMASK              - CP_HART_DSID] = "l2_waymask",

	[CP_L2_CAPACITY          - CP_HART_DSID] = "l2_capacity",

	[CP_DSID_SEL             - CP_HART_DSID] = "dsid_sel",

	[CP_LIMIT_INDEX          - CP_HART_DSID] = "N/A",

	[CP_LIMIT                - CP_HART_DSID] = "N/A",

	[CP_LOW_THRESHOLD        - CP_HART_DSID] = "N/A",

	[CP_HIGH_THRESHOLD       - CP_HART_DSID] = "N/A",

	[CP_MAX_QUOTA            - CP_HART_DSID] = "N/A",

	[CP_MIN_QUOTA            - CP_HART_DSID] = "N/A",

	[CP_QUOTA_STEP           - CP_HART_DSID] = "N/A",

	[CP_TIMER_LO             - CP_HART_DSID] = "timestamp",

	[CP_TIMER_HI             - CP_HART_DSID] = "timestamp",

	[CP_AUTOCAT_EN           - CP_HART_DSID] = "autocat_en",

	[CP_AUTOCAT_BIN_POWER    - CP_HART_DSID] = "autocat_cycle_log2",

	[CP_AUTOCAT_WAYMASK      - CP_HART_DSID] = "autocat_waymask",

	[CP_AUTOCAT_WATCH_DSID   - CP_HART_DSID] = "autocat_watch",

	[CP_AUTOCAT_SET          - CP_HART_DSID] = "autocat_set",

	[CP_AUTOCAT_GAP          - CP_HART_DSID] = "autocat_gap",

	[CORE_PC_HI              - CP_HART_DSID] = "N/A",

	[CORE_PC_LO              - CP_HART_DSID] = "N/A",

	[CORE_PC_SNAP            - CP_HART_DSID] = "N/A",

	[CORE_PC_READ_DONE       - CP_HART_DSID] = "N/A",

	[CORE_PC_READ            - CP_HART_DSID] = "N/A",

	[CORE_INT_DEBUG          - CP_HART_DSID] = "N/A",

	[CORE_N_INT_DEBUG        - CP_HART_DSID] = "N/A",

	[CORE_N_INT_DEBUG_LOCAL  - CP_HART_DSID] = "N/A",

	[CORE_CSR_INT_VALID      - CP_HART_DSID] = "N/A",

	[CORE_CSR_PENDING_INT_LO - CP_HART_DSID] = "N/A",

	[CORE_CSR_PENDING_INT_HI - CP_HART_DSID] = "N/A",

	[CP_HART_ID              - CP_HART_DSID] = "vhartid",

	[CP_L2_REQ_EN            - CP_HART_DSID] = "l2_query_miss",

	[CP_L2_REQ_MISS          - CP_HART_DSID] = "l2_miss",

	[CP_L2_REQ_TOTAL         - CP_HART_DSID] = "l2_total",

	[CP_L2_STAT_RESET        - CP_HART_DSID] = "l2_stat_reset",
};

#define NR(arr) (sizeof(arr) / sizeof(arr[0]))

// waymask,access,miss,usage,sizes,freq,incs,read,write
// cpbase[idx * (1 << proc_dsid_width) + proc_dsid]

void dsid_direct_write(unsigned int dsid, int i, uint32_t num);
void dsid_direct_cache_show(unsigned int dsid);
#endif
