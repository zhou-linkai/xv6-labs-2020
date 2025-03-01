#include "kernel/types.h"
#include "user/user.h"
#include "kernel/stat.h"
#include "kernel/fs.h"


void find(char * path, char * filename)
{
   int fd;
   char buf[512], *p;
   struct stat st;
   struct dirent de;
   if((fd = open(path, 0)) < 0){
      fprintf(2, "open path error!\n");
      return;
   }
   if(fstat(fd, &st)){
      fprintf(2, "find : cannot fstat %s", path);
      return;
   }

   if(st.type != T_DIR){
      fprintf(2, "usage: find <directory> <filename>\n");
      return;
   }
   if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
      fprintf(2, "path too long!\n");
      return;
   }
   strcpy(buf, path);
   p = buf + strlen(buf);
   *p++ = '/';
   while(read(fd, &de, sizeof de) == sizeof de){
      if(de.inum == 0){
         continue;
      }
      memmove(p, de.name, DIRSIZ);
      p[DIRSIZ] = 0;

      if(stat(buf, &st)){
         fprintf(2, "find: stat error!\n");
	 continue;
      }

      if(st.type == T_DIR && strcmp(p, ".") != 0 && strcmp(p, "..") != 0){
        find(buf, filename);
      }else if(strcmp(p, filename) == 0){
        printf("%s\n", buf);
      }
   
   }
   close(fd);
}


int main(int argc, char* argv[])
{
    if(argc != 3){
       fprintf(2, "usage: find <directory> <filename>\n");
    }
    find(argv[1], argv[2]);
    exit(0);
}
