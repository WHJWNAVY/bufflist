#ifndef __BUFFER_LIST_H__
#define __BUFFER_LIST_H__

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "list.h"

typedef struct {
  struct list_head list;
  uint8_t *buff; // buffer data
  uint64_t blen; // buffer len (total)
  uint64_t boff; // buffer offset
  uint64_t bsze; // write size (real)
} bufflist_t;

bufflist_t *bufflist_init(void);
bufflist_t *bufflist_new(bufflist_t *head, uint64_t blen, uint64_t boff);
bufflist_t *bufflist_find(bufflist_t *head, uint64_t boff);
bool bufflist_del(bufflist_t *head, uint64_t boff);
bool bufflist_destroy(bufflist_t *head);

#endif