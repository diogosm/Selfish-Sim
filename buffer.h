#ifndef BUFFER_H
#define BUFFER_H

#include "cabe.h"
#include "message.h"
#include "debug.h"

#define MAX_SPACE 10 //Em MB. Para valor em B mult por 1000

class buffer
{
public:
	int id;
	int space;		//Espaco total
	int	busy;		//Espaco ocupado
	vector<message> disk;	//buffer em si
	set<int> msgsAtDisk;
	vector<message> received;	//messages para mim

	void setBuffer(int id);
	int	getFreeSpace();
	void addMessage(message msg);
	int hasMessage(int idMsg);
	void eraseMessage(int idMsg);
};

void buffer::setBuffer(int id){ 
	this->id = id;
	this->space = MAX_SPACE;
	this->busy = 0;
	this->disk.clear();
}

int buffer::getFreeSpace(){
	return this->space-this->busy;
}

int buffer::hasMessage(int idMsg){
	if(this->msgsAtDisk.find(idMsg)!=this->msgsAtDisk.end())
		return 1;
	return 0;
}

void buffer::addMessage(message msg){
	int enoughSpace = this->getFreeSpace();
	if(msg.getSize() > enoughSpace){
		char enough[7]; sprintf(enough,"%d",msg.getId());
		string debug = "Message "; debug += enough;
		debug += " is bigger than enough space";
		DEBUG(debug);
	}else{
		char enough[7]; sprintf(enough,"%d",msg.getId());
		string debug = "Message "; debug+=enough;
		debug += " armazenada com sucesso no nodo ";
		sprintf(enough,"%d",this->id);
		debug += enough;
		DEBUG(debug);

		this->disk.push_back(msg);			//armazeno a msg e atualizo busy
		this->busy += msg.getSize();
		this->msgsAtDisk.insert(msg.getId());
	}
}

void buffer::eraseMessage(int idMsg){
	if(this->hasMessage(idMsg)==0) return;

	this->msgsAtDisk.erase(idMsg);
	for(vector<message>::iterator it = this->disk.begin();
		it!=this->disk.end();it++){
		if(it->getId() == idMsg){
			this->busy -= it->getSize();
			this->disk.erase(it);
			break;
		}
	}
}

#endif