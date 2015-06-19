/*
 * AnimationLoader.cpp
 *
 *  Created on: 29/05/2011
 *      Author: jorge
 */

#include "persist/md3/AnimationLoader.h"

#include "utilitys/utils.h"

namespace persist {

	CAnimationLoader::CAnimationLoader() {
	}

	CAnimationLoader::~CAnimationLoader() {
	}

	bool CAnimationLoader::importAnimations(const std::string& modelPath){
		gui::tAnimation animations[gui::MAX_ANIMATIONS];

		std::string configFilePath = modelPath + (std::string)"animation.cfg";

		std::ifstream fin(configFilePath.c_str());

		if( fin.fail() ){
			return false;
		}

		std::string strWord = "";
		std::string strLine = "";
		int currentAnim = 0;
		//int torsoOffset = 0;

		while( fin >> strWord){
			if(!isdigit( strWord[0] )){
				getline(fin, strLine);
				continue;
			}

			int startFrame = atoi(strWord.c_str());
			int numOfFrames = 0, loopingFrames = 0, framesPerSecond = 0;

			fin >> numOfFrames >> loopingFrames >> framesPerSecond;

			animations[currentAnim].startFrame		= startFrame;
			animations[currentAnim].endFrame		= startFrame + numOfFrames;
			animations[currentAnim].loopingFrames	= loopingFrames;
			animations[currentAnim].fps = framesPerSecond;

			fin >> strLine >> strLine;

			strcpy(animations[currentAnim].name, strLine.c_str());

			//std::cout<<"[CAnimationLoader::importAnimations] nombre: "<<animations[currentAnim].name<<"\n";

			if(isInString(strLine, "BOTH")){
				_lowerAnims.push_back(animations[currentAnim]);
				_upperAnims.push_back(animations[currentAnim]);

				_lowerAnimNames.push_back(animations[currentAnim].name);
				_upperAnimNames.push_back(animations[currentAnim].name);
			}
			else if(isInString(strLine, "TORSO")){
				_upperAnims.push_back(animations[currentAnim]);
				_upperAnimNames.push_back(animations[currentAnim].name);
			}
			else if(isInString(strLine, "LEGS")){
				_lowerAnims.push_back(animations[currentAnim]);
				_lowerAnimNames.push_back(animations[currentAnim].name);
			}
			else if(isInString(strLine, "HEAD")){
				_headAnims.push_back(animations[currentAnim]);
				_headAnimNames.push_back(animations[currentAnim].name);
			}

			currentAnim++;
		}

		if((_lowerAnims.size() == 0) && (_upperAnims.size() == 0) && (_headAnims.size() == 0))
			return false;

		return true;
	}

}
