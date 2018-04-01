#ifndef NODE_H
#define NODE_H

#include "cabe.h"
#include "buffer.h"
#include "debug.h"

class node
{
public:
	int id;
	buffer Buffer;

	void setId(int id);
	int getId();
	void initNode(int id);
};

void node::initNode(int id){
	this->setId(id);
	this->Buffer.setBuffer(id);
}

void node::setId(int id){ this->id = id; }

int node::getId(){ return id; }

#endif