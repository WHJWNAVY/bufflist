#include "bufflist.h"
#include "log.h"

bufflist_t *bufflist_init(void) {
  bufflist_t *head = malloc(sizeof(bufflist_t));
  if (head == NULL) {
    return NULL;
  }
  memset(head, 0, sizeof(bufflist_t));
  INIT_LIST_HEAD(&(head->list));

  return head;
}

static inline bufflist_t *bufflist_new_entry(bufflist_t *head, uint64_t blen,
                                             uint64_t boff, uint64_t blksz) {
  bufflist_t *node = NULL;
  uint64_t blkn = 0;
  if ((head == NULL) || (blen == 0)) {
    return NULL;
  }

  node = malloc(sizeof(bufflist_t));
  if (node == NULL) {
    return NULL;
  }
  memset(node, 0, sizeof(bufflist_t));

  node->buff = malloc(blen);
  if (node->buff == NULL) {
    free(node);
    return NULL;
  }
  node->blen = blen;
  node->boff = boff;
  node->blksz = blksz;
  node->bsze = 0;

  blkn = BLOCK_CNT(blen, blksz);
  node->bbuf = malloc(sizeof(bool) * blkn);
  if (node->bbuf == NULL) {
    free(node->buff);
    free(node);
    return NULL;
  }
  memset(node->bbuf, 0, (sizeof(bool) * blkn));

  LOG_DEBUG("Add buffer [%lu][%lu][%lu] entry success!", node->boff, node->blen,
            node->blksz);

  return node;
}

bufflist_t *bufflist_new(bufflist_t *head, uint64_t blen, uint64_t boff,
                         uint64_t blksz) {
  bufflist_t *node = NULL;

  // node = bufflist_find(head, boff);
  // if (node != NULL)
  // {
  //     LOG_ERROR("Buffer [%lu][%lu] already exists!", node->boff, node->blen);
  //     return NULL;
  // }

  node = bufflist_new_entry(head, blen, boff, blksz);
  if (node == NULL) {
    return NULL;
  }
  list_add_tail(&(node->list), &(head->list));

  head->blen += blen;

  LOG_DEBUG("Add buffer [%lu][%lu][%lu] success! total buffer size [%lu]",
            node->boff, node->blen, node->blksz, head->blen);

  return node;
}

bufflist_t *bufflist_find(bufflist_t *head, uint64_t boff) {
  bufflist_t *node = NULL;

  if (list_empty(&(head->list))) {
    LOG_ERROR("Buffer list is empty!");
    return NULL;
  }

  list_for_each_entry(node, &(head->list), list) {
    if ((node != NULL) && (boff >= node->boff) &&
        (boff < (node->boff + node->blen))) {
      LOG_DEBUG("Found buffer [%lu][%lu][%lu] by offset [%lu]", node->boff,
                node->blen, node->blksz, boff);
      return node;
    }
  }

  LOG_DEBUG("Can't find buffer by offset [%lu]", boff);
  return NULL;
}

bool bufflist_delentry(bufflist_t *head, bufflist_t *node) {
  if ((head == NULL) || (node == NULL)) {
    return false;
  }

  LOG_DEBUG("Del buffer [%lu][%lu][%lu] entry!", node->boff, node->blen,
            node->blksz);

  list_del(&(node->list));

  if (head->blen >= node->blen) {
    head->blen -= node->blen;
  }

  if (node->buff != NULL) {
    free(node->buff);
  }

  if (node->bbuf != NULL) {
    free(node->bbuf);
  }

  free(node);

  return true;
}

bool bufflist_delete(bufflist_t *head, uint64_t boff) {
  if (!bufflist_delentry(head, bufflist_find(head, boff))) {
    LOG_ERROR("Failed to delete buffer by offset [%lu]", boff);
    return false;
  }

  LOG_DEBUG("Del buffer by offset [%lu] success! total buffer size [%lu]", boff,
            head->blen);
  return true;
}

bool bufflist_destroy(bufflist_t *head) {
  bufflist_t *node = NULL;
  bufflist_t *temp = NULL;
  if (head == NULL) {
    return false;
  }

  list_for_each_entry_safe(node, temp, &(head->list), list) {
    bufflist_delentry(head, node);
  }

  free(head);

  LOG_DEBUG("Buffer destroy success!");

  return true;
}
#if 0
bool bufflist_foreach(bufflist_t *head, bufflist_foreach_cb callback) {
    bufflist_t *node = NULL;
    bufflist_t *temp = NULL;
    if ((head == NULL) || (callback == NULL)) {
        return false;
    }

    if (list_empty(&(head->list))) {
        LOG_ERROR("Buffer list is empty!");
        return false;
    }

    list_for_each_entry_safe(node, temp, &(head->list), list) {
        if (callback(head, node)) {
            break;
        }
    }

    return true;
}
#endif