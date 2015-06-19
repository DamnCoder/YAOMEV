/*
 * SpriteOGL.h
 *
 *  Created on: 13/01/2010
 *      Author: jorge
 */

#ifndef OGLSPRITE_H_
#define OGLSPRITE_H_


#include "persist/Resource.h"

#include "math/BoundingBox.h"

#include "gui/OglGraphics.h"

namespace persist{
	class CResourceManager;
	class CSpriteCache;
}

namespace gui {

	class COglSprite : public persist::CResource{

	/**
	 * El gestor de recursos es friend porque es el unico que puede
	 * crear instancias de esta clase
	 */
	friend class persist::CResourceManager;
	friend class persist::CSpriteCache;

	public:

		//--------------------------------------------------------------------------------------
		// Getters
		//--------------------------------------------------------------------------------------

		float getX() const{
			return _position.x;
		}

		float getY() const {
			return _position.y;
		}

		float getWidth() const {
			return _width;
		}

		float getHeight() const {
			return _height;
		}

		TRGBAColor getColor() const {
			return _color;
		}

		uint getTextureID() const {
			return _textureID;
		}
		//--------------------------------------------------------------------------------------
		// Setters
		//--------------------------------------------------------------------------------------
		void setBounds(float x, float y, float width, float height);

		void setPosition(float x, float y){
			_position.x = x;
			_position.y = y;
		}

		void setWidth(float width){
			_width = width;
		}

		void setHeight(float height){
			_height = height;
		}

		void setAlpha(float alpha){
			if(alpha>1.0f)
				_color.a = 1.0f;
			else if(alpha<0.0f)
				_color.a = 0.0f;
			else
				_color.a = alpha;
		}

		void setColor(TRGBAColor color){
			_color = color;
		}

		//--------------------------------------------------------------------------------------
		// Renderizado
		//--------------------------------------------------------------------------------------
		bool render();

	protected:

		//--------------------------------------------------------------------------------------
		// Constructor / Destructor
		//--------------------------------------------------------------------------------------

		COglSprite(const std::string& filename):
			CResource(filename),
			_position(),
			_width(0), _height(0),
			_alpha(1.0f),
			_color(1.0f, 1.0f, 1.0f, 1.0f),
			_bbox()
		{
		}

		virtual ~COglSprite()
		{
		}

		/**
		 * Asignamos el ID de la textura al sprite
		 * @param textureID
		 */
		void setTextureId(const uint textureID){
			_textureID = textureID;
		}

	private:

		void drawBoundingBox();

		//--------------------------------------------------------------------------------------
		// ATRIBUTOS
		//--------------------------------------------------------------------------------------

		uint 				_textureID;	// ID de la textura del sprite

		math::CPositionf	_position;	// Posicion 3D del sprite

		float 				_width;		// Ancho del sprite
		float 				_height;	// Alto del sprite
		float 				_alpha;		// Valor de transparencia

		TRGBAColor			_color;

		math::CBoundingBox	_bbox;
	};

}

#endif /* OGLSPRITE_H_ */
