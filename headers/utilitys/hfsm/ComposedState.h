/*
 * ComposedState.h
 *
 *  Created on: 06/04/2011
 *      Author: jorge
 */

#ifndef COMPOSEDSTATE_H_
#define COMPOSEDSTATE_H_

#include "StateHandler.h"

namespace utils{

	class CComposedState : public IState {
	public:

		CComposedState():
			_stateHandler(0)
		{}

		virtual ~CComposedState()
		{
			delete _stateHandler;
		}

		virtual void onCreate()
		{
			_stateHandler = new CStateHandler();
		}

		virtual void onDestroy()
		{
			_stateHandler->releaseAll();
		}

		void addState(const std::string& name, IState* state )
		{
			if(!name.empty() || state)
				_stateHandler->addState(name, state);
		}

		void setState(const std::string& name){
			if(!name.empty())
				_stateHandler->setState(name);
		}

	private:

		CStateHandler* _stateHandler;
	};

}

#endif /* COMPOSEDSTATE_H_ */
