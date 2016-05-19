#include "Text.hh"


void Text::llegir(istringstream iss){
	string paraula;
	iss >> paraula;
	bool primer = true;
	list <string>::iterator it = titol.begin();
	while (paraula[paraula.size()-1] != '"'){
		if (primer){
			paraula.erase(0,1);
			primer = false;
			titol.insert(it,paraula);
			iss >> paraula;
			}
		else {
			titol.insert(it,paraula);
			iss >> paraula;
			}
		}
	int ultima = paraula.size()-1;
	paraula.erase(ultima,0);
	titol.insert(it,paraula);
	
	it = autor.begin();
	cin >> paraula;
	primer = true;
	while (paraula[paraula.size()-1] != '"'){
		if (primer){
			paraula.erase(0,1);
			primer = false;
			autor.insert(it,paraula);
			cin >> paraula;
			}
		else {
			autor.insert(it,paraula);
			cin >> paraula;
			}
		}
	ultima = paraula.size()-1;
	paraula.erase(ultima,0);
	autor.insert(it,paraula);
	cjtfrase.llegir();
}
