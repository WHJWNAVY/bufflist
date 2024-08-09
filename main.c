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