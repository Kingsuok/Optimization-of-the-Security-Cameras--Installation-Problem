#include "stdio.h"
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc,char* argv[]){
	int fd1[2];
	int pid;
	int rw;
	rw = pipe(fd1);
	pid = fork();
	if(pid<0){
		perror("fork error");
		exit(-1);
	}else if(pid > 0){
    
        int i;
        int temp;
	//char buffer1[3];
	//int buffer2;
        if(argc>0){
	for (i=1;i<argc;i+=2){
			
			if(argv[i][1]=='s'){
				//sscanf(argv[i+1],"%d",&buffer2);
 				temp=atoi(argv[i+1]);
                                if(temp<2) {
                                printf("Error:the input is wrong.\n");
				fflush(stdout);
                                exit(0);
                                }
				
				}else if(argv[i][1]=='n'){
				temp=atoi(argv[i+1]);
                                if(temp<1) {
                                printf("Error:the input is wrong.\n");
                                fflush(stdout);
                                exit(0);
				}
			}else if(argv[i][1]=='l'){
				temp=atoi(argv[i+1]);
                                if(temp<5) {
                                printf("Error:the input is wrong.\n");
                                fflush(stdout);
                                exit(0);}
				}else {
				temp=atoi(argv[i+1]);
                                if(temp<1) {
                                printf("Error:the input is wrong.\n");
                                fflush(stdout);
                                exit(0);
			      }
			}
		 
	        }
	
	   }


        argv[0] = "rgen";
	close(fd1[0]);
	dup2(fd1[1],STDOUT_FILENO);
        execvp("./rgen", argv);       
	}
	else{
                int fd2[2];
	        int pid1;
	        int rw1;
	        rw1 = pipe(fd2);
	        pid1 = fork();
		if(pid1<0){
			perror("fork error");
			exit(-1);
			}else if(pid1 > 0){
		close(fd2[0]);
		dup2(fd2[1],STDOUT_FILENO);
		close(fd1[1]);
		dup2(fd1[0],STDIN_FILENO);
                execlp("python", "python","a1-ece650.py",NULL);  
                	
		}else {
		int fd3[2];
	        int pid2;
	        int rw2;
	        rw2 = pipe(fd3);
	        pid2 = fork();
		if(pid2<0){
			perror("fork error");
			exit(-1);
			}else if(pid2 > 0){
                //close(fd3[1]);
                //dup2(fd3[0],STDIN_FILENO);
		close(fd2[1]);
		dup2(fd2[0],STDIN_FILENO);   
		execl("./a2-ece650","a2-ece650",NULL);
		}else{
                      char *c = NULL;
		      size_t bytes = 0;
                      close(fd2[0]);
                      dup2(fd2[1],STDOUT_FILENO);
                      while(getline(&c, &bytes, stdin) != EOF){
                      printf("%s\n",c);
                      fflush(stdout);
                      }
                      if(c){
			free(c);
			}
		}
		}
	}
return 0;
}
