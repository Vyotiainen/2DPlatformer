#include "ContactListener.h"
#include "PistolAmmo.h"
#include "NormalEnemy.h"

ContactListener::ContactListener()
{
}

void ContactListener::BeginContact(b2Contact *contact) {
	Player _temp;

	void* bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
	void* bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();

	void* fixtureUserDataA = contact->GetFixtureA()->GetUserData();
	void* fixtureUserDataB = contact->GetFixtureB()->GetUserData();

	//Players feetfixture is 1002, groundfixture is 1010
	if ((int)fixtureUserDataA == 1002 && (int)fixtureUserDataB == 1010 ||
		(int)fixtureUserDataA == 1010 && (int)fixtureUserDataB == 1002) {
		_temp.setFootCount(1);
	}

	//Ammofixtures start from 1101 and enemies 1011
	if (((int)fixtureUserDataA >= 1011 && (int)fixtureUserDataA <= 1100) &&
		(int)fixtureUserDataB >= 1101 ||
		(int)fixtureUserDataA >= 1101 &&
		((int)fixtureUserDataB >= 1011 && (int)fixtureUserDataB <= 1100)
		) {
		if (static_cast<Drawable*>(bodyUserDataA)->returnID() == PISTOLAMMO) {
			contact->GetFixtureA()->GetBody()->SetLinearVelocity(b2Vec2(0, 0));
			static_cast<NormalEnemy*>(static_cast<Drawable*>(bodyUserDataB))->takeDmg(static_cast<PistolAmmo*>(static_cast<Drawable*>(bodyUserDataA))->getDmg());
			_deleteList.push_back(static_cast<Drawable*>(bodyUserDataA));
			if (static_cast<NormalEnemy*>(static_cast<Drawable*>(bodyUserDataB))->getHp() <= 0){
				_deleteList.push_back(static_cast<Drawable*>(bodyUserDataB));
			}
		}
		else {
			contact->GetFixtureB()->GetBody()->SetLinearVelocity(b2Vec2(0, 0));
			static_cast<NormalEnemy*>(static_cast<Drawable*>(bodyUserDataA))->takeDmg(static_cast<PistolAmmo*>(static_cast<Drawable*>(bodyUserDataB))->getDmg());
			_deleteList.push_back(static_cast<Drawable*>(bodyUserDataB));
			if (static_cast<NormalEnemy*>(static_cast<Drawable*>(bodyUserDataA))->getHp() <= 0){
				_deleteList.push_back(static_cast<Drawable*>(bodyUserDataA));
			}
		}

	}

	//Player collides with enemy
	if ((int)fixtureUserDataA == 1001 && (int)fixtureUserDataB >= 1011 && (int)fixtureUserDataB <= 1100 ||
		(int)fixtureUserDataA >= 1011 && (int)fixtureUserDataA <= 1100 && (int)fixtureUserDataB == 1001){

		if (static_cast<Drawable*>(bodyUserDataA)->returnID() == PLAYER){
			if (static_cast<Player*>(static_cast<Drawable*>(bodyUserDataA))->getHp() > 0){
				static_cast<Player*>(static_cast<Drawable*>(bodyUserDataA))->takeDmg(10);
			}
		}
		else{
			if (static_cast<Player*>(static_cast<Drawable*>(bodyUserDataA))->getHp() > 0){
				static_cast<Player*>(static_cast<Drawable*>(bodyUserDataB))->takeDmg(10);
			}
		}
	}

	//Bullet collides with ground
	if ((int)fixtureUserDataA >= 1101 && (int)fixtureUserDataB == 1010){
		contact->GetFixtureA()->GetBody()->SetLinearVelocity(b2Vec2(0, 0));
		_deleteList.push_back(static_cast<Drawable*>(bodyUserDataA));
	}
	else if ((int)fixtureUserDataB >= 1101 && (int)fixtureUserDataA == 1010){
		contact->GetFixtureB()->GetBody()->SetLinearVelocity(b2Vec2(0, 0));
		_deleteList.push_back(static_cast<Drawable*>(bodyUserDataB));
	}
}

void ContactListener::EndContact(b2Contact *contact) {
	Player _temp;
	void* fixtureUserDataA = contact->GetFixtureA()->GetUserData();
	void* fixtureUserDataB = contact->GetFixtureB()->GetUserData();

	//Players feetfixture is 1002, groundfixture is 1010
	if ((int)fixtureUserDataA == 1002 && (int)fixtureUserDataB == 1010 ||
		(int)fixtureUserDataA == 1010 && (int)fixtureUserDataB == 1002) {
		_temp.setFootCount(-1);
	}

}

std::list<Drawable *>* ContactListener::getDeleteList() {
	return &_deleteList;
}

ContactListener::~ContactListener()
{
}
