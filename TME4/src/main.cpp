#include "Banque.h"

using namespace std;
const int NB_THREAD = 100;
const int NB_COMPTE = 50;
const int ARGENT =10;

void exo1_q1 (pr::Banque& b)
{
	for(int k=0;k<1000;k++)
	{
		int i = rand()%NB_COMPTE;
		int j = rand()%NB_COMPTE;
		int m = (rand()%100) + 1;
		int timesleep = rand()%20;
		b.transfert(j,i,m);
		
		this_thread::sleep_for(chrono::milliseconds(timesleep));
		
	}

}


void comptabiliserEnBoucle(pr::Banque& b) {
	while(1) {
		/*int timesleep = rand()%20;
		this_thread::sleep_for(chrono::milliseconds(timesleep));*/
		b.comptabiliser(NB_COMPTE * ARGENT);
	}
}


int main () {
	pr::Banque banque(NB_COMPTE,ARGENT);
	vector<thread> threads;
	time_t t;
	time(&t);
	srand(t);
	banque.comptabiliser(ARGENT*NB_COMPTE);
	for(int i=0;i<NB_THREAD;i++)
	{
		threads.emplace_back(exo1_q1,ref(banque));
	}

	thread comptable(comptabiliserEnBoucle,ref(banque));

	for (auto & t : threads) {
		t.join();
	}
	comptable.detach();
	banque.comptabiliser(0);
	// TODO : tester solde = NB_THREAD * JP
	return 0;
}
