#include "dsid_direct_lib.h"
int main(){
register_cp_mmio();
dsid_direct_cache_show(1);
unregister_cp_mmio();
return 0;
}
