#include "Banque.h"

using namespace std;
const int NB_THREAD = 10;
const int NB_COMPTE = 5;

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





int main () {
	pr::Banque banque(NB_COMPTE,10);
	vector<thread> threads;
	banque.comptabiliser(10*NB_COMPTE);
	for(int i=0;i<NB_THREAD;i++)
	{
		threads.emplace_back(exo1_q1,ref(banque));
	}

	for (auto & t : threads) {
		t.join();
	}
	banque.comptabiliser(10*NB_COMPTE);
	// TODO : tester solde = NB_THREAD * JP
	return 0;
}
