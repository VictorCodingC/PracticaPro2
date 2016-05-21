#include "cjtextosvictor.hh"

Cjt_Textos::Cjt_Textos(){
	triat = false;
	it_triat = ctextos.end();
}

void Cjt_Textos::imprimir_vector(vector<string>& v){
	for(int i=0; i<v.size(); ++i){
		cout << v[i] << ' ';
	}
	cout << endl;
}

void Cjt_Textos::crear_vfrase(string s, vector<string>& frase){
	istringstream iss(s);
	string op;
	iss >> op;
	while(iss){
		frase.push_back(op);
		iss >> op;
		}
}

bool Cjt_Textos::trobar_paraules(vector<string> v, Text& t){
	vector <string> titol;
	crear_vfrase(t.consultar_titol(), titol);
	
	vector <string> autor;
	crear_vfrase(t.consultar_autor(), autor);
	
	vector <bool> vb(v.size(), 0);
	
	for(int i=0; i<v.size(); ++i){  //buscar al títol
		for(int j=0; j<titol.size() and not vb[i]; ++j){
			if(v[i] == titol[j]) vb[i] = true;
		}
	}
		
	for(int i=0; i<v.size(); ++i){  //buscar al autor
		for(int j=0; j<autor.size() and not vb[i]; ++j){
			if(v[i] == autor[j]) vb[i] = true;
		}
	}
		
	for(int i=0; i<v.size(); ++i){  //buscar al contingut
		if (not vb[i]){
			Cjt_Frases cfrases;
			cfrases= t.consultar_contingut();
			if(cfrases.conte_paraula(v[i])) vb[i]=true;
			}
	}
	
	for(int i=0; i<vb.size(); ++i){
		if (not vb[i]) return false;
		}
	return true;
}

bool Cjt_Textos::ordena(aut_tit a,aut_tit b){
	if (a.autor != b.autor) return a.autor < b.autor;
	return a.titol < b.titol;
}


void Cjt_Textos::afegir_text(const Text& text){
	list <Text>::iterator fi;
	fi = ctextos.end();
	ctextos.insert(fi,text);
}
	
void Cjt_Textos::eliminar_text(){
	it_triat = ctextos.erase(it_triat);
	triat = false;
	}
	
void Cjt_Textos::triar_text(string& s){
	s.erase(0,12);
	s.erase(s.size()-1, 1);
	list<Text>::iterator it;
	bool b=false;
	bool b2=false;
	for(it=ctextos.begin(); it!=ctextos.end(); ++it){
		Text t=*it;
		vector <string> frase;
		crear_vfrase(s, frase);
		if(trobar_paraules(frase, t) and not b){
			b=true;
			it_triat=it;
			triat=true;
			}
		else if (trobar_paraules(frase, t) and b){
			b2=true;
			triat=false;
			break;	
		}
	}
	if(not b) triat=false;
	
}

bool Cjt_Textos::text_triat(){
	return triat;
	}
	
Text Cjt_Textos::consultar_text_triat(){
	Text text = (*it_triat);
	return text;
	}

void Cjt_Textos::imprimir_textos(){
	vector <aut_tit> v (ctextos.size());
	list <Text>::iterator it;
	int i = 0;
	for (it = ctextos.begin(); it != ctextos.end(); ++it){
		v[i].autor = (*it).consultar_autor();
		v[i].titol = (*it).consultar_titol();
		++i;
		}
	sort(v.begin(), v.end(),ordena);
	for (int i = 0; i < v.size();++i){
		cout << v[i].autor << ' ' << '"' << v[i].titol << '"' << endl;
		}
	}

void Cjt_Textos::imprimir_tots_autors() const{
	vector<s1> v;
	list<Text>::const_iterator it;
	for(it=ctextos.begin(); it!=ctextos.end(); ++it){
		Text text=*it;
		Cjt_Frases cfrases = text.consultar_contingut();
		bool b=false;
		int i;
		for(i=0; i<v.size() and not b; ++i){
			if(v[i].aautor==text.consultar_autor()) b=true;
			}
		--i;
		cout << "la i ---> "<< i << endl;
		
		if(b) {
			++v[i].num_textos;
			v[i].num_paraules += cfrases.numero_de_paraules();
			v[i].num_frases += cfrases.numero_de_frases();
			cout << "segon text ---> "<< v[i].num_frases << endl;
			}

		else{
			s1 aux;
			aux.num_textos = 1;
			aux.aautor = text.consultar_autor();
			aux.num_frases = cfrases.numero_de_frases();
			aux.num_paraules = cfrases.numero_de_paraules();
			v.push_back(aux);
			cout << "primer text ---> "<< aux.num_frases << endl;
			}
	}
	cout << "tamany vector ---> " << v.size() << endl;
	for(int i=0; i<v.size(); ++i){
		cout << v[i].aautor << ' ' << v[i].num_textos << ' ' << v[i].num_frases << ' ' << v[i].num_paraules << endl;
		}
}
