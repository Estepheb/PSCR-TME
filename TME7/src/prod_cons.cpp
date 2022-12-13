#include "Stack.h"
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <vector>
#include <semaphore.h>
#include <sys/stat.h>
 #include <fcntl.h> 


using namespace std;
using namespace pr;

void producteur (Stack<char> * stack) {
	char c ;
	while (cin.get(c)) {
		stack->push(c);
	}
}

void consomateur (Stack<char> * stack) {
	while (true) {
		char c = stack->pop();
		cout << c << flush ;
	}
}

int main () {

	Stack<char> * s = new Stack<char>();
	int a=2000,b=2000;
	sem_t* sem1 =sem_open("/monsem1",O_CREAT|O_EXCL|O_RDWR,0600,0);
	sem_t* sem2 =sem_open("/monsem2",O_CREAT|O_EXCL|O_RDWR,0600,1);

	pid_t pp = fork();
	if (pp==0) {
		//producteur(s);
		//return 0;
		for(int i=0;i<10;i++){

			sem_wait(sem1);
			cout<<"Pong"<<endl;
			sem_post(sem2);
		}
			if(sem_close(sem1)==0)cout<<"BIEN CLOSE SEM1 FORK1"<<endl;
			if(sem_close(sem2)==0)cout<<"BIEN CLOSE SEM2 FORK1"<<endl;
		return 0;
	}

	pid_t pc = fork();
	if (pc==0) {
		//consomateur(s);
		//return 0;
		for(int i=0;i<10;i++){
			sem_wait(sem2);
			cout<<"Ping"<<endl;
			sem_post(sem1);
		}
			if(sem_close(sem1)==0)cout<<"BIEN CLOSE SEM1 FORK2"<<endl;
			if(sem_close(sem2)==0)cout<<"BIEN CLOSE SEM2 FORK2"<<endl;
		return 0;
	}
	if(sem_close(sem1)==0)cout<<"BIEN CLOSE SEM1 Main"<<endl;
	if(sem_close(sem2)==0)cout<<"BIEN CLOSE SEM2 Main"<<endl;

	wait(0);
	wait(0);
	sem_unlink("/monsem1");
	sem_unlink("/monsem2");

	//delete s;
	return 0;
}