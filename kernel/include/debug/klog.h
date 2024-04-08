#ifndef _DEBUG_KLOG_H_
#define _DEBUG_KLOG_H_

#define klog(fmt, ...) _klog("%s: " fmt "\n", __func__, ## __VA_ARGS__)

void _klog(char *fmt, ...);

#endif /* _DEBUG_KLOG_H_ */
