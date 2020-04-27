#ifndef MSG_DBG
#define MSG_DBG

#include<stdio.h>

//调试信息打印等级
#define ENABLE_DBG_INFO_ERROR       1
#define ENABLE_DBG_INFO_WARNING     1
#define ENABLE_DBG_INFO_NORMAL      0


#if ENABLE_DBG_INFO_ERROR
#define DEBUGE(fmt, ...) \
//    do {                    \
//        NSLog("-->%s : %s() L%d: ","error", __FUNCTION__, __LINE__);  \
        NSLog(fmt, __VA_ARGS__);	\
//    } while (0)
#else
#define DEBUGE(fmt, ...)
#endif

#if ENABLE_DBG_INFO_WARNING
#define DEBUGW(fmt, ...)  \
//    do {                    \
//        NSLog("-->%s : %s() L%d: ","warning", __FUNCTION__, __LINE__);  \
        NSLog(fmt, __VA_ARGS__);	\
//    } while (0)
#else
#define DEBUGW(fmt, ...)
#endif

#if ENABLE_DBG_INFO_NORMAL
#define DEBUGN(fmt, ...) \
//    do {                    \
//        NSLog("-->%s : func %s() L%d: ","normal", __FUNCTION__, __LINE__);  \
        NSLog(fmt, __VA_ARGS__);	\
//    } while (0)
#else
#define DEBUGN(fmt, ...)
#endif

#endif // MSG_DBG

