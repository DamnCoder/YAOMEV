/*
 * COctreeNode.h
 *
 *  Created on: 12/06/2011
 *      Author: jorge
 */

#ifndef COCTREENODE_H_
#define COCTREENODE_H_

#include "gui/scene/AnimatedEntityNode.h"
#include "gui/scene/StaticEntityNode.h"

namespace gui {

	enum eOctreeNodes {
		TOP_LEFT_FRONT,			// 0
		TOP_LEFT_BACK,			// 1
		TOP_RIGHT_BACK,			// etc...
		TOP_RIGHT_FRONT,
		BOTTOM_LEFT_FRONT,
		BOTTOM_LEFT_BACK,
		BOTTOM_RIGHT_BACK,
		BOTTOM_RIGHT_FRONT
	};

	///--------------------------------------------------------------------------------

	class COctreeNode {
	public:
		COctreeNode():
			_width(0),
			_tris(0),
			_depth(0){}
		virtual ~COctreeNode(){}

	protected:
		math::CVector3f	_center;
		float			_width;
		int				_tris;
		int				_depth;
	};

	///--------------------------------------------------------------------------------

	class COctreeLeaf : public COctreeNode {
	public:
		COctreeLeaf(){}
		virtual ~COctreeLeaf(){}

	protected:
	};

	///--------------------------------------------------------------------------------

	class COctree : public COctreeNode {
	public:
		COctree(int maxTris=1000, int maxDepth=4):
			_maxTris(maxTris),
			_maxDepth(maxDepth){}
		virtual ~COctree(){}

		void addModel(CStaticEntityNode* node);

	private:
		// Redefiniciones
		typedef std::vector<CAnimatedEntityNode*> TAnimList;
		typedef std::vector<CStaticEntityNode*> TStatList;

		void createChilds();
		void addChild(int id, COctreeNode* child);

		void calculateCenter();
		void calculateWidthOfCube();
		void calculateTris();

		int		_maxTris;
		int		_maxDepth;

		COctreeNode*	_childs[8];

		TAnimList	_animatedModels;
		TStatList	_staticModels;

		TAnimList::iterator animIt, animEnd;
		TStatList::iterator statIt, statEnd;
	};

}

#endif /* COCTREENODE_H_ */
