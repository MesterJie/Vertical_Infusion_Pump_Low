#include "main.h"
#include "FreeRTOS.h" 
#include "task.h" 

#define START_TASK_PRIO 1                   /* 任务优先级 */
#define START_STK_SIZE  128                 /* 任务堆栈大小 */
TaskHandle_t            StartTask_Handler;  /* 任务句柄 */
void start_task(void *pvParameters);        /* 任务函数 */


#define TASK1_PRIO      10                   /* 任务优先级 */
#define TASK1_STK_SIZE  128                 /* 任务堆栈大小 */
TaskHandle_t            Task1Task_Handler;  /* 任务句柄 */
void task1(void *pvParameters);             /* 任务函数 */


#define TASK2_PRIO      8                   /* 任务优先级 */
#define TASK2_STK_SIZE  128                 /* 任务堆栈大小 */
TaskHandle_t            Task2Task_Handler;  /* 任务句柄 */
void task2(void *pvParameters);             /* 任务函数 */


#define TASK3_PRIO      6                   /* 任务优先级 */
#define TASK3_STK_SIZE  128                 /* 任务堆栈大小 */
TaskHandle_t            Task3Task_Handler;  /* 任务句柄 */
void task3(void *pvParameters);             /* 任务函数 */
 
#define TASK4_PRIO      4                   /* 任务优先级 */
#define TASK4_STK_SIZE  128                 /* 任务堆栈大小 */
TaskHandle_t            Task4Task_Handler;  /* 任务句柄 */
void task4(void *pvParameters);             /* 任务函数 */

int main(void)
{
	 
	
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
    delay_init();
    HardWare_Init();
	
    UARTx_Init(USART1,115200);
    USART_DMACmd(USART1,USART_DMAReq_Rx,ENABLE);
    DMACHx_Init(DMA1_Channel3, (u32)&(USART1->DT), (u32)s_UartDma.pDmaBuf, UART1_BUF_LEN);//串口1RX通道13，串口2RX通道15
    
    Communite_Init();  
    //创建开始任务
    xTaskCreate((TaskFunction_t )start_task,            /* 任务函数 */
                (const char*    )"start_task",          /* 任务名称 */
                (uint16_t       )START_STK_SIZE,        /* 任务堆栈大小 */
                (void*          )NULL,                  /* 传入给任务函数的参数 */
                (UBaseType_t    )START_TASK_PRIO,       /* 任务优先级 */
                (TaskHandle_t*  )&StartTask_Handler);   /* 任务句柄 */
    vTaskStartScheduler();    
}
void start_task(void *pvParameters)
{
    taskENTER_CRITICAL();           /* 进入临界区 */
    /* 创建任务1 */
    xTaskCreate((TaskFunction_t )task1,                 /* 任务函数 */
                (const char*    )"task1",               /* 任务名称 */
                (uint16_t       )TASK1_STK_SIZE,        /* 任务堆栈大小 */
                (void*          )NULL,                  /* 传入给任务函数的参数 */
                (UBaseType_t    )TASK1_PRIO,            /* 任务优先级 */
                (TaskHandle_t*  )&Task1Task_Handler);   /* 任务句柄 */
    /* 创建任务2 */
    xTaskCreate((TaskFunction_t )task2,                 /* 任务函数 */
                (const char*    )"task2",               /* 任务名称 */
                (uint16_t       )TASK2_STK_SIZE,        /* 任务堆栈大小 */
                (void*          )NULL,                  /* 传入给任务函数的参数 */
                (UBaseType_t    )TASK2_PRIO,            /* 任务优先级 */
                (TaskHandle_t*  )&Task2Task_Handler);   /* 任务句柄 */
    /* 创建任务3 */
    xTaskCreate((TaskFunction_t )task3,                 /* 任务函数 */
                (const char*    )"task3",               /* 任务名称 */
                (uint16_t       )TASK3_STK_SIZE,        /* 任务堆栈大小 */
                (void*          )NULL,                  /* 传入给任务函数的参数 */
                (UBaseType_t    )TASK3_PRIO,            /* 任务优先级 */
                (TaskHandle_t*  )&Task3Task_Handler);   /* 任务句柄 */
    /* 创建任务4 */
    xTaskCreate((TaskFunction_t )task4,                 /* 任务函数 */
                (const char*    )"task4",               /* 任务名称 */
                (uint16_t       )TASK4_STK_SIZE,        /* 任务堆栈大小 */
                (void*          )NULL,                  /* 传入给任务函数的参数 */
                (UBaseType_t    )TASK4_PRIO,            /* 任务优先级 */
                (TaskHandle_t*  )&Task4Task_Handler);   /* 任务句柄 */   
    vTaskDelete(StartTask_Handler); /* 删除开始任务 */
    taskEXIT_CRITICAL();            /* 退出临界区 */
}
void task1(void *pvParameters)
{   

    while (1)
    { 
//        Get_UsartPack(&tagProtocol[e_Prot_Uart1]);	//接收DMA数据,并根据包头的不同，进入不同的处理函数
        Sys_Led();  
        vTaskDelay(10);
    }
}

void task2(void *pvParameters)
{   
    static uint16_t cnt = 0;
    while (1)
    {
        cnt++;
        vTaskDelay(10);
    }
}


void task3(void *pvParameters)
{   
    while (1)
    {
       vTaskDelay(10);
    }
}
void task4(void *pvParameters)
{   
    while (1)
    {
       vTaskDelay(10);
    }
}

