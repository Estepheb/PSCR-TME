#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "rsleep.h"
using namespace std;

char pv = 3;//Point de vie

void handlerPV(int signum) {
	pv--;
	if (!pv) {
		cout << getpid() << " est mort"<<endl;
		exit(0);
	}
	cout << getpid() << " vie : " << (int)pv << endl;
}

void attaque(pid_t adversaire){/* La phase d'attaque commence par installer un gestionnaire pour le signal SIGINT, qui
décrémente les  points de vie  du processus et affiche le nombre de points restants. Si
0 est atteint il affiche que le processus se termine, et celui-ci se termine en retournant 1.
 Ensuite le processus envoie un signal SIGINT à l'adversaire ; si cette invocation échoue,
on suppose que l'adversaire a déjà perdu, et le processus sort avec la valeur 0 ;
 Ensuite le processus s'endort pour une durée aléatoire.*/
//    cout<<"Attaque sur : "<<adversaire<<endl;
//Setup du handler pour recevoir les attaques 
    //preparation au sigaction 
        struct sigaction s;
        sigset_t sig_proc;
        sigemptyset(&sig_proc);
        s.sa_mask=sig_proc;
        s.sa_flags=0;
        s.sa_handler = handlerPV;
    //
    sigaction(SIGINT,&s,NULL);

    if(kill(adversaire,SIGINT))
    {
        cout << getpid() << " : " << (int)pv << "restant"<<endl;
		exit(0);
    }
	randsleep();
}


void defense(){/*La phase de défense consiste à désarmer le signal SIGINT en positionnant son action à SIG_IGN ;
    Ensuite le processus s'endort pour une durée aléatoire.*/
    //cout<<"Defense de : "<<getpid()<<endl;
    //preparation au sigaction
        struct sigaction s;
        sigset_t sig_proc;
        sigemptyset(&sig_proc);
        s.sa_mask=sig_proc;
        s.sa_flags=0;
        s.sa_handler = SIG_IGN;
    //
    sigaction(SIGINT,&s,NULL);
    randsleep();
    //cout<<"Fin de defense de "<<getpid()<<endl;
}

void combat(pid_t adversaire){
    cout<<"Début du combat pour : "<<getpid()<<" contre : "<<adversaire<<endl;
    /*boucle indéfniment sur une défense suivie d'une attaque et invoquez-la dans le corps des deux fils.*/
    while(true){
        attaque(adversaire);
        defense();
        

    }
}



int main(void){

    pid_t Vador=getpid();
    pid_t Luke=fork();
    if (Luke==0){Luke =getpid();} 
    cout<<"Pid de Vador : "<<Vador<<endl<<" Pid de Luke : "<<Luke<<endl<<endl;
/*Debut du combat*/
    if(getpid()==Vador)
        combat(Luke);
    else
        combat(Vador);


    return 0;
}