#include "Banque.h"

#include <iostream>

using namespace std;

namespace pr {

void Banque::transfert(size_t deb, size_t cred, unsigned int val) {
	Compte & debiteur = comptes[deb];
	Compte & crediteur = comptes[cred];

	recursive_mutex& Md=debiteur.getMutex();
	recursive_mutex& Mc=crediteur.getMutex();
//defer lock ne lock pas desuite
	unique_lock<recursive_mutex>gd(Md,defer_lock);
	unique_lock<recursive_mutex>gc(Mc,defer_lock);

	//Necessaire pour le comptable sinon il block tous
	if (deb < cred) {
		gd.lock();//le debiteur avant le crediteur car l'adresse du crediteur est superieur
		gc.lock();// donc le comptable deblock avant le debiteur	
	} else {
		gc.lock();
		gd.lock();
	}


	if (debiteur.debiter(val)) {
		crediteur.crediter(val);
	}
}
size_t Banque::size() const {
	return comptes.size();
}
bool Banque::comptabiliser (int attendu) {
	int bilan = 0;
	int id = 0;
	for ( auto & compte : comptes) {
		compte.getMutex().lock();
		if (compte.getSolde() < 0) {
			cout << "Compte " << id << " en négatif : " << compte.getSolde() << endl;
		}
		/*else {
			cout << "Compte " << id << " en positif : " << compte.getSolde() << endl;
		}*/
		bilan += compte.getSolde();
		id++;
	}

	for ( auto & compte : comptes) {
		compte.getMutex().unlock();
	}

	if (bilan != attendu) {
		cout << "Bilan comptable faux : attendu " << attendu << " obtenu : " << bilan << endl;
	}
	/*else{
		cout << "Bilan comptable bon : attendu " << attendu << " obtenu : " << bilan << endl;
	}*/
	return bilan == attendu;
}
}
