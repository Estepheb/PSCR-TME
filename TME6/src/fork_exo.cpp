#include <iostream>
#include <unistd.h>
#include <sys/wait.h>	

int main () {
	const int N = 3;
	std::cout << "main pid=" << getpid() << std::endl;
	int n = 0;
	bool b = true;
	for (int i=1, j=N; i<=N && j==N && fork()==0 ; i++ ) {
		std::cout <<" i:j " << i << ":" << j << std::endl;
		n=0;
		for (int k=1; k<=i && j==N ; k++) {
			if ( fork() == 0) {
				j=0;
				n = 0;
				b = false;
				std::cout <<" k:j " << k << ":" << j << std::endl;
			} else {
				n++;
			}
		}
		if (i == N) b=false;
	}

	for (int i=0;i<n;i++) {
		
		std::cout << getpid() <<" attend  "<< wait(NULL)<< std::endl;
	}
	if (b) {
		std::cout  << getpid() <<" attend  "<<wait(NULL)<< std::endl;
	}
	return 0;
}
