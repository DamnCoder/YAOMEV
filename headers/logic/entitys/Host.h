/*
 * Host.h
 *
 *  Created on: 12/11/2010
 *      Author: jorge
 */

#ifndef HOST_H_
#define HOST_H_

#include "Avatar.h"

namespace logic {

class CQuizShowHost: public CAvatar {

public:

	CQuizShowHost(
			const std::string& id,
			const std::string& name,
			float x, float y, float z,
			float orientation,
			bool visible,
			float scale = 1):
		CAvatar(id, name, x, y, z, orientation, visible, scale)
	{}

	~CQuizShowHost();
};

}

#endif /* HOST_H_ */
