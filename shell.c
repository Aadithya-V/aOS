#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>


struct Args{
    int argc;
    char* argv[32];    
};

struct Args command_prompt(){
    
    char input[32];
    printf("~$  ");
    fgets(input, sizeof(input)-2, stdin);
    input[strcspn(input, "\n")] = 0;  //removing the "\n" attached at the end, courtesy of fgets.
    
    struct Args args;
    args.argc = 0;
        
    char* token = strtok(input, " ");
    *(args.argv) = token;
    
    while (token != NULL){
        args.argc++;
        token = strtok(NULL, " ");
        args.argv[args.argc]  =  token;
    }
    args.argv[args.argc + 1] = NULL;  //End of argv marked my NULL pointer by convention
    return args;
}   


void main(){
    while (1){
        struct Args args = command_prompt();
        
        if (fork() != 0){
            int statloc;
            waitpid(-1, &statloc, 0 );
        }
        else{
            execve(args.argv[0], args.argv,0);
            exit();
        }
    }
 }
 