# Buffer List

## example
```c
#include "bufflist.h"
#include "log.h"

#ifdef LOG_DEBUG
#undef LOG_DEBUG
#define LOG_DEBUG(FMT, ...)
#endif

#define BUFFER_LEN 100

int main(int argc, char *argv[]) {
  uint64_t idx = 0;
  uint64_t boff = 0;
  uint64_t blen = BUFFER_LEN;
  bufflist_t *nodebuf = NULL;
  bufflist_t *buffer = bufflist_init();

  for (idx = 0; idx < 10; idx++) {
    if ((nodebuf = bufflist_new(buffer, blen, boff)) == NULL) {
      LOG_DEBUG("Failed to add buffer [%lu][%lu]", boff, blen);
      break;
    }
    LOG_DEBUG("Success to add buffer [%lu][%lu]", boff, blen);
    boff += blen;
  }

  boff = blen * 5 + 3;
  if ((nodebuf = bufflist_find(buffer, boff)) != NULL) {
    LOG_DEBUG("Success to find buffer [%lu][%lu] by offset[%lu]", nodebuf->boff,
              nodebuf->blen, boff);

    if (!bufflist_del(buffer, boff)) {
      LOG_ERROR("Failed to delete buffer [%lu][%lu]by offset[%lu]",
                nodebuf->boff, nodebuf->blen, boff);
    } else {
      LOG_DEBUG("Success to delete buffer [%lu][%lu]by offset[%lu]",
                nodebuf->boff, nodebuf->blen, boff);
    }
  } else {
    LOG_ERROR("Failed to find buffer [%lu]", boff);
  }

  if (!bufflist_destroy(buffer)) {
    LOG_ERROR("Failed to destroy buffer");
  } else {
    LOG_ERROR("Success to destroy buffer");
  }
  return 0;
}
```

## output
```
./bufflist
>>>>>> (bufflist_new_entry:37) [DEBUG] Add buffer [0][100] entry success!
>>>>>> (bufflist_new:61) [DEBUG] Add buffer [0][100] success! total buffer size [100]
>>>>>> (bufflist_new_entry:37) [DEBUG] Add buffer [100][100] entry success!
>>>>>> (bufflist_new:61) [DEBUG] Add buffer [100][100] success! total buffer size [200]
>>>>>> (bufflist_new_entry:37) [DEBUG] Add buffer [200][100] entry success!
>>>>>> (bufflist_new:61) [DEBUG] Add buffer [200][100] success! total buffer size [300]
>>>>>> (bufflist_new_entry:37) [DEBUG] Add buffer [300][100] entry success!
>>>>>> (bufflist_new:61) [DEBUG] Add buffer [300][100] success! total buffer size [400]
>>>>>> (bufflist_new_entry:37) [DEBUG] Add buffer [400][100] entry success!
>>>>>> (bufflist_new:61) [DEBUG] Add buffer [400][100] success! total buffer size [500]
>>>>>> (bufflist_new_entry:37) [DEBUG] Add buffer [500][100] entry success!
>>>>>> (bufflist_new:61) [DEBUG] Add buffer [500][100] success! total buffer size [600]
>>>>>> (bufflist_new_entry:37) [DEBUG] Add buffer [600][100] entry success!
>>>>>> (bufflist_new:61) [DEBUG] Add buffer [600][100] success! total buffer size [700]
>>>>>> (bufflist_new_entry:37) [DEBUG] Add buffer [700][100] entry success!
>>>>>> (bufflist_new:61) [DEBUG] Add buffer [700][100] success! total buffer size [800]
>>>>>> (bufflist_new_entry:37) [DEBUG] Add buffer [800][100] entry success!
>>>>>> (bufflist_new:61) [DEBUG] Add buffer [800][100] success! total buffer size [900]
>>>>>> (bufflist_new_entry:37) [DEBUG] Add buffer [900][100] entry success!
>>>>>> (bufflist_new:61) [DEBUG] Add buffer [900][100] success! total buffer size [1000]
>>>>>> (bufflist_find:78) [DEBUG] Found buffer [500][100] by offset [503]
>>>>>> (bufflist_find:78) [DEBUG] Found buffer [500][100] by offset [503]
>>>>>> (bufflist_del_entry:99) [DEBUG] Del buffer [500][100] entry!
>>>>>> (bufflist_del:123) [DEBUG] Del buffer by offset [503] success! total buffer size [900]
>>>>>> (bufflist_del_entry:99) [DEBUG] Del buffer [0][100] entry!
>>>>>> (bufflist_del_entry:99) [DEBUG] Del buffer [100][100] entry!
>>>>>> (bufflist_del_entry:99) [DEBUG] Del buffer [200][100] entry!
>>>>>> (bufflist_del_entry:99) [DEBUG] Del buffer [300][100] entry!
>>>>>> (bufflist_del_entry:99) [DEBUG] Del buffer [400][100] entry!
>>>>>> (bufflist_del_entry:99) [DEBUG] Del buffer [600][100] entry!
>>>>>> (bufflist_del_entry:99) [DEBUG] Del buffer [700][100] entry!
>>>>>> (bufflist_del_entry:99) [DEBUG] Del buffer [800][100] entry!
>>>>>> (bufflist_del_entry:99) [DEBUG] Del buffer [900][100] entry!
>>>>>> (bufflist_destroy:144) [ERROR] Buffer destroy success!
>>>>>> (main:46) [ERROR] Success to destroy buffer
```