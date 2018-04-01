#include "cabe.h"
#include "node.h"
#include "buffer.h"
#include "message.h"
#include "debug.h"

typedef long long int llint;
typedef unsigned int uint;
typedef pair<int,int> pii;

#define MAX_SIMULATION_TIME 16981817

int UNIQUE_MESSAGE_ID = 0;
int UNIQUE_NODE_ID = 0;

//Trace file variable
//1-Time 2-type 3-from 4-to
vector<pair<int,pair<int,pii> > > traceSettings;

void init(){
	FILE *trace;
	trace = fopen("RealityConnectionTraceFinal.txt","r");
	int time,from,to;
	char tipo[5];
	while(fscanf(trace,"%d %*s %d %d %s",&time,&from,&to,tipo)!=EOF){
		pair<int,pair<int,pii> > aux;
		aux = make_pair(time,make_pair(tipo[0]=='u' ? 1 : 0,make_pair(from,to)));
		traceSettings.push_back(aux);
	}
}

void simul(){
	init();


	while(ATUAL_SIMULATION_TIME <= MAX_SIMULATION_TIME){
		ATUAL_SIMULATION_TIME++;
	}
}

int main(){

	ios::sync_with_stdio(false);

	/* Teste 
	node nodes[2];
	nodes[0].initNode(UNIQUE_NODE_ID++);
	nodes[1].initNode(UNIQUE_NODE_ID++);
	message msg;
	msg.createMessage(UNIQUE_MESSAGE_ID++,0,1,15);
	nodes[0].Buffer.addMessage(msg);
	msg.createMessage(UNIQUE_MESSAGE_ID++,0,1,15);
	nodes[0].Buffer.addMessage(msg);
	msg.createMessage(UNIQUE_MESSAGE_ID++,0,1,7);
	nodes[0].Buffer.addMessage(msg);
	printf("%d %d\n",nodes[0].getId(),nodes[0].Buffer.getFreeSpace());
	printf("%d\n", nodes[0].Buffer.hasMessage(msg.getId()));
	nodes[0].Buffer.eraseMessage(2);
	printf("%d\n", nodes[0].Buffer.hasMessage(msg.getId()));
	printf("%d %d\n",nodes[0].getId(),nodes[0].Buffer.getFreeSpace());
	*/

	simul();

	return 0;
}