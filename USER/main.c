#include "main.h"
#include "FreeRTOS.h" 
#include "task.h" 

#define START_TASK_PRIO 1                   /* �������ȼ� */
#define START_STK_SIZE  128                 /* �����ջ��С */
TaskHandle_t            StartTask_Handler;  /* ������ */
void start_task(void *pvParameters);        /* ������ */


#define TASK1_PRIO      10                   /* �������ȼ� */
#define TASK1_STK_SIZE  128                 /* �����ջ��С */
TaskHandle_t            Task1Task_Handler;  /* ������ */
void task1(void *pvParameters);             /* ������ */


#define TASK2_PRIO      8                   /* �������ȼ� */
#define TASK2_STK_SIZE  128                 /* �����ջ��С */
TaskHandle_t            Task2Task_Handler;  /* ������ */
void task2(void *pvParameters);             /* ������ */


#define TASK3_PRIO      6                   /* �������ȼ� */
#define TASK3_STK_SIZE  128                 /* �����ջ��С */
TaskHandle_t            Task3Task_Handler;  /* ������ */
void task3(void *pvParameters);             /* ������ */
 
#define TASK4_PRIO      4                   /* �������ȼ� */
#define TASK4_STK_SIZE  128                 /* �����ջ��С */
TaskHandle_t            Task4Task_Handler;  /* ������ */
void task4(void *pvParameters);             /* ������ */

int main(void)
{
	 
	
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
    delay_init();
    HardWare_Init();
	
    UARTx_Init(USART1,115200);
    USART_DMACmd(USART1,USART_DMAReq_Rx,ENABLE);
    DMACHx_Init(DMA1_Channel3, (u32)&(USART1->DT), (u32)s_UartDma.pDmaBuf, UART1_BUF_LEN);//����1RXͨ��13������2RXͨ��15
    
    Communite_Init();  
    //������ʼ����
    xTaskCreate((TaskFunction_t )start_task,            /* ������ */
                (const char*    )"start_task",          /* �������� */
                (uint16_t       )START_STK_SIZE,        /* �����ջ��С */
                (void*          )NULL,                  /* ������������Ĳ��� */
                (UBaseType_t    )START_TASK_PRIO,       /* �������ȼ� */
                (TaskHandle_t*  )&StartTask_Handler);   /* ������ */
    vTaskStartScheduler();    
}
void start_task(void *pvParameters)
{
    taskENTER_CRITICAL();           /* �����ٽ��� */
    /* ��������1 */
    xTaskCreate((TaskFunction_t )task1,                 /* ������ */
                (const char*    )"task1",               /* �������� */
                (uint16_t       )TASK1_STK_SIZE,        /* �����ջ��С */
                (void*          )NULL,                  /* ������������Ĳ��� */
                (UBaseType_t    )TASK1_PRIO,            /* �������ȼ� */
                (TaskHandle_t*  )&Task1Task_Handler);   /* ������ */
    /* ��������2 */
    xTaskCreate((TaskFunction_t )task2,                 /* ������ */
                (const char*    )"task2",               /* �������� */
                (uint16_t       )TASK2_STK_SIZE,        /* �����ջ��С */
                (void*          )NULL,                  /* ������������Ĳ��� */
                (UBaseType_t    )TASK2_PRIO,            /* �������ȼ� */
                (TaskHandle_t*  )&Task2Task_Handler);   /* ������ */
    /* ��������3 */
    xTaskCreate((TaskFunction_t )task3,                 /* ������ */
                (const char*    )"task3",               /* �������� */
                (uint16_t       )TASK3_STK_SIZE,        /* �����ջ��С */
                (void*          )NULL,                  /* ������������Ĳ��� */
                (UBaseType_t    )TASK3_PRIO,            /* �������ȼ� */
                (TaskHandle_t*  )&Task3Task_Handler);   /* ������ */
    /* ��������4 */
    xTaskCreate((TaskFunction_t )task4,                 /* ������ */
                (const char*    )"task4",               /* �������� */
                (uint16_t       )TASK4_STK_SIZE,        /* �����ջ��С */
                (void*          )NULL,                  /* ������������Ĳ��� */
                (UBaseType_t    )TASK4_PRIO,            /* �������ȼ� */
                (TaskHandle_t*  )&Task4Task_Handler);   /* ������ */   
    vTaskDelete(StartTask_Handler); /* ɾ����ʼ���� */
    taskEXIT_CRITICAL();            /* �˳��ٽ��� */
}
void task1(void *pvParameters)
{   

    while (1)
    { 
//        Get_UsartPack(&tagProtocol[e_Prot_Uart1]);	//����DMA����,�����ݰ�ͷ�Ĳ�ͬ�����벻ͬ�Ĵ�����
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

