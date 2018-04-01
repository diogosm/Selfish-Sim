#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <stack>
#include <algorithm>
#include <cmath>
#include <math.h>
#include <map>
#include <set>
#include <queue>
#include <iterator>
#include <sstream>
#include <ext/numeric>
#include <bitset>
#include <list>
#include <string>
#include <unistd.h>
#include <limits.h>
#include <string>

using namespace std;

typedef struct
{
	int tempo;
	string estado;
	int from,to;
} setting;

typedef struct
{
	int id;
	set<int> buffer;
	set<int> finalBuffer;
	set<int> provsBuffer;
} nodo;

map<int, pair<int,int> > messagens;
std::vector<setting> vet;
int grafo[97][97];
std::vector<nodo> nodos;
double SELFISH_LEVEL = 0.0;
int UNIQUE_ID_MESSAGE = 0;
int SENDED = 0;
int REJECTED = 0;
int tempo;

void send(int from, int to, int id){
	double aleat = rand()/(1.*INT_MAX);
	messagens[id] = make_pair(from,to);
	if(aleat > SELFISH_LEVEL){
		nodos[from].buffer.insert(id);
		SENDED++;
		for(int i = 0;i<97;i++){
			if(grafo[from][i] && i!=from){
				nodos[i].buffer.insert(id);
				if(i==to){
					nodos[i].finalBuffer.insert(id);
					nodos[i].buffer.erase(id);
				}
			}
		}
	}else{
		REJECTED++;
	}
}

void report(){
	//cout<<"Nivel de egoismo: ";
	printf("%.2lf ", SELFISH_LEVEL);
	cout<<SENDED<<" "<<REJECTED<<" ";
	int taxaEntrega = 0;
	for(unsigned int i = 0;i<nodos.size();i++) taxaEntrega += nodos[i].finalBuffer.size();
	cout<<taxaEntrega<<endl;
	//cout<<"\n";
}

void update(){
	for(unsigned int i = 0;i<nodos.size();i++){
		for(unsigned int j = 0;j<nodos.size();j++){
			if(i==j) continue;
			if(grafo[i][j] && rand()/(1.*INT_MAX) > SELFISH_LEVEL){
				for(set<int>::iterator it = nodos[i].buffer.begin();it!=nodos[i].buffer.end();it++){
					nodos[j].provsBuffer.insert(*it);
				}
				for(set<int>::iterator it = nodos[j].buffer.begin();it!=nodos[j].buffer.end();it++){
					nodos[i].provsBuffer.insert(*it);
				}
			}
		}
	}

	for(unsigned int i = 0;i<nodos.size();i++){
		for(set<int>::iterator it = nodos[i].provsBuffer.begin();it!=nodos[i].provsBuffer.end();it++){
			nodos[i].buffer.insert(*it);
			if(messagens[*it].second == i) nodos[i].finalBuffer.insert(*it), nodos[i].buffer.erase(*it);
		}
		nodos[i].provsBuffer.clear();
	}

	for(unsigned int i = 0;i<nodos.size() && tempo%10000==0;i++){
		//cout<<"tamanho do buffer em "<<i<<": "<<nodos[i].finalBuffer.size()<<endl;
	}
}

void run(){
	tempo=1;
	int indice = 0;
	memset(grafo,0,sizeof(grafo));
	for(unsigned int i = 0;i<nodos.size();i++) nodos[i].buffer.clear(), nodos[i].finalBuffer.clear(), nodos[i].provsBuffer.clear();;
	SENDED = REJECTED = UNIQUE_ID_MESSAGE = 0;
	messagens.clear();

	while(tempo < vet[vet.size()-1].tempo && tempo < 50000){
		//if(tempo%10000 == 0) cout<<"debug "<<tempo<<endl;
		while(tempo==vet[indice].tempo){
			if(vet[indice].estado=="up"){
				grafo[vet[indice].from][vet[indice].to] = 1;
			}else{
				grafo[vet[indice].from][vet[indice].to] = 0;
			}
			indice++;
		}

		if(tempo%5==0 && UNIQUE_ID_MESSAGE <= 1000){
			int a = rand()%97; int b=rand()%97;
			while(b==a){b=rand()%97;}
			send(28,b,UNIQUE_ID_MESSAGE++);
		}

		++tempo;

		update();
	}
}

int main(int argc, char const *argv[])
{
	srand(time(NULL));
	int tempo;
	string t1,t2;
	int from,to;

	while(cin>>tempo>>t1>>from>>to>>t2){
		setting aux;
		aux.tempo = tempo;
		aux.estado = t2;
		aux.from = from;
		aux.to = to;
		vet.push_back(aux);
	}
	nodo aux;
	for(unsigned int i = 0;i<97;i++){
		aux.id = i;
		nodos.push_back(aux);
	}

	while(SELFISH_LEVEL<=1.0 + 1e-5){
		run();
		report();
		SELFISH_LEVEL+=0.05;
	}

	return 0;
}