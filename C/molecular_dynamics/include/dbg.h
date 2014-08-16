#ifndef __dbg_h__
#define __dbg_h__

#include <stdio.h>
#include <errno.h>
#include <string.h>

#define DEBUG

#ifdef DEBUG
#define DEBUG_PRINT(M, ...) fprintf(stderr, "DEBUG %s:%d: " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#else
#define DEBUG_PRINT(M, ...) do {} while(0)
#endif

#define CLEAN_ERRNO() (errno == 0 ? "None" : strerror(errno))

#define LOG_ERROR(M, ...) fprintf(stderr, "[ERROR] (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__, CLEAN_ERRNO(), ##__VA_ARGS__)

#define LOG_WARN(M, ...) fprintf(stderr, "[WARN] (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__, CLEAN_ERRNO(), ##__VA_ARGS__)

#define LOG_INFO(M, ...) fprintf(stderr, "[INFO] (%s:%d) " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)

#define CHECK(A, M, ...) if(!(A)) { LOG_ERR(M, ##__VA_ARGS__); errno=0; goto error; }

#define SENTINEL(M, ...)  { LOG_ERR(M, ##__VA_ARGS__); errno=0; goto error; }

#define CHECK_MEM(A) check((A), "Out of memory.")

#define CHECK_DEBUG(A, M, ...) if(!(A)) { DEBUG_PRINT(M, ##__VA_ARGS__); errno=0; goto error; }

#endif
