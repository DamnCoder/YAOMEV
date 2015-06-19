/*
 * CModelMD3.h
 *
 *  Created on: 24/04/2010
 *      Author: jorge
 */

#ifndef CMODELMD3_H_
#define CMODELMD3_H_

#include "gui/graphicserver/md3/Model.h"

#include "persist/Resource.h"

namespace persist{
	class CResourceManager;
	class CAnimatedGfxCache;
}

namespace gui {

	typedef std::vector<std::string> TSkinNameList;

	class CAnimatedModelMd3 : public persist::CResource{

	friend class persist::CResourceManager;
	friend class persist::CAnimatedGfxCache;

	public:

		enum EModelType{
			MODEL_LOWER,
			MODEL_UPPER,
			MODEL_HEAD
		};

		void render(
				const math::CPositionf& position,
				const float orientation,
				const float scale);

		bool castShadow(const math::CPositionf& position, const float orientation);

		//----------------------------------------------------------------------------------
		// Modificadores
		//----------------------------------------------------------------------------------
		void skin(const std::string& skin);
		void animation(
				const tAnimationState& lowerAnim,
				const tAnimationState& upperAnim,
				const tAnimationState& headAnim);

		//----------------------------------------------------------------------------------
		// Accesores
		//----------------------------------------------------------------------------------
		const tModel* 	get(int whichPart) 	const;
		const int 		tris() 				const;
		tAnimationState legsAnimation(const std::string& animation);
		tAnimationState torsoAnimation(const std::string& animation);
		tAnimationState headAnimation(const std::string& animation);
		TSkinNameList	skinNames() const { return _skinNames; }

		std::vector<tBoundingVolumes> legsSpheres() const { return _lower->volumes; }
		std::vector<tBoundingVolumes> upperSpheres() const { return _upper->volumes; }
		std::vector<tBoundingVolumes> headSpheres() const { return _head->volumes; }

	protected:
		CAnimatedModelMd3(
				const std::string& filename,
				tModel* head,
				tModel* upper,
				tModel* lower);
		~CAnimatedModelMd3();

		void destroy(tModel *pModel);

	private:

		void getSkinNames();

		tModel* _lower;
		tModel* _upper;
		tModel* _head;

		tAnimationState _lowerAnimState;
		tAnimationState _upperAnimState;
		tAnimationState _headAnimState;

		SkinMap			_lowerSkins;
		SkinMap			_upperSkins;
		SkinMap			_headSkins;

		TSkinNameList _skinNames;

	};

}

#endif /* CMODELMD3_H_ */
