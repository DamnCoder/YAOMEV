/*
 * SdlAudio.h
 *
 *  Created on: 09/03/2011
 *      Author: jorge
 */

#ifndef SDLAUDIO_H_
#define SDLAUDIO_H_

#include "utilitys/Singleton.h"

#include <vector>
#include <map>

#include <SDL/SDL_mixer.h>

namespace audio {

	class CAudioManager : public CSingleton<CAudioManager> {

	friend class CSingleton<CAudioManager>;

	public:

		void init();

		void end();

		// LOADS
		void loadSong(const char* audio_path);
		void loadEffect(const char* effect_path);
		void loadDialogue(uint id, const char* dialogue_path);

		// PLAYS
		void playSong(int audio_num, bool loop);
		void playEffect(int effect_num, int channel);
		void playDialogue(int dialogueID);

		// CONTROLS
		void stop();
		void pause();
		void resume();

		// VOLUME
		void fadeInChannel(int channel){}
		void fadeOutChannel(int channel, int millisecs)
		{
			Mix_FadeOutChannel(channel, millisecs);
		}

		/**
		 * Establece el volumen de las cancion
		 * que este sonando
		 * @param vol
		 */
		void setSongVolume(int vol){
			Mix_VolumeMusic(checkVolume(vol));
		}

		/**
		 * Establece el volumen del canal especificado.
		 * Si pasas -1 como canal, estableces el
		 * volumen de todos los canales.
		 * @param vol
		 * @param channel
		 */
		void setChannelVolume(int vol, int channel){
			Mix_Volume(channel, checkVolume(vol));
		}

		/**
		 * Establece el volumen de todos los canales
		 * @param vol
		 */
		void setChannelsVolume(int vol){
			Mix_Volume(-1, checkVolume(vol));
		}

		/**
		 * Devuelve el volumen del canal especificado.
		 *
		 * @param channel
		 * @return
		 */
		int getChannelVolume(int channel){
			return Mix_Volume(channel, -1);
		}

		// RELEASE
		void releaseEffects(){}
		void releaseSong(){}

	protected:

		/**
		 * Comprueba que el volumen pasado
		 * este dentro de los parametros permitidos
		 * en SDL_mixer.
		 *
		 * El volumen maximo viene especificado
		 * por MIX_MAX_VOLUME
		 * y el minimo por 0
		 *
		 * @param vol
		 * @return
		 */
		int checkVolume(int vol){
			if(vol > MIX_MAX_VOLUME)
				return MIX_MAX_VOLUME;
			else if(vol<0)
				return 0;
			return vol;
		}

		CAudioManager():
			audio_rate(22050),
			audio_format(AUDIO_S16SYS),
			audio_channels(2),
			audio_buffers(4096)
		{
		}


		virtual ~CAudioManager(){ }

	private:

		int 	audio_rate;
		Uint16 	audio_format;
		int		audio_channels;
		int		audio_buffers;

		std::vector<Mix_Music*> sounds;
		std::vector<Mix_Chunk*> effects;
		std::map<uint, Mix_Chunk*> dialogues;
	};

}

#endif /* SDLAUDIO_H_ */
