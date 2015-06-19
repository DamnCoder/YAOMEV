#include "logic/ui/CUiComponent.h"

namespace logic {

	CUiComponent::CUiComponent():
		_id(""),
		_position(0, 0),
		_width(0),
		_height(0),
		_alpha(1),
		_visible(true),
		_mouseInside(false),
		_style(""){}

	CUiComponent::CUiComponent(float x, float y, float width, float height):
		_id(""),
		_position(x, y),
		_width(width),
		_height(height),
		_alpha(1),
		_visible(true),
		_mouseInside(false),
		_style(""){}

	CUiComponent::~CUiComponent() {
		//std::cout<<"[delete:CUiComponent] Quedan "<<_listeners.size()<<" listeners de componente UI\n";
		_listeners.clear();
	}

	//--------------------------------------------------------------------
	// Modificadores
	//--------------------------------------------------------------------

	void CUiComponent::setID(const std::string& id){
		_id = id;
		emitChangedID();
	}

	void CUiComponent::setPosition(float x, float y) {
		_position.x = x;
		_position.y = y;
		emitChangedPosition();
	}

	void CUiComponent::setDepth(const float z) {
		_position.z = z;
		emitChangedPosition();
	}

	void CUiComponent::setDimensions(float width, float height){
		_width = width;
		_height = height;
		emitChangedDimensions();
	}
	void CUiComponent::setBounds(float x, float y, float width, float height){
		setPosition(x, y);
		setDimensions(width, height);
	}

	void CUiComponent::setAlpha(const float alpha){
		if(alpha>1)
			_alpha = 1.0f;
		else if(alpha<0)
			_alpha = 0.0f;
		else
			_alpha = alpha;

		emitChangedAlpha();
	}

	void CUiComponent::setVisible(const bool visible){
		_visible = visible;
		emitChangedVisibility();
	}

	void CUiComponent::setMouseInside(bool inside){ _mouseInside = inside; }
	void CUiComponent::setStyle(const std::string& style){ _style = style; }

	//--------------------------------------------------------------------
	// Metodos protegidos
	//--------------------------------------------------------------------
	void CUiComponent::emitChangedPosition(){
		std::list<UiPropertyListener*>::const_iterator it, end;
		end = _listeners.end();
		for(it=_listeners.begin(); it!=end; ++it)
			(*it)->positionChanged(_position);

	}

	void CUiComponent::emitChangedDimensions(){
		std::list<UiPropertyListener*>::const_iterator it, end;
		end = _listeners.end();
		for(it=_listeners.begin(); it!=end; ++it)
			(*it)->dimensionsChanged(_width, _height);
	}

	void CUiComponent::emitChangedAlpha(){
		std::list<UiPropertyListener*>::const_iterator it, end;
		end = _listeners.end();
		for(it=_listeners.begin(); it!=end; ++it)
			(*it)->alphaChanged(_alpha);
	}

	void CUiComponent::emitChangedVisibility(){
		std::list<UiPropertyListener*>::const_iterator it, end;
		end = _listeners.end();
		for(it=_listeners.begin(); it!=end; ++it)
			(*it)->visibilityChanged(_visible);
	}

	void CUiComponent::emitChangedID(){
		std::list<UiPropertyListener*>::const_iterator it, end;
		end = _listeners.end();
		for(it=_listeners.begin(); it!=end; ++it)
			(*it)->idChanged(_id);
	}
}
