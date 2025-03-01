#include "kernel/types.h"
#include "user/user.h"
#include "kernel/stat.h"
#include "kernel/param.h"

int main(int argc, char* argv[])
{
    char *new_argv[MAXARG];
    char buf[512];
    int i, n;

    for(i = 1; i < argc; ++i){
       new_argv[i - 1] = argv[i];
    }

    while((n = read(0, buf, sizeof(buf))) > 0)
    {
         int p = 0;
	 while(p < n){
	      int start = p;
	      while(p < n && buf[p] != '\n'){
	           p ++;
	      }
	      buf[p] = 0;
	      p ++;

	      new_argv[argc - 1] = buf + start;
	      new_argv[argc] = 0;

	      if(fork() == 0)
	      {
	         exec(new_argv[0], new_argv);
		 exit(1);
	      }else{
	         wait(0);
	      }
	 }
    }
    exit(0);

}
