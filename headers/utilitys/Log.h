/*
 * Log.h
 *
 *  Created on: 06/12/2010
 *      Author: jorge
 */

#ifndef LOG_H_
#define LOG_H_

#include "Singleton.h"

#include <cstdio>
#include <cstdlib>
#include <cstdarg>

namespace utils {

	/**
	 * Clase para escribir un log.
	 *
	 * Basado en las rutinas basicas
	 * de manejo de errores de Jeff Molofee
	 */
	class CLog : public CSingleton<CLog> {

	friend class CSingleton<CLog>;
	public:
		/**
		 * Inicializa el log de errores
		 *
		 * @return 	cierto si se ha iniciado correctamente y falso
		 * 			en caso contrario
		 */
		bool init(const char* path){

			if(!(_log = fopen(path, "w"))){		// If We Can't Open LOG_FILE For Writing

				perror("Can't init Logfile!\n" );		// Report With perror() (Standard + Explains Cause Of The Error)
				return false;							// And Exit, This Is Critical, We Want Logging
			}

			log("-- Log Init...\n");					// We Print The Name Of The App In The Log

			return true;								// Otherwhise Return TRUE (Everything Went OK)

		}

		/**
		 * Cierra el log de errores
		 * @return
		 */
		bool end(){
			log("-- Closing Log...\n");				// Print The End Mark

			if(_log)								// If The File Is Open
				fclose(_log);						// Close It

			return true;							// And Return, Quite Plain Huh? :)

		}

		/**
		 * Añade una linea al log.
		 * @param szFormat
		 * @return
		 */
		bool log(const char* szFormat, ...){
			va_list arg;								// We're Using The Same As The printf() Family, A va_list
														// To Substitute The Tokens Like %s With Their Value In The Output

			va_start(arg,szFormat);						// We Start The List

			if(_log){								// If The Log Is Open
				vfprintf(_log, szFormat, arg);		// We Use vprintf To Perform Substituctions
				fflush(_log);						// And Ensure The Line Is Written, The Log Must Be Quick
			}

			va_end(arg);								// We End The List

			return true;								// And Return A Ok
		}

	protected:

		CLog():_log(0){}

		virtual ~CLog(){
		}

	private:

		FILE* 	_log;
	};


}

#endif /* LOG_H_ */
