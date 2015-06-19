/*
 * OglButton.h
 *
 *  Created on: 10/08/2010
 *      Author: jorge
 */

#ifndef OGLBUTTON_H_
#define OGLBUTTON_H_

#include "persist/Resource.h"

#include "OglSprite.h"

#include "math/BoundingBox.h"

#include "gui/text/OglText.h"
#include "gui/text/FontsManager.h"

namespace persist{
	class CResourceManager;
	class CButtonCache;
}

namespace gui {

	class COglButton : public persist::CResource{

	/**
	 * El gestor de recursos es friend porque es el unico que puede
	 * crear instancias de esta clase
	 */
	friend class persist::CResourceManager;
	friend class persist::CButtonCache;

	public:

		enum EButtonStatus{
			NORMAL,
			PRESSED,
			HIGHLIGHTED,
		};

		virtual bool render();

		//--------------------------------------------------------------------------------------
		// Setters
		//--------------------------------------------------------------------------------------
		void setBounds(float x, float y, float width, float height);
		void setPosition(float x, float y);
		void setText(const std::string& text);
		void setFontType(const std::string& fontName, uint fontSize);

		//--------------------------------------------------------------------------------------
		// Setters
		//--------------------------------------------------------------------------------------

		COglSprite* 	getSprite(EButtonStatus status) { return _buttonStates[status]; }
		COglText* 		getGfxText() 					const { return _gfxText; }
		math::CVector3f fontPosition() 				const { return _fontPosition; }
		const std::string	fontName()		const { return _fontType; }
		const int			fontSize()		const { return _fontSize; }
		//--------------------------------------------------------------------------------------
		// Estados del boton
		//--------------------------------------------------------------------------------------

		void doPressed();
		void doReleased();
		void doHighlighted();

	protected:

		//--------------------------------------------------------------------------------------
		// Constructor / Destructor
		//--------------------------------------------------------------------------------------

		COglButton(const std::string& filename):
			CResource(filename),
			_spritePosition(),
			_fontPosition(),
			_width(0),
			_height(0),
			_strText(""),
			_gfxText(new COglText),
			_fontSize(10),
			_currentState(NORMAL)
		{
		}

		virtual ~COglButton();

		void setSprite(COglSprite* sprite, EButtonStatus status){
			_buttonStates[status] = sprite;
		}

	private:

		typedef std::map<EButtonStatus, COglSprite*>::const_iterator TSpriteMapIterator;

		math::CVector3f							_spritePosition;
		math::CVector3f							_fontPosition;

		float									_width;
		float									_height;

		std::string								_strText;

		COglText*								_gfxText;

		std::string								_fontType;

		int										_fontSize;

		EButtonStatus							_currentState;

		std::map<EButtonStatus, COglSprite*> 	_buttonStates;

	};

}

#endif /* OGLBUTTON_H_ */
