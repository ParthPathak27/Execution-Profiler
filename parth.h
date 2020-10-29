#include<stdio.h>
#include<malloc.h>
#include<time.h>
int total, freed;
char * flag;
clock_t begin, f1, f2, f3, f4;

typedef struct _mem_node_t
{
  void * mem_pointer;
  char * file_name;
  char * function;
  int line;
  int size;
  int flag;

} mem_node_t ;

#define MAX_MEM_PTRS 1024
mem_node_t mem_node[MAX_MEM_PTRS];

void *add_mem_node(int size, char * file_name, int line, char * function)
{

  int i = 0;
  int ret = -1;

  void *pointer = malloc(size);

  for(i = 0; i < MAX_MEM_PTRS; i++) {
      if(mem_node[i].flag == 0) {
        total += size;
        mem_node[i].flag = 1;
        mem_node[i].mem_pointer = pointer;
        mem_node[i].file_name = file_name;
        mem_node[i].function = function;
        mem_node[i].line = line;
        mem_node[i].size = size;
        ret = 0;
        break;
      }
  }
  return pointer;
}

void del_mem_node(void * mem_pointer)
{

  int i = 0;
  int ret = -1;

  for(i = 0; i < MAX_MEM_PTRS; i++) {
      if(mem_node[i].mem_pointer == mem_pointer) {
        freed += mem_node[i].size;
        mem_node[i].flag = 0;
        mem_node[i].mem_pointer = NULL;
        mem_node[i].file_name = 0;
        mem_node[i].function = 0;
        mem_node[i].line = 0;
        mem_node[i].size = 0;
        ret = 0;
        free(mem_pointer);
        break;
      }
  }
  return;
}

void show_mem_stat(void)
{
  int i = 0;
  int ret = 0;
  printf("\nTotal memory allocated: %d bytes\n", total);
  printf("Total memory freed: %d bytes\n", freed);
  printf("Total memory unfreed: %d bytes\n", total - freed);
  for(i = 0; i < MAX_MEM_PTRS; i++) {

      if(mem_node[i].flag == 1) {
        printf("0x%p of %d bytes allocated"
               " from %s:%d in %s() is not freed\r\n",
               mem_node[i].mem_pointer,
               mem_node[i].size,
               mem_node[i].file_name,
               mem_node[i].line,
               mem_node[i].function);
        ret = 1;
      }
  }
  
  if(ret == 0) {
     printf("\nno memory leak detected!\r\n");
  }
  return;
}

double time_taken(clock_t begin){
  return ((double)begin) / CLOCKS_PER_SEC;
}

double get_cpu_util(){
  long double a[4], b[4], loadavg;
  FILE *fp;
  char dump[50];
  fp = fopen("/proc/stat","r");
  fscanf(fp,"%*s %Lf %Lf %Lf %Lf",&a[0],&a[1],&a[2],&a[3]);
  fclose(fp);
  fp = fopen("/proc/stat","r");
  fscanf(fp,"%*s %Lf %Lf %Lf %Lf",&b[0],&b[1],&b[2],&b[3]);
  fclose(fp);
  loadavg = ((b[0]+b[1]+b[2]) - (a[0]+a[1]+a[2])) / ((b[0]+b[1]+b[2]+b[3]) - (a[0]+a[1]+a[2]+a[3]));
  return loadavg;
}

#undef malloc
#define malloc(size) add_mem_node(size, \
                                  __FILE__, \
                                  __LINE__, \
                                  (char*)__FUNCTION__)
#undef free
#define free(_p) del_mem_node(_p)
