#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdint.h>

#define BIN_LEN 5


int create_shell(void){
    char path_command[256]={0};
    int stat;
    pid_t f;
    uint8_t counter=0;
    char history_arr[100][10]={0};
    uint8_t add_flag=1;
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
            if(strcmp(path_command,"history")==0){
                continue;
            }
            int ex_stat=execlp(path_command,path_command,NULL);

            if(ex_stat==-1){
                printf("I'm process nubmer: %d\n",getpid());
                printf("Error, running the command: %s\n",path_command);
                perror("execl error");                
                _exit(EXIT_FAILURE);
            }
        
            _exit(EXIT_SUCCESS);


        }
        else if(f!=0){
            if(strcmp(path_command,"history")==0){
                uint8_t i=0;
                while(history_arr[i][0]!=0){
                    printf("%s\n",history_arr[i]);
                    i++;
                }
                add_flag=0;
            }
            if(add_flag==1){
                if(counter==100){
                    counter=0;
                }
                strcpy(history_arr[counter++],path_command);

            }
            memset(path_command,0,sizeof(path_command));
            add_flag=1;
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