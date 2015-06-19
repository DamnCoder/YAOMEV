/**
 * mTextureManager.h
 *
 * Basado en CTextureManager v1.00 [5/22/01] de Christopher Smith
 * Christopher.Smith@Trinity.edu
 * www.cs.trinity.edu/~csmith8
 *
 * Modificado por Jorge López González para adaptarlo al framework MoLo3D.
 *
 * Redefincion de los tipos usados originalmente.
 * Uso de un template para convertir la clase en singleton.
 * Uso de SDL_image para la carga de imagenes.
 */

#ifndef MTEXTUREMANAGER_H_
#define MTEXTUREMANAGER_H_

#include "utilitys/utils.h"
#include "utilitys/Singleton.h"

#include <SDL/SDL.h>

namespace gui{

	using namespace std;
	
	/**
	 * Clase que centraliza la carga y gestion de texturas usando OpenGL y SDL.
	 * Mediante SDL_image se realiza la carga de las texturas y despues se asocia a OpenGL.
	 * Todas las texturas se crean con sus correspondiente mip maps.
	 */
	class CTextureCache : public CSingleton<CTextureCache> {

	friend class CSingleton<CTextureCache>;

	public :

		//---------------------------------------------------------------------------------------------------------------
		// Usage / Implementation
		//---------------------------------------------------------------------------------------------------------------
		/**
		 * Carga una imagen (tga, png, bmp o jpg) usando SDL_image y se le asigna un ID
		 *
		 *
		 * @param filename
		 * @param newTextureID
		 * @return
		 */
		uint loadTexture(const string& filename, uint newTextureID = -1);

		/**
		 * Si nID se encuentra en la lista de IDs, se borrara de la lista y liberara la memoria
		 * asignada a esa textura.
		 *
		 * Si no se encuentra en la lista no se hara nada.
		 *
		 * @param nID Correspondiente con la ID de la textura a eliminar
		 */
		void freeTexture(uint nID);

		/**
		 * Elimina la lista de IDs usadas y libera la memoria asignada a las texturas.
		 */
		void freeAll();

		//---------------------------------------------------------------------------------------------------------------
		// Debug / Utilitarian
		//---------------------------------------------------------------------------------------------------------------

		/**
		 * Si ha ocurrido un error, se habra almacenado en la variable szErrorMessage. Esta funcion
		 * simplemente devuelve ese mensaje.
		 *
		 * @return El mensaje de error que haya ocurrido o una cadena vacia
		 */
		string getErrorMessage() const { return szErrorMessage; }

		/**
		 * Devuelve el numero de IDs de texturas asignadas
		 *
		 * @return El numero de IDs asignadas.
		 */
		int getNumTextures() const { return (int)nTexIDs.size(); }

	protected :

		//---------------------------------------------------------------------------------------------------------------
		// Constructor / Destructor
		//---------------------------------------------------------------------------------------------------------------

		CTextureCache();

		virtual ~CTextureCache();

	private:

		SDL_Surface* mirrorImage(SDL_Surface* surface);

		//---------------------------------------------------------------------------------------------------------------
		// Carga de imagenes
		//---------------------------------------------------------------------------------------------------------------

		/**
		 * A partir del parametro pasado como argumento intentara asignarlo como ID a la textura, si no puede asignara
		 * otra ID valida y la devolvera.
		 *
		 * Si el ID pasado como argumento ya existe en la lista, lo devolvera
		 *
		 * @param nPossibleTextureID. Posible ID para la textura
		 * @return La ID asignada.
		 */
		uint getNewTextureID(uint nPossibleTextureID);	// get a new one if one isn't provided

		uint checkTexture(const std::string& filename);

		//---------------------------------------------------------------------------------------------------------------
		// ATRIBUTOS
		//---------------------------------------------------------------------------------------------------------------

		typedef list<uint>::iterator idIterator;

		typedef map<std::string, uint>::iterator TTexturesHashIterator;

		string		szErrorMessage;		// Mensaje de error

		list<uint>	nTexIDs;			// Lista de identificadores de textura

		map<std::string, uint>	_textureIDs;
	};

}



#endif
