#ifndef MESSAGE_H
#define MESSAGE_H

#include "cabe.h"
#include "debug.h"

class message
{
public:
	int id;
	double timeCreated;
	int size;
	int from;
	int to;
	vector<int> path;

	void createMessage(int id, int from, int to, int size);
	void setId(int id);
	void setSize(int size);
	void setNodes(int from,int to);
	int getId();
	int getSize();
	void addPath(int id);
	int pathSize();
};

void message::createMessage(int id, int from, int to, int size, double time){
	this->setId(id);
	this->setSize(size);
	this->setNodes(from,to);
	this->timeCreated = time;
}

int message::pathSize(){ return this->path.size(); }

void message::addPath(int id){
	this->path.push_back(id);
}

void message::setId(int id){ this->id = id; }

void message::setSize(int size){ this->size = size; }

void message::setNodes(int from, int to){ 
	this->from = from;
	this->to = to;
}

int message::getId(){ return this->id; }

int message::getSize(){ return this->size; }

#endif