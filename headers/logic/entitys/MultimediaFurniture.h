/*
 * MultimediaFurniture.h
 *
 *  Created on: 01/06/2011
 *      Author: jorge
 */

#ifndef MULTIMEDIAFURNITURE_H_
#define MULTIMEDIAFURNITURE_H_

#include "Entity.h"

#include <vector>

namespace logic {

	class CMultimediaFurniture : public CEntity{
	public:

		CMultimediaFurniture():CEntity(){}
		CMultimediaFurniture(
				const std::string& id,
				float x, float y, float z,
				float orientation,
				bool visible, float scale = 1);
		virtual ~CMultimediaFurniture();

		virtual void actualize(float dt);

		//--------------------------------------------------------------------------------------
		// Modificadores
		//--------------------------------------------------------------------------------------
		void setSkinList(const std::vector<std::string>& skinList) { _skinList = skinList; }
		void setInterval(float millisecs) { _interval = millisecs; }

		//--------------------------------------------------------------------------------------
		// Accesores
		//--------------------------------------------------------------------------------------
		const float			interval() 	const { return _interval; }

	private:
		void emitChangedSkin();

		float						_interval;
		float						_elapsed;

		int							_skinIndex;
		std::vector<std::string>	_skinList;
	};

}

#endif /* MULTIMEDIAFURNITURE_H_ */
