/*
The MIT License (MIT)
Copyright (c) 2016 Lorhan Sohaky
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "process_creator.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>

#if _WIN32 || _WIN64

#include <windows.h>
int call_prog( char *prog, char *argv[], int argc ) {
	printf( "windows\n" );
	PROCESS_INFORMATION ProcessInfo; // This is what we get as an [out] parameter
	STARTUPINFO StartupInfo;		 // This is an [in] parameter
	ZeroMemory( &StartupInfo, sizeof( StartupInfo ) );
	StartupInfo.cb = sizeof StartupInfo; // Only compulsory field
	DWORD exit_code;
	_string str;
	str.value = (char *)malloc( 100 * sizeof( char ) );
	str.size  = 100;
	if( str == NULL ) {
		return -1;
	}
	copy_string( str, prog );
	for( int i = 0; i < argc; i++ ) {
		append_string( str, " " );
		append_string( str, argv[i] );
	}
	printf( "%s\n", str );
	printf( "%s\n", prog );
	if( CreateProcess( prog, str, NULL, NULL, FALSE, 0, NULL, NULL, &StartupInfo, &ProcessInfo ) ) {
		WaitForSingleObject( ProcessInfo.hProcess, INFINITE );
		GetExitCodeProcess( ProcessInfo.hProcess, &exit_code );
		printf( "returns: %d\n", exit_code );
		CloseHandle( ProcessInfo.hThread );
		CloseHandle( ProcessInfo.hProcess );
	} else {
		printf( "The process could not be started..." );
	}
	return exit_code;
}
#elif __linux__
// define it for a Linux machine
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int call_progs( char *gource_args[], char *ffmpeg_args[] ) {
	pid_t gource, ffmpeg;

	int pipefd_between_processes[2], pipefd_between_ffmpeg_and_parent[2];

	if( pipe( pipefd_between_processes ) < 0 ) {
		printf( "Erro pipe A\n" );
	}

	if( pipe( pipefd_between_ffmpeg_and_parent ) < 0 ) {
		printf( "Erro pipe B\n" );
	}

	gource = fork();
	if( gource == 0 ) {
		close( pipefd_between_processes[0] );
		close( pipefd_between_ffmpeg_and_parent[1] );
		close( pipefd_between_ffmpeg_and_parent[0] );

		dup2( pipefd_between_processes[1], 1 );

		execvp( "gource", gource_args );
	} else {
		ffmpeg = fork();

		if( ffmpeg == 0 ) {
			close( pipefd_between_processes[1] );
			close( pipefd_between_ffmpeg_and_parent[0] );

			dup2( pipefd_between_processes[0], 0 );
			dup2( 1, pipefd_between_ffmpeg_and_parent[1] );
			execvp( "ffmpeg", ffmpeg_args );

		} else {
			close( pipefd_between_processes[0] );
			close( pipefd_between_processes[1] );
			close( pipefd_between_ffmpeg_and_parent[1] );

			dup2( pipefd_between_ffmpeg_and_parent[0], 1 );

			waitpid( gource, NULL, 0 );
			waitpid( ffmpeg, NULL, 0 );
		}
	}
	return 0;
}

#endif
