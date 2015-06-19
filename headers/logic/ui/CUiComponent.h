/**
 * GuiComponent.h
 *
 *  Created on: 20/07/2010
 *      Author: jorge
 */

#ifndef GUICOMPONENT_H_
#define GUICOMPONENT_H_

#include "math/BoundingBox.h"
#include "math/Mathlib.h"
#include <list>
#include <string>
#include <iostream>
#include "event/MouseListener.h"

namespace logic {

	class CUiComponent : public event::MouseAdapter {

	public:

		/**
		 * Observador de las propiedades de CUiComponent
		 */
		class UiPropertyListener{
		public:
			virtual ~UiPropertyListener() {}

			virtual void alphaChanged(float newAlpha) = 0;
			virtual void positionChanged(const math::CVector3f& newPos) = 0;
			virtual void dimensionsChanged(float newWidth, float newHeight) = 0;
			virtual void visibilityChanged(bool newVisibility) = 0;
			virtual void idChanged(const std::string& id) = 0;
		};

		/// Constructores y destructor
		CUiComponent();
		CUiComponent(float x, float y, float width, float height);

		virtual ~CUiComponent();


		//--------------------------------------------------------------------
		/// Modificadores
		//--------------------------------------------------------------------

		void setID(const std::string& id);
		void setMouseInside(bool inside);

		virtual void setPosition(float x, float y);
		virtual void setDepth(const float z);
		virtual void setDimensions(float width, float height);
		virtual void setBounds(float x, float y, float width, float height);
		virtual void setAlpha(const float alpha);
		virtual void setVisible(const bool visible);
		virtual void setStyle(const std::string& style);


		//--------------------------------------------------------------------
		/// Accesores
		//--------------------------------------------------------------------

		const std::string 		id() 			const { return _id; }
		const math::CVector3f 	position() 		const { return _position; }
		const float				depth()			const { return _position.z; }
		const float 			width() 		const { return _width; }
		const float 			height() 		const { return _height; }
		const float 			alpha() 		const { return _alpha; }
		const bool 				visible() 		const { return _visible; }
		const bool 				isMouseInside() const { return _mouseInside; }

		math::CBoundingBox bb() const {
			return math::CBoundingBox(
					_position.x,
					_position.y,
					0.0f,
					_position.x+_width,
					_position.y+_height,
					0.0f);
		}

		std::string style() const { return _style; }

		//--------------------------------------------------------------------
		// Metodos de añadido o eliminacion de observadores
		//--------------------------------------------------------------------

		bool addPropertyListener(UiPropertyListener* newOb){
			_listeners.push_back(newOb);
			return true;
		}

		bool removeListener(UiPropertyListener* oldOb){
			_listeners.remove(oldOb);
			return true;
		}

	protected:

		//--------------------------------------------------------------------
		// Transmision de eventos a los observadores
		//--------------------------------------------------------------------

		void emitChangedPosition();
		void emitChangedDimensions();
		void emitChangedAlpha();
		void emitChangedVisibility();
		void emitChangedID();

		//--------------------------------------------------------------------
		// Atributos
		//--------------------------------------------------------------------

		std::string				_id;
		math::CVector3f 		_position;
		float 					_width;
		float					_height;
		float					_alpha;
		bool					_visible;
		bool					_mouseInside;
		std::string				_style;

		std::list<UiPropertyListener*> 	_listeners;

	};

}

#endif /* GUICOMPONENT_H_ */
