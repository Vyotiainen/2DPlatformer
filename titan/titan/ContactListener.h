#pragma once

#include "Globalvars.h"
#include <Box2D/Box2D.h>
#include "Player.h"
#include <iostream>
#include <list>


class ContactListener : public b2ContactListener
{
public:
	std::list<Drawable *>* getDeleteList();
	ContactListener();
	void BeginContact(b2Contact *contact);
	void EndContact(b2Contact *contact);
	~ContactListener();
private:
	std::list<Drawable *> _deleteList;
};

