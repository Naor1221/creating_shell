#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>


#define BIN_LEN 5

void insert_bin_path(char *path_command){
    char bin_path[]="/bin/";
    size_t len=strlen(bin_path);
    //לעשות בדיקה על path command מחייב לקבל את הפרמטר של הגודל בבתים
    //כי אי אפשר לחשב את זה כשהוא ארגומנט
    //ומצד שני גם לחשב עם strlen לא יעזור לי כאן
    if(path_command==NULL){
        printf("path_command is null\n");
        return;
    }
    for(size_t i=0;i<len;i++){
        path_command[i]=bin_path[i];
    }
}

int create_shell(void){
    char path_command[256]={0};
    // insert_bin_path(path_command);
    int stat;
    pid_t f;
    while(1){
        if(fgets(path_command/* +BIN_LEN */,sizeof(path_command)/* -BIN_LEN */,stdin)==NULL){
            break;
        };        
        size_t len=strlen(path_command/* +BIN_LEN */);
        path_command[len/* +BIN_LEN */-1]=0;
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
            memset(path_command/* +BIN_LEN */,0,sizeof(path_command)/* -BIN_LEN */);
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