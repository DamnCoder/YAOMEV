/**
 * State.h
 *
 *	Interfaz que debe implementar cualquier estado
 *	de la maquina de estados.
 *
 *  Created on: 06/04/2011
 *      Author: jorge
 */

#ifndef STATE_H_
#define STATE_H_

namespace utils{

	/**
	 * Interfaz que debe implementar cualquier estado
	 * de la maquina de estados.
	 */
	class IState{
	public:

		/**
		 * Destructor
		 */
		virtual ~IState() {}

		/**
		 * Función llamada cuando se crea el estado.
		 * Sirve para inicializar todos aquellos elementos
		 * que solo necesitan iniciarse una vez.
		 */
		virtual void onCreate() {}

		/**
		 * Función llamada cuando se elimina el
		 * estado de la aplicación.
		 *
		 * Deberian destruirse todos los elementos
		 * inicializados en onCreate
		 */
		virtual void onDestroy() {}

		/**
		 * Función llamada por la aplicación cuando se activa
		 * el estado.
		 *
		 * Aqui se inician todos aquellos parametros que tengan
		 * que resetear su valor cada vez que se activa un
		 * estado
		 */
		virtual void onActivate() {}

		/**
		 * Función llamada por la aplicación cuando se desactiva
		 * el estado.
		 */
		virtual void onDeactivate() {}

	};
}

#endif /* STATE_H_ */
