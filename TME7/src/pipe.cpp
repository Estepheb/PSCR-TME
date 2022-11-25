#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <vector>

int main (int argc, char ** argv) {
    int pfd [2];
    pipe(pfd);

    pid_t f1,f2,p;
    p=getpid();
    
    
    if((f1=fork())==0){
        f1=getpid();
        dup2(pfd[1],STDOUT_FILENO);
        close (pfd[1]); close (pfd[0]);
        execl("/bin/cat","cat","pipe.cpp",NULL);//execv pour utiliser un tableau
        //read(pfd[0],&f2,sizeof(pid_t));//attends le pid de f2
        //dup2(f1,f2);//remplace f2 par f1

    return 0;
    }
    if((f2=fork())==0){
        f2=getpid();

        dup2(pfd[0],STDIN_FILENO);
        //write(pfd[1],&f2,sizeof(pid_t));
        close (pfd[0]);
        close (pfd[1]);
        execl("/bin/wc","wc","-l",NULL);
        return 0;
    }
    std::cout<<std::endl;
    return 0;
}