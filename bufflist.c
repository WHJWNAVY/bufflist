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
                                             uint64_t boff) {
  bufflist_t *node = NULL;
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
  node->bsze = 0;

  LOG_DEBUG("Add buffer [%lu][%lu] entry success!", node->boff, node->blen);

  return node;
}

bufflist_t *bufflist_new(bufflist_t *head, uint64_t blen, uint64_t boff) {
  bufflist_t *node = NULL;

  // node = bufflist_find(head, boff);
  // if (node != NULL)
  // {
  //     LOG_ERROR("Buffer [%lu][%lu] already exists!", node->boff, node->blen);
  //     return NULL;
  // }

  node = bufflist_new_entry(head, blen, boff);
  if (node == NULL) {
    return NULL;
  }
  list_add_tail(&(node->list), &(head->list));

  head->blen += blen;
  head->bsze += blen;

  LOG_DEBUG("Add buffer [%lu][%lu] success! total buffer size [%lu]",
            node->boff, node->blen, head->blen);

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
      LOG_DEBUG("Found buffer [%lu][%lu] by offset [%lu]", node->boff,
                node->blen, boff);
      return node;
    }
  }

  LOG_DEBUG("Can't find buffer by offset [%lu]", boff);
  return NULL;
}

static inline bool bufflist_del_entry(bufflist_t *head, bufflist_t *node) {
  if ((head == NULL) || (node == NULL)) {
    return false;
  }

  // if (list_empty(&(head->list)))
  // {
  //     LOG_ERROR("Buffer list is empty!");
  //     return false;
  // }

  LOG_DEBUG("Del buffer [%lu][%lu] entry!", node->boff, node->blen);

  list_del(&(node->list));

  if (head->blen >= node->blen) {
    head->blen -= node->blen;
    head->bsze -= node->blen;
  }

  if (node->buff != NULL) {
    free(node->buff);
  }

  free(node);

  return true;
}

bool bufflist_del(bufflist_t *head, uint64_t boff) {
  if (!bufflist_del_entry(head, bufflist_find(head, boff))) {
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

  if (list_empty(&(head->list))) {
    LOG_ERROR("Buffer list is empty!");
    return NULL;
  }

  list_for_each_entry_safe(node, temp, &(head->list), list) {
    bufflist_del_entry(head, node);
  }

  LOG_ERROR("Buffer destroy success!");

  return true;
}