#include "dsid_direct_lib.h"
uint32_t cp_reg_r(uint32_t dm_reg)
{
    return (uint32_t)*(cpbase + dm_reg);
}

void cp_reg_w(uint32_t dm_reg, uint32_t val)
{
    if (cpbase == NULL) {
        printf("cpbase is NULL\n");
    }
    else {
        *(cpbase + dm_reg) = val;
        //writeq(val, cpbase + dm_reg);
    }
}
void register_cp_mmio(void)
{
	cpbase = ioremap_nocache(0x20000, 0x10000);
}

void unregister_cp_mmio(void)
{
	iounmap(cpbase);
}

void dsid_direct_write(unsigned int dsid, int i, uint32_t num)
{
            cp_reg_w(CP_DSID_SEL - CP_HART_DSID, dsid << 2);
            cp_reg_w(i, num);
}

void dsid_direct_cache_show(unsigned int dsid)
{
    const int NR_WAYS = 16;
    const int CACHE_LABEL_INDEX = 0x59;
    const int CACHE_LABEL_DATA = 0x5a;
    const int DSID_WIDTH = 5;  // log2(4 cores) + 3 proc_bits

    uint32_t label = dsid << 2;
	printf("physical label: %d\n", label);

    int cnt[NR_WAYS];
    int i;
    for (i = 0; i < NR_WAYS; i++) {
        int index = (i << DSID_WIDTH) | label;
        cp_reg_w(CACHE_LABEL_INDEX - CP_HART_DSID, index);
        cnt[i] = cp_reg_r(CACHE_LABEL_DATA - CP_HART_DSID);
    }

    printf("way,set_cnt\n");
    for (i = 0; i < NR_WAYS; i++) {
        printf("%d,%d\n", i, cnt[i]);
    }

    return 0;
}
