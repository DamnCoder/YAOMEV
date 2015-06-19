/*
 * ComponentEvent.h
 *
 *  Created on: 11/02/2011
 *      Author: jorge
 */

#ifndef COMPONENTEVENT_H_
#define COMPONENTEVENT_H_

#include "Event.h"

//#include "logic/ui/GuiComponent.h"

namespace logic{
	class CUiComponent;
}

namespace event {

	class ComponentEvent : public Event{
	public:

		ComponentEvent(logic::CUiComponent* source):
			_source(source)
		{}

		virtual ~ComponentEvent(){}

		const logic::CUiComponent* getSource() const { return _source; }

	private:
		logic::CUiComponent* _source;

	};

}

#endif /* COMPONENTEVENT_H_ */
