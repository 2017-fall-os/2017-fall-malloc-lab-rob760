#include "stdio.h"
#include "stdlib.h"
#include "myAllocator.h"
#include "sys/time.h"
#include <sys/resource.h>
#include <unistd.h>

double diffTimeval(struct timeval *t1, struct timeval *t2) {
  double d = (t1->tv_sec - t2->tv_sec) + (1.0e-6 * (t1->tv_usec - t2->tv_usec));
  return d;
}

void getutime(struct timeval *t)
{
  struct rusage usage;
  getrusage(RUSAGE_SELF, &usage);
  *t = usage.ru_utime;
}

int main() 
{
  void *p1, *p2, *p3,*p4;
  arenaCheck();
  p1 = firstFitAllocRegion(254);
  p2 = firstFitAllocRegion(254);
  p3 = firstFitAllocRegion(254);
  p4 = firstFitAllocRegion(254);
  printf("%8zx %8zx %8zx %8zx\n", p1, p2, p3, p4);
  arenaCheck();
  printf("freeing region p3\n");
  freeRegion(p3);
  arenaCheck();
  freeRegion(p1);
  arenaCheck();
    
    void *p5, *p6 *p7;
    p5 = nextFitAllocRegion(512);
    p6 = nextFitAllocRegion(8);
    p7 = nextFitAllocRegion(32);
    arenaCheck();
    
    
    
  {				/* measure time for 10000 mallocs */
    struct timeval t1, t2;
    int i;
      
      
      // testing time for firstFit
    getutime(&t1);
    for(i = 0; i < 10000; i++)
      if (firstFitAllocRegion(8) == 0)
	break;
    getutime(&t2);
    printf("%d firstFitAllocRegion(8) required %f seconds\n", i, diffTimeval(&t2, &t1));
      
      
      
      //testing time for nextFit
      getutime(&t1);
      for(i = 0; i < 10000; i++)
          if (nextFitAllocRegion(8) == 0)
              break;
      getutime(&t2);
      printf("%d nextFitAllocRegion(8) required %f seconds\n", i, diffTimeval(&t2, &t1));
  }
  return 0;
}



