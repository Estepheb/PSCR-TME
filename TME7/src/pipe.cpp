#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <vector>
#include <string.h>

int main (int argc, char ** argv) {
    int pfd [2];//pfd[0] == lecture pfd[1] == ecriture
    pipe(pfd);
    int i;
    argv[0]=0;
    
    char* argv1[20]={0};
    char* argv2[20]={0};

    for(i=1;i<argc;i++){
        argv1[i-1]=argv[i];
         //std::cout<<argv[i]<<std::endl;    
        if(strcmp(argv[i],"|")==0){
            argv[i]=0;
            argv1[i-1]=0;
            break;}
    }
    std::cout<<argc<<"\t"<<i<<std::endl;


    if((fork())==0){
        dup2(pfd[1],STDOUT_FILENO);//l'ecriture correspond au Out de ce fork la sortie de ce exec sera donc lu au bout du pipe
        
        close (pfd[1]);
        close (pfd[0]);

        execv(argv1[0],argv1);//execv pour utiliser un tableau
        return 0;
    }

    if((fork())==0){
        dup2(pfd[0],STDIN_FILENO);//lit donc la sortie du premier fils 
        //STDIN du fork2  = STDOUT du fork1 
        close (pfd[0]);
        close (pfd[1]);
        execl("/bin/wc","wc","-l",NULL);
        return 0;
    }

    close (pfd[0]);//fermeture des pipes dans le main sinon les autres ne peuvent pas se fermer.
    close (pfd[1]);
    wait(0);//attend les deux processus
    wait(0);
    return 0;
}