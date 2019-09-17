
#ifndef __TIMER_H__
#define __TIMER_H__

#include <stdbool.h>
#include <stddef.h>

#if defined(__cplusplus)
extern "C" {
#endif

/** @name timer handle */
/**@{*/
typedef void* timer;
/**@}*/

/**
 * 定时器回调函数
 *
 * @param[in] timer_handle
 * @param[in] context 自定义参数
 */
typedef void (timer_h)(timer timer_handle, void * context);


/**
 * 创建定时器实例
 *
 * @param[in] timer_handle
 * @param[in] context 自定义参数
 */
int timer_create(timer * timer_handle);


/**
 * 开始定时器
 *
 * @param[in] timer_handle
 * @param[in] cb 定时器回调函数
 * @param[in] cb_arg 定时器回调函数自定义参数
 * @param[in] timeout 如果 timeout 为 0 ，则立即执行，单位：秒
 * @param[in] repeat 如果 repeat 不为 0，则定时器会在 timeout 后重复执行，单位：秒
 * @return 0：返回成功，其他值失败
 */
int timer_start(timer timer_handle, timer_h cb, void * cb_arg,
        unsigned int timeout, unsigned int repeat);


/**
 * 结束定时器
 *
 * @param[in] timer_handle
 * @return 0：返回成功，其他值失败
 */
int timer_stop(timer timer_handle);

/**
 * 设置定时器循环周期
 *
 * @param[in] timer_handle
 * @param[in] repeat 定时器循环周期，单位：秒
 * @return 0：返回成功，其他值失败
 */
int timer_set_repeat(timer timer_handle, unsigned int repeat);


/**
 * 注销定时器
 *
 * @param[in] timer_handle
 */
void timer_destroy(timer timer_handle);


#ifdef __cplusplus
}
#endif

#endif /* __TIMER_H__ */
