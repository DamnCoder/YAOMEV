/**
 * BTAComposeState.h
 *
 *  Created on: 27/09/2010
 *      Author: jorge
 */

#ifndef BTACOMPOSESTATE_H_
#define BTACOMPOSESTATE_H_

#include "YaoController.h"

namespace app {

	class CStateHandler;

	class CYaoCompositeController : public CYaoController {
	public:
		CYaoCompositeController(CYaoApp* app);
		virtual ~CYaoCompositeController();

		virtual void onCreate();
		virtual void onDestroy();
		virtual void onRun(float dt);

		void addState(const std::string& name, CYaoController* state );
		void setState(const std::string& name);
		void setPreviousState();

	private:
		CStateHandler*	_stateHandler;
	};

}

#endif /* BTACOMPOSESTATE_H_ */
