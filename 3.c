#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>


#define BIN_LEN 5


int create_shell(void){
    char path_command[256]={0};
    int stat;
    pid_t f;
    
    while(1){
        if(fgets(path_command,sizeof(path_command),stdin)==NULL){
            break;
        };        
        size_t len=strlen(path_command);
        path_command[len-1]=0;
        f=fork();
        if(f==-1){
            printf("Error creating son process, exiting shell\n");
            _exit(EXIT_FAILURE);
        }
        if(f==0){
            
            int ex_stat=execlp(path_command,path_command,NULL);
            if(ex_stat==-1){
                printf("I'm process nubmer: %d\n",getpid());
                printf("Error, running the command: %s\n",path_command);
                perror("execl error");
            }
            _exit(EXIT_FAILURE);

        }
        else if(f!=0){
            memset(path_command,0,sizeof(path_command));
            while(wait(&stat)!=-1){    
            };
        }   
    }
    return -1;
}


int main(void) {
    //code
    //allow watching in debuging
    setbuf(stdout, NULL);
    create_shell();
    return 0;
}