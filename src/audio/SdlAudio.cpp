/*
 * SdlAudio.cpp
 *
 *  Created on: 09/03/2011
 *      Author: jorge
 */

#include "audio/SdlAudio.h"

#include <iostream>

namespace audio {

	void CAudioManager::init(){

		if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers))
			printf("Unable to open audio!\n");

		Mix_QuerySpec(&audio_rate, &audio_format, &audio_channels);

		// get and print the audio format in use
		int numtimesopened, frequency, channels;
		Uint16 format;
		numtimesopened=Mix_QuerySpec(&frequency, &format, &channels);
		if(!numtimesopened) {
		    printf("Mix_QuerySpec: %s\n",Mix_GetError());
		}
		else {
		    const char *format_str="Unknown";
		    switch(format) {
		        case AUDIO_U8: format_str="U8"; break;
		        case AUDIO_S8: format_str="S8"; break;
		        case AUDIO_U16LSB: format_str="U16LSB"; break;
		        case AUDIO_S16LSB: format_str="S16LSB"; break;
		        case AUDIO_U16MSB: format_str="U16MSB"; break;
		        case AUDIO_S16MSB: format_str="S16MSB"; break;
		    }
		    printf("opened=%d times\nfrequency=%dHz\nformat=%s\nchannels=%d\n",
		            numtimesopened, frequency, format_str, channels);
		}
	}

	void CAudioManager::end(){
		/* Paramos sonidos y musica y liberamos antes de cerrar contextos */
		stop();

		{
			std::vector<Mix_Music*>::iterator it(sounds.begin()), end(sounds.end());
			for(;it!=end; ++it){
				Mix_FreeMusic(*it);
				(*it) = 0;
			}
			sounds.clear();
		}

		{
			std::vector<Mix_Chunk*>::iterator it(effects.begin()), end(effects.end());
			for(;it!=end; ++it){
				Mix_FreeChunk(*it);
				(*it) = 0;
			}
			effects.clear();
		}

		{
			std::map<uint, Mix_Chunk*>::iterator it, end;
			end = dialogues.end();
			for(it=dialogues.begin(); it!=end; ++it){
				Mix_Chunk* chunk = it->second;

				Mix_FreeChunk(chunk);
				dialogues.erase(it);
			}

			dialogues.clear();
		}

		Mix_CloseAudio ( );
	}

	void CAudioManager::loadSong(const char* audio_path){
		Mix_Music* newAudio = Mix_LoadMUS(audio_path);

		if(newAudio)
			sounds.push_back(newAudio);
		else
			std::cerr<<"[CSdlAudio::loadSong][ERROR] No se ha podido cargar "<<audio_path<<"\n";
	}

	void CAudioManager::loadEffect(const char* effect_path){
		Mix_Chunk* newEffect = Mix_LoadWAV(effect_path);

		if(newEffect)
			effects.push_back(newEffect);
		else
			std::cerr<<"[CSdlAudio::loadEffect][ERROR] No se ha podido cargar "<<effect_path<<"\n";
	}

	void CAudioManager::loadDialogue(uint id, const char* dialogue_path){
		Mix_Chunk* newDialogue = Mix_LoadWAV(dialogue_path);
		Mix_VolumeChunk(newDialogue, MIX_MAX_VOLUME);
		if(newDialogue)
			dialogues[id] = newDialogue;
		else
			std::cerr<<"[CSdlAudio::loadDialogue][ERROR] No se ha podido cargar "<<dialogue_path<<"\n";
	}

	void CAudioManager::playSong(int audio_num, bool loop){
		int result = 0;
		if(loop){
			result = Mix_PlayMusic(sounds[audio_num], -1);
		}
		else{
			result = Mix_PlayMusic(sounds[audio_num], 0);
		}

		if(result == -1)
			std::cerr<<"Mix_PlayMusic: "<<Mix_GetError()<<"\n";
	}

	void CAudioManager::playEffect(int effect_num, int channel){
		Mix_PlayChannel(channel,effects[effect_num], 0);
	}


	void CAudioManager::playDialogue(int dialogueID){
		Mix_PlayChannel(1, dialogues[dialogueID], 0);
	}

	void CAudioManager::stop(){
		Mix_HaltMusic();
		Mix_HaltChannel(-1);
	}

	void CAudioManager::pause(){
		if(Mix_PausedMusic())
			resume();
		else{
			Mix_Pause(-1);		// Pausados todos los canales
			Mix_PauseMusic();	// Pausada la musica
		}
	}

	void CAudioManager::resume(){
		Mix_ResumeMusic();
		Mix_Resume(-1);
	}

}
