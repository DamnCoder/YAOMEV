/*
 * MultimediaFurniture.cpp
 *
 *  Created on: 01/06/2011
 *      Author: jorge
 */

#include "logic/entitys/MultimediaFurniture.h"

#include <iostream>

namespace logic {

	CMultimediaFurniture::CMultimediaFurniture(
			const std::string& id,
			float x, float y, float z,
			float orientation,
			bool visible, float scale):
				CEntity(id, x, y, z, orientation, visible, scale),
				_interval(1000),
				_elapsed(0),
				_skinIndex(0)
	{
	}

	CMultimediaFurniture::~CMultimediaFurniture() {
	}

	void CMultimediaFurniture::actualize(float dt) {
		_elapsed += dt;

		if(_elapsed >= _interval){
			_elapsed = 0.0f;
			++_skinIndex;

			if(_skinIndex >= (int)_skinList.size())
				_skinIndex = 0;

			setSkin(_skinList[_skinIndex]);

			//std::cout<<"[CMultimediaFurniture::actualize] Indice: "<<_skinIndex<<" Skin: "<<_skinList[_skinIndex]<<"\n";
		}


	}

	//--------------------------------------------------------------------------------------

}
