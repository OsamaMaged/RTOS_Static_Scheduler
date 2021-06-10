

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>
#include <stdlib.h>
/* Demo includes. */
#include "basic_io.h"
#include "time.h"
#include "tm4c123gh6pm.h"
#include "stdint.h"
/* The task functions. */

int i,Ta,Tc,Tp,n;
float cpu=.0;
int times = 0;
int Tasks_info[15];
int P[5];
int Period[5];
int A[5];
int C[5];
int Priority[5];
int N=5;
int latest_arrival_time=15;
int maximum_computation_time=8;
int maximum_period_multipler=17;


static void random( int low,int high );
void delayMs(int);
void vTask1(void *pvParameters );
void vTask2(void *pvParameters );
void vTask3(void *pvParameters );
void vTask4(void *pvParameters );
void vTask5(void *pvParameters );
void schedule(void);
void priority(void);
int largest(int arr[], int n);
void creating_task(int, int);
/*-----------------------------------------------------------*/

int main( void )
{
	int k;
	int count;
	start:
	k=0;
	count = 0;
	cpu=0;
	random(2,N);
	n=i;
	printf("number of tasks is %d\n",n);
	for(k=0;k<3*n;k++)
	{ 
		if(k%3==0){
		printf("Task %d \n",++count);
		schedule();
		Tasks_info[k]=Ta;
			A[k/3]=Ta;
			vPrintStringAndNumber("Ta: ",Tasks_info[k]);
		Tasks_info[k+1]=Tc;
			C[k/3]=Tc;
			vPrintStringAndNumber("Tc: ",Tasks_info[k+1]);
		Tasks_info[k+2]=Tp;
			P[k/3]=Tp;
			Period[k/3]=Tp*100;
			vPrintStringAndNumber("Tp: ",Tasks_info[k+2]);
			cpu=cpu+((float)Tc/(float)Tp);
			printf("%f \n",cpu);
			
			}
		}
		if(cpu>=0.7) {
			vPrintString("Failed schedulability");
			goto start;
	
	}
	printf("Schedulability is OK\n");
	priority();
	for( i=0; i<n;i++){
	creating_task(Priority[i],i+1);
	}
	vTaskStartScheduler();
	while(1);
}
/*-----------------------------------------------------------*/
void random(int low,int high)
{
	 i =(rand()%(high-low))+low;
}
/*-----------------------------------------------------------*/
void creating_task(int Priority, int TaskNumber)
{
		printf("%d: Task %d created\n",times,TaskNumber);
		switch(TaskNumber){
		case 1:
		xTaskCreate( vTask1,"vTask1", 100, NULL, Priority,NULL );
		break;
		case 2:
		xTaskCreate( vTask2, "vTask2", 100, NULL, Priority,NULL );
		break;
		case 3:
		xTaskCreate( vTask3, "vTask3", 100, NULL, Priority,NULL );
		break;
		case 4:
		xTaskCreate( vTask4, "vTask4", 100, NULL, Priority, NULL );
		break;
		case 5:
		xTaskCreate( vTask5,"vTask5", 100, NULL, Priority, NULL );
		break;}

}
/*-----------------------------------------------------------*/
void vTask1(void *pvParameters){
portTickType xLastWakeTime;
xLastWakeTime = xTaskGetTickCount();
for(;;){
int comp;
printf("Task 1 starts\n");
for(comp=0;comp<C[0];comp++){
printf("%d: Task 1 running\n",times);
times++;
delayMs(100);
}
		printf("%d: Task 1 suspends\n",times);
vTaskDelayUntil( &xLastWakeTime, (Period[0] / portTICK_RATE_MS ) );

}

}
/*-----------------------------------------------------------*/
void vTask2(void *pvParameters ){
portTickType xLastWakeTime;
xLastWakeTime = xTaskGetTickCount();
for( ;; ){
int comp;
printf("Task 2 starts\n");
for(comp=0;comp<C[1];comp++){
printf("%d: Task 2 running\n",times);
times++;
delayMs(100);
}
		printf("%d: Task 2 suspends\n",times);
vTaskDelayUntil( &xLastWakeTime, ( Period[1] / portTICK_RATE_MS ) );
}
}

void vTask3(void *pvParameters ){
portTickType xLastWakeTime;
xLastWakeTime = xTaskGetTickCount();
for( ;; ){
int comp;
printf("Task 3 starts\n");
for(comp=0;comp<C[2];comp++){
printf("%d: Task 3 running\n",times);
times++;
delayMs(100);
}
printf("%d: Task 3 suspends\n",times);
vTaskDelayUntil( &xLastWakeTime, ( Period[2] / portTICK_RATE_MS ) );
}}

void vTask4(void *pvParameters ){
portTickType xLastWakeTime;
xLastWakeTime = xTaskGetTickCount();
for( ;; ){
int comp;
printf("Task 4 starts\n");
for(comp=0;comp<C[3];comp++){
printf("%d: Task 4 running\n",times);
times++;
delayMs(100);
}
printf("%d: Task 4 suspends\n",times);
vTaskDelayUntil( &xLastWakeTime, ( Period[3] / portTICK_RATE_MS ) );
}}

void vTask5(void *pvParameters ){
portTickType xLastWakeTime;
xLastWakeTime = xTaskGetTickCount();
for( ;; ){
int comp;
printf("Task 5 starts\n");
for(comp=0;comp<C[4];comp++){
printf("%d: Task 5 running\n",times);
times++;
delayMs(100);
}
printf("%d: Task 5 suspends\n",times);
vTaskDelayUntil( &xLastWakeTime, ( Period[4] / portTICK_RATE_MS ) );
}}

void priority(void){ 
int max,index,ind,a;
	int same_max;
	for(a = n;a >= 1; a--)
	{
  int s = sizeof(P)/sizeof(P[0]); 
	max = largest(P,s);
	for(ind=0;ind<n;ind++)
		
		{ if(P[ind]== max)
		    {index=ind; break;}
		}
		if(!(same_max==max))
		{Priority[index]=a;}
		else{
	Priority[index]=a+1;}
		
	same_max = max;

	P[index]=-1;
	}
}
/*-----------------------------------------------------------*/
int largest(int arr[], int n) 
{ 
    int i; 
    int max = arr[0]; 
    for (i = 1; i < n; i++) 
        if (arr[i] > max) 
            max = arr[i]; 
  
    return max; 
} 
/*-----------------------------------------------------------*/
void schedule(void)
{
	random(0,latest_arrival_time);
	Ta=i;
	random(1,maximum_computation_time);
	Tc=i;
	//safe mode
	//random(3*Tc, maximum_period_multipler*Tc);
	//no guarantee mode
	random(3*Tc,10*Tc);
	Tp=i;
}

/*-----------------------------------------------------------*/
void vApplicationIdleHook( void )
{
	while(1){
	printf("%d: Idle\n",times);
	times++;
	delayMs(100);	
	}
}
/*-----------------------------------------------------------*/
void delayMs(int n){
  int i, j;
  for(i = 0 ; i < 2*n; i++)
    for(j = 0; j < 1080; j++)
    {} /* do nothing for 1 ms */
		}
		