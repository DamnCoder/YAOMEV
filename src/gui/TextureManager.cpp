#include "gui/TextureManager.h"

#include <GL/gl.h>
#include <GL/glu.h>

#include <SDL/SDL_image.h>
#include <SDL/SDL_rotozoom.h>

namespace gui{
	
	CTextureCache::CTextureCache()	{
	}
	
	CTextureCache::~CTextureCache() {
	}

	// ===================================================================
	uint CTextureCache::loadTexture(const std::string& filename, uint newTextureID){

		uint textureID;
		SDL_Surface* loadedImageTmp = 0;
		SDL_Surface* loadedImage = 0;

		//std::cout << "[CTextureManager::loadTexture] RUTA TEXTURA: " << filename << "\n";

		uint existingID =checkTexture(filename);
		if( existingID != (uint)-1)
			return existingID;

		loadedImageTmp = IMG_Load(filename.c_str());

		if(!loadedImageTmp){
			#ifdef _DEBUG
			cerr<<"Error en la carga de la imagen:"<<filename<<" motivo: "<<SDL_GetError()<<"\n";
			#endif
			return 0;
		}

		//std::cout << "[CTextureManager::loadTexture] Leo la imagen\n";

		//loadedImage = rotozoomSurfaceXY(loadedImageTmp, 0, 1, -1, 0);

		loadedImage = loadedImageTmp;
/*
		if(!loadedImage){
			#ifdef _DEBUG
			cerr<<"Error en la carga de la imagen: "<<SDL_GetError() << "\n";
			#endif
			return 0;
		}
*/
		textureID = getNewTextureID(newTextureID);
		//std::cout << "[CTextureManager::loadTexture] ID textura: "<<textureID<<"\n";
		glBindTexture(GL_TEXTURE_2D, textureID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		// Obtenemos el numero de canales de la surface SDL
		GLint nOfColors = loadedImage->format->BytesPerPixel;

		GLenum texture_format;
		switch(nOfColors){
		case 3:	// No tiene canal alpha
			if (loadedImage->format->Rmask == 0x000000ff)
					texture_format = GL_RGB;
			else
					texture_format = GL_BGR;
			break;
		case 4: // Tiene canal alpha
			if (loadedImage->format->Rmask == 0x000000ff)
					texture_format = GL_RGBA;
			else
					texture_format = GL_BGRA;
			break;
		default:
			texture_format = GL_RGBA;
		}

		gluBuild2DMipmaps(
				GL_TEXTURE_2D,
				nOfColors,
				loadedImage->w,
				loadedImage->h,
				texture_format,
				GL_UNSIGNED_BYTE,
				loadedImage->pixels
				);

		SDL_FreeSurface(loadedImage);
		//SDL_FreeSurface(loadedImageTmp);

		// Si no ha sido posible asignarse una textura, se habra otorgado el ID 0
		if(!textureID)
			return 0;

		_textureIDs[filename] = textureID;

		//std::cout << "[CTextureManager::loadTexture] Llego al final\n";
		return textureID;
	}

	void CTextureCache::freeTexture(uint nID) {
		// Eliminamos la textura de la lista
		nTexIDs.remove(nID);

		// Liberamos la memoria de la textura
		glDeleteTextures (1, &nID);

	}

	void CTextureCache::freeAll() {

		// Copiamos las IDs de la lista a un array de enteros sin signo
		uint* puiIDs = new uint[nTexIDs.size()];

		idIterator it(nTexIDs.begin()), end(nTexIDs.end());
		int i = 0;
		for(; it!=end; ++it){
			puiIDs[i] = (*it);
			++i;
		}

		// Liberamos la memoria
		glDeleteTextures (nTexIDs.size(), puiIDs);

		// Eliminamos el array creado
		delete [] puiIDs;
		puiIDs = 0;

		nTexIDs.clear();
	}

	// ===================================================================
	
	uint CTextureCache::getNewTextureID (uint nPossibleTextureID) {

		// Si hemos usado un ID valido
		if (nPossibleTextureID != (uint)-1) {

			// Recorremos la lista y si ya existe el ID, lo devolvemos.
			idIterator it(nTexIDs.begin()), end (nTexIDs.end());
			for (; it!=end; ++it)
				if ((*it) == nPossibleTextureID)
					return nPossibleTextureID;
		}

	
		// Si el ID pasado como argumento es -1, OpenGL asignara un ID valido
		uint nNewTextureID;
		if (nPossibleTextureID == (uint)-1)
			glGenTextures (1, &nNewTextureID);
		else // Si el usuario ha proporcionado un valor valido como ID usamos ese
			nNewTextureID = nPossibleTextureID;

		nTexIDs.push_back(nNewTextureID);

		return nNewTextureID;
	}

	uint CTextureCache::checkTexture(const std::string& filename){
		TTexturesHashIterator it = _textureIDs.find(filename);
		if(it == _textureIDs.end())
			return -1;

		return it->second;
	}

	SDL_Surface* CTextureCache::mirrorImage(SDL_Surface *surface) {

	    SDL_Rect origen;
	    SDL_Rect destino;


	    // Origen -> ancho una línea
	    // Comienzo de copia por el principio

	    origen.x = 0;
	    origen.y = 0;
	    origen.w = 1;
	    origen.h = surface->h;

	    // Destino -> ancho una lína
	    // Comienzo de 'pegado' por el final
	    // Para lograr la inversión

	    destino.x = surface->w;
	    destino.y = 0;
	    destino.w = 1;
	    destino.h = surface->h;

	    SDL_Surface *invertida;

	    // Pasamos surface a formato de pantalla

	    invertida = SDL_DisplayFormat(surface);

	    if(invertida == NULL) {

		cerr << "No podemos convertir la surface al formato de pantalla" << endl;
		return NULL;
	    }

	    // Preparamos el rectángulo nuevo vacío del color transparente

	    SDL_FillRect(invertida, NULL, SDL_MapRGB(invertida->format, 0, 255, 0));

	    // Copiamos linea vertical a linea vertical, inversamente
/*
	    for(int i = 0; i < surface->w; i++) {
			SDL_BlitSurface(surface, &origen, invertida, &destino);
			origen.x = origen.x + 1;
			destino.x = destino.x - 1;
	    }
*/
	    for(int i = 0; i < surface->h; i++) {
			SDL_BlitSurface(surface, &origen, invertida, &destino);
			origen.y = origen.y + 1;
			destino.y = destino.y - 1;
	    }
	    return invertida;

	}

	// ===================================================================


} // namespace gui
