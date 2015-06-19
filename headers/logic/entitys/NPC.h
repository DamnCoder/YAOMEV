/*
 * NPC.h
 *
 *  Created on: 12/04/2010
 *      Author: jorge
 */

#ifndef NPC_H_
#define NPC_H_

#include "Avatar.h"

namespace logic {

	class CNPC: public CAvatar  {

	public:

		CNPC(	const std::string& id,
				const std::string& name,
				float x, float y, float z,
				float orientation,
				bool visible):
			CAvatar(id, name, x, y, z, orientation, visible)
		{}

		~CNPC();

		void actualize(unsigned int diff);
	};

}

#endif /* NPC_H_ */
