#ifndef __BUFFER_LIST_H__
#define __BUFFER_LIST_H__

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "list.h"

#define BLOCK_CNT(_blen, _blksz)                                               \
  ((_blen) / (_blksz)) + (((_blen) % (_blksz)) ? 1 : 0)

typedef struct {
  struct list_head list;
  uint8_t *buff;  // buffer data
  uint64_t blen;  // buffer len (total)
  uint64_t boff;  // buffer offset
  uint64_t bsze;  // write size (real)
  uint64_t blksz; // block size
  bool *bbuf;     // block write flag
} bufflist_t;

bufflist_t *bufflist_init(void);
bufflist_t *bufflist_new(bufflist_t *head, uint64_t blen, uint64_t boff,
                         uint64_t blksz);
bufflist_t *bufflist_find(bufflist_t *head, uint64_t boff);
bool bufflist_delentry(bufflist_t *head, bufflist_t *node);
bool bufflist_delete(bufflist_t *head, uint64_t boff);
bool bufflist_destroy(bufflist_t *head);
#if 0
typedef bool (*bufflist_foreach_cb)(bufflist_t *head, bufflist_t *node);
bool bufflist_foreach(bufflist_t *head, bufflist_foreach_cb callback);
#else
#define bufflist_foreach(_head, _node, _temp)                                  \
  list_for_each_entry_safe(_node, _temp, &((_head)->list), list)
#endif
#define bufflist_isempty(_head) (list_empty(&((_head)->list)))

#endif