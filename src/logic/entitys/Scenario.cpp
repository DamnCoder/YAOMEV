/*
 * Scenario.cpp
 *
 *  Created on: 10/12/2010
 *      Author: jorge
 */

#include "logic/entitys/Scenario.h"

#include "logic/entitys/Player.h"
#include "logic/entitys/Host.h"
#include "logic/entitys/MultimediaFurniture.h"
#include "logic/entitys/Screen.h"

#include "gui/cam/AbstractCamera.h"

namespace logic {

	CScenario::CScenario():
			_screen(0),
			_visible(true)

	{
	}

	CScenario::~CScenario() {

		deleteVector(_entitys);
		deleteVector(_cameras);
		safeDelete(_screen);

		_entitys.clear();
		_avatares.clear();
		_players.clear();
		_audience.clear();
		_furniture.clear();
		_multFurniture.clear();
	}

	void CScenario::setScreen(CScreen* screen){
		_screen = screen;
	}

	void CScenario::setScreen(CEntity* screenmult){
		_screenmult = screenmult;
	}

	void CScenario::setHost(CQuizShowHost* host){
		_host = host;
		addCharacter(host);
	}

	void CScenario::addEntity(CEntity* entity){
		_entitys.push_back(entity);
	}

	void CScenario::addFurniture(CEntity* furniture){
		addEntity(furniture);
		_furniture.push_back(furniture);
	}

	void CScenario::addMultimediaFurniture(CMultimediaFurniture* furniture) {
		addEntity(furniture);
		_multFurniture.push_back(furniture);
	}

	void CScenario::addCharacter(CAvatar* avatar){
		addEntity(avatar);
		_avatares.push_back(avatar);
	}

	void CScenario::addAudience(CAvatar* avatar){
		addCharacter(avatar);
		_audience.push_back(avatar);
	}

	void CScenario::addPlayer(CPlayer* player){
		addCharacter(player);
		_players.push_back(player);
	}

	void CScenario::setVisible(bool visible){
		if(_visible == visible) return;

		TEntityIterator it(_entitys.begin()),end(_entitys.end());
		for(; it!=end; ++it)
			(*it)->setVisible(visible);

		_screen->setVisible(visible);

		_visible = visible;
	}

	void CScenario::setAudienceAppearance(int numPlayer, const string& id, const string& skin, int scale){
		CAvatar* audienceMember = _audience[numPlayer];
		audienceMember->setId(id);
		audienceMember->setSkin(skin);
		audienceMember->setScale(scale);
		//cout<<"[CGame::setPlayerAppearance] ID: "<<_players[numPlayer]->getId()<<" Nombre: "<<_players[numPlayer]->getName()<<"\n";
	}

	void CScenario::actualizeEntitys(float dt){
		TEntityIterator it(_entitys.begin()), end(_entitys.end());
		for(;it!=end; ++it)
			(*it)->actualize(dt);

		_screen->actualize(dt);
	}

}
