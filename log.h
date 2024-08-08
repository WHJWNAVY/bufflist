#ifndef __LOG_H__
#define __LOG_H__

#include <ctype.h>
#include <inttypes.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFLIST_DEBUG 1
#define LOGL_DEBUG "DEBUG"
#define LOGL_ERROR "ERROR"

#define LOGP(LEVEL, FMT, ...)                                                  \
  do {                                                                         \
    fprintf(stderr, ">>>>>> (%s:%d) [%s] " FMT "\n", __func__, __LINE__,       \
            LEVEL, ##__VA_ARGS__);                                             \
  } while (0)

#ifdef BUFFLIST_DEBUG
#define LOG_DEBUG(FMT, ...) LOGP(LOGL_DEBUG, FMT, ##__VA_ARGS__)
#else
#define LOG_DEBUG(FMT, ...)
#endif

#define LOG_ERROR(FMT, ...) LOGP(LOGL_ERROR, FMT, ##__VA_ARGS__)

char *printf_hex(const uint8_t *buf, uint32_t size);
char *dump_hex(uint8_t *bytes, size_t len);
uint8_t *scanf_hex(char *str, size_t *len);
#endif