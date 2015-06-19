/**
 * AppState.h
 *
 * Interfaz que define el comportamiento de los diferentes estados
 * del juego.
 *
 *  Created on: 27/10/2009
 *      Author: jorge
 */

#ifndef CAPPSTATE_H_
#define CAPPSTATE_H_

#include "app/Application.h"

#include "utilitys/hfsm/State.h"

namespace app {

	/**
	 * Interfaz que deben implementar todos los estados de una aplicacion gestionada por app::CApplication
	 */
	class CApplicationState : public utils::IState {

	public:

		/**
		 * Constructor
		 */
		CApplicationState(CApplication *app) : _app(app) {}

		/**
		 * Destructor
		 */
		virtual ~CApplicationState(){}

		/**
		 * Función llamada por la aplicación para que se ejecute
		 * la funcionalidad del estado.
		 * @param dt Número de milisegundos transcurridos desde
		 * la última llamada (o desde la áctivación del estado, en caso
		 * de ser la primera vez...).
		 */
		virtual void onRun(float dt){}

	protected:

		CApplication* _app;	// Instancia de la aplicacion

	};

}


#endif /* CAPPSTATE_H_ */
