/*
 * AnimationLoader.h
 *
 *  Created on: 29/05/2011
 *      Author: jorge
 */

#ifndef ANIMATIONLOADER_H_
#define ANIMATIONLOADER_H_

#include "gui/graphicserver/md3/MD3structs.h"
#include "gui/graphicserver/md3/Model.h"

namespace persist {

	class CAnimationLoader {
	public:
		CAnimationLoader();
		~CAnimationLoader();

		bool importAnimations(const std::string& modelPath);

		std::vector<gui::tAnimation> lowerAnimations()	const { return _lowerAnims; }
		std::vector<gui::tAnimation> upperAnimations()	const { return _upperAnims; }
		std::vector<gui::tAnimation> headAnimations()	const { return _headAnims; }

		std::vector<std::string> lowerAnimationsNames()	const { return _lowerAnimNames; }
		std::vector<std::string> upperAnimationsNames()	const { return _upperAnimNames; }
		std::vector<std::string> headAnimationsNames()	const { return _headAnimNames; }

	private:
		std::vector<gui::tAnimation> _lowerAnims;
		std::vector<gui::tAnimation> _upperAnims;
		std::vector<gui::tAnimation> _headAnims;

		//TODO He de guardar las animaciones por tipo, ahora se acumulan las de cada personaje
		std::vector<std::string> _lowerAnimNames;
		std::vector<std::string> _upperAnimNames;
		std::vector<std::string> _headAnimNames;

	};

}

#endif /* ANIMATIONLOADER_H_ */
