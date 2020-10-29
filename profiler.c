
/********************************* 
Author: Parth Pathak (2020PCS1013)
**********************************/

#include <stdio.h>
#include <malloc.h>
#include <time.h>
#include "parth.h"

void fun1(void)
{
  f1 = clock();
  int i = 1024, l;
  void * p = malloc(i);
  
  free(p);
  p = NULL;
  for(l = 0; l < 4000000; l++){
  }
  if(p != NULL){
    flag = "NO";
  }else
  {
    flag = "YES";
  }
  f1 = clock() - f1;
  double t1 = time_taken(f1);
  printf("Fun 1:\t  %d\t %s\t %f\r\n", i, flag, t1);
}

void fun2(void)
{
  f2 = clock();
  int j = 100, l;
  void * p = malloc(j);
  
  //free(p);
  //p = NULL;
  for(l = 0; l < 3000000; l++){
  }
  if(p != NULL){
    flag = "NO";
  }else
  {
    flag = "YES";
  }
  f2 = clock() - f2;
  double t2 = time_taken(f2);
  printf("Fun 2:\t  %d\t %s\t %f\r\n", j, flag, t2);
}

void fun3(void)
{
  f3 = clock();
  int k = 10, l;
  void * p = malloc(k);
  
  //free(p); /* << memory leak added here*/
  //p = NULL;
  for(l = 0; l < 2000000; l++){
  }
  if(p != NULL){
    flag = "NO";
  }else
  {
    flag = "YES";
  }
  f3 = clock() - f3;
  double t3 = time_taken(f3);
  printf("Fun 3:\t  %d\t %s\t %f\r\n", k, flag, t3);
}

void fun4(void)
{
  f4 = clock();
  int l = 20, m;
  void * p = malloc(l);
  int i;
  free(p); /* << memory leak added here*/
  p = NULL;
  for(m = 0; m < 1000000; m++){
  }
  if(p != NULL){
    flag = "NO";
  }else
  {
    flag = "YES";
  }
  f4 = clock() - f4;
  double t4 = time_taken(f4);
  printf("Fun 4:\t  %d\t %s\t %f\r\n", l, flag, t4);
}

int main(int argc, char *argv[])
{
  begin = clock();
  printf("\n********************Execution Profiler********************\r\n\n");
  printf("--------------------------------------------\n");
  printf("Function  Bytes  Freed?  Execution Time\n");
  printf("--------------------------------------------\n");
  fun1(); 
  fun2();
  fun3();
  fun4();
  printf("--------------------------------------------\n");
  show_mem_stat();
  begin = clock() - begin;
  double time_spent = time_taken(begin);
  printf("Total Execution Time: %f", time_spent);
  long double util = get_cpu_util();
  printf("\nThe current CPU utilization is: %lf\n", util);
  return 0;
}