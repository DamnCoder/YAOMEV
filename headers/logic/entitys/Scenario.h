/*
 * Scenario.h
 *
 *  Created on: 10/12/2010
 *      Author: jorge
 */

#ifndef SCENARIO_H_
#define SCENARIO_H_

#include "utilitys/utils.h"

namespace gui{
	class CAbstractCamera;
}

namespace logic {

	class CScreen;

	class CEntity;
	class CAvatar;
	class CPlayer;
	class CQuizShowHost;
	class CMultimediaFurniture;

	/**
	 * Clase contenedora de todas las entidades que
	 * participan en el juego y que pertenecen a un
	 * escenario de juego.
	 *
	 * Diferenciamos entre dos tipos, por un lado las
	 * entidades estaticas (objetos inertes del escenario)
	 * y por otro lado las animadas.
	 */
	class CScenario {

	public:

		typedef vector<CMultimediaFurniture*>	TMultFurnList;
		typedef vector<CEntity*> 				TEntityList;
		typedef vector<CAvatar*> 				TAvatarList;
		typedef vector<CPlayer*> 				TPlayerList;

		typedef TMultFurnList::iterator			TMultFurIterator;
		typedef TEntityList::iterator 			TEntityIterator;
		typedef TAvatarList::iterator 			TAvatarIterator;
		typedef TPlayerList::iterator 			TPlayerIterator;

		CScenario();
		~CScenario();

		void actualizeEntitys(float dt);

		void addEntity(CEntity* newEntity);
		void addFurniture(CEntity* furniture);
		void addMultimediaFurniture(CMultimediaFurniture* furniture);
		void addCharacter(CAvatar* avatar);
		void addAudience(CAvatar* newPublic);
		void addPlayer(CPlayer* player);

		void setScreen(CScreen* screen);
		void setScreen(CEntity* screenmult);
		void setHost(CQuizShowHost* host);

		vector<CEntity*> 					entitys()		const { return _entitys; }
		vector<CEntity*> 					furniture() 	const { return _furniture; }
		vector<CMultimediaFurniture*> 		multFurniture() const { return _multFurniture; }
		vector<CAvatar*> 					avatares() 		const { return _avatares; }
		vector<CAvatar*>					audience()		const { return _audience; }
		vector<CPlayer*> 					players() 		const { return _players; }
		CScreen* 							screen() 		const { return _screen; }
		CEntity*							screenMult() 	const { return _screenmult; }
		CQuizShowHost* 						host() 			const { return _host; }
		std::vector<gui::CAbstractCamera*>	getCameras() 	const { return _cameras; }
	    const std::string 					id()			const { return _id; }

	    void setId(const std::string& _id){ this->_id = _id; }
		void setCameras(const std::vector<gui::CAbstractCamera*> cameras){ _cameras = cameras; }
		void setVisible(bool visible);
		void setAudienceAppearance(int numPlayer, const string& id, const string& skin, int scale);

	private:

		std::string			_id;

		TEntityList			_entitys;		/** Lista global de todas las entidades */
		TEntityList			_furniture;		/** Lista del mobiliario del escenario */
		TMultFurnList		_multFurniture;	/** Lista de mobiliario multimedia */
		TAvatarList			_avatares;		/** Conjunto de todos los avatares del juego */
		TAvatarList			_audience;		/** Avatares del publico */
		TPlayerList			_players;		/** Lista de jugadores */
		CQuizShowHost*		_host;
		CScreen*			_screen;
		CEntity*			_screenmult;

		std::vector<gui::CAbstractCamera*>	_cameras;

		bool				_visible;
	};

}

#endif /* SCENARIO_H_ */
