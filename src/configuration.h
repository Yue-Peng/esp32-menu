// 波特率
#define BAUD_RATE 115200

// 线程堆栈大小设置，以字节为单位
#define DISPLAY_TASK_STACK_SIZE (5 * 1024) // 5k
#define PROCESS_TASK_STACK_SIZE (5 * 1024) // 1k

// 线程循环刷新率，这里是一个预估值，
// 实际刷新率会受到线程中的延时影响
#define DISPLAY_REFRESH_RATE 20
#define PROCESS_REFRESH_RATE 2
