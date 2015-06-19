#ifndef __BEHAVIOR_H_
#define __BEHAVIOR_H_

/**
 * @file Behavior
 * Clases abstractas correspondientes a los distintos tipos de comportamiento
 * que existen para implementar.
 */
namespace logic{

	class CGame;
	class CEntity;
	class CAvatar;

	class CBehavior{
	public:
		CBehavior(logic::CGame* game):_game(game), _active(false){}
		virtual ~CBehavior(){};

		virtual void activate() = 0;
		virtual void actualize(float dt) = 0;
	
	protected:
		CGame*		_game;
		bool		_active;
	};

}
#endif /*__BEHAVIOR_H_*/
