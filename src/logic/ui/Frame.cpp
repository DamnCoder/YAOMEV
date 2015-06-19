/*
 * Frame.cpp
 *
 *  Created on: 20/07/2010
 *      Author: jorge
 */

#include "logic/ui/Frame.h"

#include "utilitys/utils.h"

#include "gui/WindowManager.h"

namespace logic {

	CFrame::CFrame(): CUiComponent()
	{
		_width = gui::CWindowManager::instance().width();
		_height = gui::CWindowManager::instance().height();
		_id = "transparent";
	}

	CFrame::CFrame(float x, float y, float width, float height):
		CUiComponent(x, y, width, height)
	{
		_id = "transparent";
	}

	CFrame::~CFrame() {
		deleteList(_components);
	}

	void CFrame::setAlpha(const float alpha) {
		TComponentIterator it(_components.begin()), end(_components.end());
		for( ;it!=end; ++it){
			(*it)->setAlpha(alpha);
		}
		CUiComponent::setAlpha(alpha);
	}
	void CFrame::setVisible(const bool visible){
		TComponentIterator it(_components.begin()), end(_components.end());
		for( ;it!=end; ++it){
			(*it)->setVisible(visible);
		}
		_visible = visible;
		emitChangedVisibility();
	}

	void CFrame::setDepth(const float z) {
		CUiComponent::setDepth(z);

		// TODO Hacer diferencia entre el depth de los componentes y el del frame y añadir esa diferencia

		_itbut = _buttons.begin(); _endbut = _buttons.end();
		for(; _itbut!=_endbut; ++_itbut)
			(*_itbut)->setDepth(this->depth()+1);

		_itlab = _labels.begin(); _endlab = _labels.end();
		for(; _itlab!=_endlab; ++_itlab)
			(*_itlab)->setDepth(this->depth()+1);

		_ittb = _textBoxes.begin(); _endtb = _textBoxes.end();
		for(; _ittb!=_endtb; ++_ittb)
			(*_ittb)->setDepth(this->depth()+1);

	}

	bool CFrame::add(CUiComponent* component){
		if(!component)
			return false;

		component->setDepth(this->depth()+1);
		_components.push_back(component);
		_mouseListeners.push_back(component);

		return true;
	}

	bool CFrame::add(CButton* button){
		if(!add((CUiComponent*)button))
			return false;

		_buttons.push_back(button);

		return true;
	}

	bool CFrame::add(CLabel* label){
		if(!add((CUiComponent*)label))
			return false;

		_labels.push_back(label);

		return true;
	}

	bool CFrame::add(CTextBox* textBox){
		if(!add((CUiComponent*) textBox))
			return false;

		_textBoxes.push_back(textBox);

		return true;
	}

	void CFrame::remove(CUiComponent* component){
		if(component){
			_components.remove(component);
			_mouseListeners.remove(component);

			safeDelete(component);
		}
	}

	void CFrame::remove(CButton* button){
		_buttons.remove(button);
		remove((CUiComponent*)button);
	}

	void CFrame::remove(CTextBox* textBox){
		_textBoxes.remove(textBox);
		remove((CUiComponent*)textBox);
	}

	void CFrame::remove(CLabel* label){
		_labels.remove(label);
		remove((CUiComponent*)label);
	}

	void CFrame::mousePressed(event::MouseInputEvent e){
		TComponentIterator it(_components.begin()), end(_components.end());

		for(;it!=end;++it){

			if((*it)->visible()){
				math::CBoundingBox bb = (*it)->bb();
				// Hay que convertir X e Y, porque OGL y SDL toman coordenadas distintas de pantalla
				float scrHeight = gui::CWindowManager::instance().height();

				if( bb.isInside2dBox(math::CVector3f(e.getX(), scrHeight - e.getY()))){
					emitMouseEvent(event::MouseEvent(
									*it,
									e.getX(), e.getY(),
									e.getButton(),
									event::MouseEvent::MOUSE_PRESSED));
				}

			}
		}
	}

	void CFrame::mouseReleased(event::MouseInputEvent e){
		TComponentIterator it(_components.begin()), end(_components.end());

		for(;it!=end;++it){
			if((*it)->visible()){
				math::CBoundingBox bb = (*it)->bb();
				// Hay que convertir X e Y, porque OGL y SDL toman coordenadas distintas de pantalla
				float scrHeight = gui::CWindowManager::instance().height();

				if( bb.isInside2dBox(math::CVector3f(e.getX(), scrHeight - e.getY())))
					emitMouseEvent(event::MouseEvent(
										*it,
										e.getX(), e.getY(),
										e.getButton(),
										event::MouseEvent::MOUSE_RELEASED));

			}
		}
	}

	void CFrame::mouseMotion(event::MouseInputEvent e){
		TComponentIterator it(_components.begin()), end(_components.end());

		for(;it!=end;++it){
			if((*it)->visible()){
				math::CBoundingBox bb = (*it)->bb();
				// Hay que convertir X e Y, porque OGL y SDL toman coordenadas distintas de pantalla
				float scrHeight = gui::CWindowManager::instance().height();

				if( bb.isInside2dBox(math::CVector3f(e.getX(), scrHeight - e.getY()))){
					emitMouseEvent(event::MouseEvent(
										*it,
										e.getX(), e.getY(),
										e.getButton(),
										event::MouseEvent::MOUSE_ENTERED));
					(*it)->setMouseInside(true);
				}
				else if((*it)->isMouseInside()){	// Si el puntero no esta dentro, pero antes lo estaba, desactivamos el componente
					emitMouseEvent(event::MouseEvent(
										*it,
										e.getX(), e.getY(),
										e.getButton(),
										event::MouseEvent::MOUSE_EXITED));
					(*it)->setMouseInside(false);
				}
			}
		}
	}

	bool CFrame::addListener(event::MouseInputListener* e){
		_mouseInputListeners.push_back(e);
		return true;
	}

	bool CFrame::addListener(event::MouseListener* e){
		_mouseListeners.push_back(e);
		return true;
	}

	bool CFrame::removeListener(event::MouseInputListener* e){
		_mouseInputListeners.remove(e);
		return true;
	}

	bool CFrame::removeListener(event::MouseListener* e){
		_mouseListeners.remove(e);
		return true;
	}


	void CFrame::emitMouseEvent(event::MouseEvent mouseEvent){
		TMLterator
			it(_mouseListeners.begin()),
			end(_mouseListeners.end());

		for(;it!=end; ++it){
			switch(mouseEvent.getEvent()){

			case event::MouseEvent::MOUSE_PRESSED:
				(*it)->mousePressed(mouseEvent);
				break;

			case event::MouseEvent::MOUSE_RELEASED:
				(*it)->mouseReleased(mouseEvent);
				break;

			case event::MouseEvent::MOUSE_ENTERED:
				(*it)->mouseEntered(mouseEvent);
				break;

			case event::MouseEvent::MOUSE_EXITED:
				(*it)->mouseExited(mouseEvent);
				break;

			default:
				break;

			}
		}
	}

}
