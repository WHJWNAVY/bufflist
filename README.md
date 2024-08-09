# Buffer List

## example
```c
#include "bufflist.h"
#include "log.h"

#ifdef LOG_DEBUG
#undef LOG_DEBUG
#define LOG_DEBUG(FMT, ...)
#endif

#define BUFFER_LEN 1024
#define BLOCKS_LEN 512

int main(int argc, char *argv[]) {
  uint64_t idx = 0;
  uint64_t boff = 0;
  uint64_t blen = BUFFER_LEN;
  uint64_t blks = BLOCKS_LEN;
  bufflist_t *nodebuf = NULL;
  bufflist_t *buffer = bufflist_init();

  for (idx = 0; idx < 10; idx++) {
    if ((nodebuf = bufflist_new(buffer, blen, boff, blks)) == NULL) {
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

    if (!bufflist_delete(buffer, boff)) {
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
>>>>>> (bufflist_new_entry:47) [DEBUG] Add buffer [0][1024][512] entry success!
>>>>>> (bufflist_new:70) [DEBUG] Add buffer [0][1024][512] success! total buffer size [1024]
>>>>>> (bufflist_new_entry:47) [DEBUG] Add buffer [1024][1024][512] entry success!
>>>>>> (bufflist_new:70) [DEBUG] Add buffer [1024][1024][512] success! total buffer size [2048]
>>>>>> (bufflist_new_entry:47) [DEBUG] Add buffer [2048][1024][512] entry success!
>>>>>> (bufflist_new:70) [DEBUG] Add buffer [2048][1024][512] success! total buffer size [3072]
>>>>>> (bufflist_new_entry:47) [DEBUG] Add buffer [3072][1024][512] entry success!
>>>>>> (bufflist_new:70) [DEBUG] Add buffer [3072][1024][512] success! total buffer size [4096]
>>>>>> (bufflist_new_entry:47) [DEBUG] Add buffer [4096][1024][512] entry success!
>>>>>> (bufflist_new:70) [DEBUG] Add buffer [4096][1024][512] success! total buffer size [5120]
>>>>>> (bufflist_new_entry:47) [DEBUG] Add buffer [5120][1024][512] entry success!
>>>>>> (bufflist_new:70) [DEBUG] Add buffer [5120][1024][512] success! total buffer size [6144]
>>>>>> (bufflist_new_entry:47) [DEBUG] Add buffer [6144][1024][512] entry success!
>>>>>> (bufflist_new:70) [DEBUG] Add buffer [6144][1024][512] success! total buffer size [7168]
>>>>>> (bufflist_new_entry:47) [DEBUG] Add buffer [7168][1024][512] entry success!
>>>>>> (bufflist_new:70) [DEBUG] Add buffer [7168][1024][512] success! total buffer size [8192]
>>>>>> (bufflist_new_entry:47) [DEBUG] Add buffer [8192][1024][512] entry success!
>>>>>> (bufflist_new:70) [DEBUG] Add buffer [8192][1024][512] success! total buffer size [9216]
>>>>>> (bufflist_new_entry:47) [DEBUG] Add buffer [9216][1024][512] entry success!
>>>>>> (bufflist_new:70) [DEBUG] Add buffer [9216][1024][512] success! total buffer size [10240]
>>>>>> (bufflist_find:86) [DEBUG] Found buffer [5120][1024][512] by offset [5123]
>>>>>> (bufflist_find:86) [DEBUG] Found buffer [5120][1024][512] by offset [5123]
>>>>>> (bufflist_delentry:100) [DEBUG] Del buffer [5120][1024][512] entry!
>>>>>> (bufflist_delete:127) [DEBUG] Del buffer by offset [5123] success! total buffer size [9216]
>>>>>> (bufflist_delentry:100) [DEBUG] Del buffer [0][1024][512] entry!
>>>>>> (bufflist_delentry:100) [DEBUG] Del buffer [1024][1024][512] entry!
>>>>>> (bufflist_delentry:100) [DEBUG] Del buffer [2048][1024][512] entry!
>>>>>> (bufflist_delentry:100) [DEBUG] Del buffer [3072][1024][512] entry!
>>>>>> (bufflist_delentry:100) [DEBUG] Del buffer [4096][1024][512] entry!
>>>>>> (bufflist_delentry:100) [DEBUG] Del buffer [6144][1024][512] entry!
>>>>>> (bufflist_delentry:100) [DEBUG] Del buffer [7168][1024][512] entry!
>>>>>> (bufflist_delentry:100) [DEBUG] Del buffer [8192][1024][512] entry!
>>>>>> (bufflist_delentry:100) [DEBUG] Del buffer [9216][1024][512] entry!
>>>>>> (bufflist_destroy:144) [DEBUG] Buffer destroy success!
>>>>>> (main:48) [ERROR] Success to destroy buffer
```