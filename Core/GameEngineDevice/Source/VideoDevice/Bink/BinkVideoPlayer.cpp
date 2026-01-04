/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////

//----------------------------------------------------------------------------
//
//                       Westwood Studios Pacific.
//
//                       Confidential Information
//                Copyright (C) 2001 - All Rights Reserved
//
//----------------------------------------------------------------------------
//
// Project:   Generals
//
// Module:    VideoDevice
//
// File name: BinkDevice.cpp
//
// Created:   10/22/01	TR
//
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
//         Includes
//----------------------------------------------------------------------------

#include "Lib/BaseType.h"
#include "VideoDevice/Bink/BinkVideoPlayer.h"
#include "Common/AudioAffect.h"
#include "Common/GameAudio.h"
#include "Common/GameMemory.h"
#include "Common/GlobalData.h"
#include "Common/Registry.h"
#include "Common/FileSystem.h"
#include <windows.h>

//----------------------------------------------------------------------------
//         Externals
//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
//         Defines
//----------------------------------------------------------------------------
#define VIDEO_LANG_PATH_FORMAT "Data/%s/Movies/%s.%s"
#define VIDEO_PATH	"Data\\Movies"
#define VIDEO_EXT		"bik"



//----------------------------------------------------------------------------
//         Private Types
//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
//         Private Data
//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
//         Public Data
//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
//         Private Prototypes
//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
//         Private Functions
//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
//         Public Functions
//----------------------------------------------------------------------------


//============================================================================
// BinkVideoPlayer::BinkVideoPlayer
//============================================================================

BinkVideoPlayer::BinkVideoPlayer()
{

}

//============================================================================
// BinkVideoPlayer::~BinkVideoPlayer
//============================================================================

BinkVideoPlayer::~BinkVideoPlayer()
{
	deinit();
}

//============================================================================
// BinkVideoPlayer::init
//============================================================================

void	BinkVideoPlayer::init( void )
{
	// Need to load the stuff from the ini file.
	VideoPlayer::init();

	initializeBinkWithMiles();
}

//============================================================================
// BinkVideoPlayer::deinit
//============================================================================

void BinkVideoPlayer::deinit( void )
{
	TheAudio->releaseHandleForBink();
	VideoPlayer::deinit();
}

//============================================================================
// BinkVideoPlayer::reset
//============================================================================

void	BinkVideoPlayer::reset( void )
{
	VideoPlayer::reset();
}

//============================================================================
// BinkVideoPlayer::update
//============================================================================

void	BinkVideoPlayer::update( void )
{
	VideoPlayer::update();

}

//============================================================================
// BinkVideoPlayer::loseFocus
//============================================================================

void	BinkVideoPlayer::loseFocus( void )
{
	VideoPlayer::loseFocus();
}

//============================================================================
// BinkVideoPlayer::regainFocus
//============================================================================

void	BinkVideoPlayer::regainFocus( void )
{
	VideoPlayer::regainFocus();
}

//============================================================================
// BinkVideoPlayer::createStream
//============================================================================

VideoStreamInterface* BinkVideoPlayer::createStream( HBINK handle, const char* tempFilePath )
{

	if ( handle == NULL )
	{
		return NULL;
	}

	BinkVideoStream *stream = NEW BinkVideoStream;

	if ( stream )
	{

		stream->m_handle = handle;
		stream->m_next = m_firstStream;
		stream->m_player = this;
		m_firstStream = stream;
		
		// Store temp file path if provided (for cleanup when stream closes)
		if (tempFilePath != NULL)
		{
			int pathLen = strlen(tempFilePath) + 1;
			stream->m_tempFilePath = NEW char[pathLen];
			strcpy(stream->m_tempFilePath, tempFilePath);
		}

		// never let volume go to 0, as Bink will interpret that as "play at full volume".
		Int mod = (Int) ((TheAudio->getVolume(AudioAffect_Speech) * 0.8f) * 100) + 1;
		Int volume = (32768*mod)/100;
		DEBUG_LOG(("BinkVideoPlayer::createStream() - About to set volume (%g -> %d -> %d",
			TheAudio->getVolume(AudioAffect_Speech), mod, volume));
		BinkSetVolume( stream->m_handle,0, volume);
		DEBUG_LOG(("BinkVideoPlayer::createStream() - set volume"));
	}

	return stream;
}

//============================================================================
// Helper function to try opening file through FileSystem (supports .big archives)
// Returns HBINK handle if successful, NULL otherwise
// Outputs tempFilePath if a temp file was created (caller must free this string)
//============================================================================
static HBINK tryOpenBinkFromFileSystem(const char* filePath, char** tempFilePathOut)
{
	*tempFilePathOut = NULL;
	
	// Try opening through FileSystem first (supports .big archives)
	File* file = TheFileSystem->openFile(filePath);
	if (file)
	{
		// Get file size before reading
		Int fileSize = file->size();
		if (fileSize > 0)
		{
			// Read entire file into memory
			char* fileData = file->readEntireAndClose();
			if (fileData)
			{
				// BinkOpen doesn't support memory buffers directly, so we need to write to a temp file
				// Create a temporary file path
				char tempPath[_MAX_PATH];
				char tempFileName[_MAX_PATH];
				GetTempPath(_MAX_PATH, tempPath);
				GetTempFileName(tempPath, "Bink", 0, tempFileName);
				
				// Write the file data to the temp file
				File* tempFile = TheFileSystem->openFile(tempFileName, File::WRITE);
				if (tempFile)
				{
					Int bytesWritten = tempFile->write(fileData, fileSize);
					tempFile->close();
					
					if (bytesWritten == fileSize)
					{
						// Now try to open the Bink file from the temp file
						HBINK handle = BinkOpen(tempFileName, BINKPRELOADALL);
						if (handle)
						{
							// Free the original file data
							delete[] fileData;
							
							// Store the temp file path for cleanup
							int pathLen = strlen(tempFileName) + 1;
							*tempFilePathOut = NEW char[pathLen];
							strcpy(*tempFilePathOut, tempFileName);
							
							return handle;
						}
					}
					
					// If BinkOpen failed, delete the temp file
					DeleteFile(tempFileName);
				}
				
				// Free the memory if we couldn't use it
				delete[] fileData;
			}
		}
		else
		{
			// File size is 0 or invalid, close the file
			file->close();
		}
	}
	
	return NULL;
}

//============================================================================
// BinkVideoPlayer::open
//============================================================================

VideoStreamInterface*	BinkVideoPlayer::open( AsciiString movieTitle )
{
	VideoStreamInterface*	stream = NULL;

	const Video* pVideo = getVideo(movieTitle);
	if (pVideo) {
		DEBUG_LOG(("BinkVideoPlayer::createStream() - About to open bink file"));

		HBINK handle = NULL;
		char* tempFilePath = NULL;

		if (pVideo->m_objectDirectory.isNotEmpty())
		{
			// If object directory is set, use {objectDirectory}Art\Videos\ path
			// Note: objectDirectory already ends with a backslash, so we don't add another one
			const char* objectDirPath = pVideo->m_objectDirectory.str();

			if (TheGlobalData->m_modDir.isNotEmpty())
			{
				char filePath[ _MAX_PATH ];
				sprintf( filePath, "%s%sArt\\Videos\\%s.%s", TheGlobalData->m_modDir.str(), objectDirPath, pVideo->m_filename.str(), VIDEO_EXT );
				
				// Try FileSystem first (supports .big archives)
				handle = tryOpenBinkFromFileSystem(filePath, &tempFilePath);
				if (!handle)
				{
					// Fall back to direct file system access
					handle = BinkOpen(filePath , BINKPRELOADALL );
					DEBUG_ASSERTLOG(!handle, ("opened bink file %s", filePath));
				}
				if (handle)
				{
					return createStream( handle, tempFilePath );
				}
			}

			char filePath[ _MAX_PATH ];
			sprintf( filePath, "%sArt\\Videos\\%s.%s", objectDirPath, pVideo->m_filename.str(), VIDEO_EXT );
			
			// Try FileSystem first (supports .big archives)
			handle = tryOpenBinkFromFileSystem(filePath, &tempFilePath);
			if (!handle)
			{
				// Fall back to direct file system access
				handle = BinkOpen(filePath , BINKPRELOADALL );
				DEBUG_ASSERTLOG(!handle, ("opened bink file %s", filePath));
			}
			if (handle)
			{
				return createStream( handle, tempFilePath );
			}
		}
		else
		{
			// Original logic when object directory is empty
			if (TheGlobalData->m_modDir.isNotEmpty())
			{
				char filePath[ _MAX_PATH ];
				sprintf( filePath, "%s%s\\%s.%s", TheGlobalData->m_modDir.str(), VIDEO_PATH, pVideo->m_filename.str(), VIDEO_EXT );
				
				// Try FileSystem first (supports .big archives)
				handle = tryOpenBinkFromFileSystem(filePath, &tempFilePath);
				if (!handle)
				{
					// Fall back to direct file system access
					handle = BinkOpen(filePath , BINKPRELOADALL );
					DEBUG_ASSERTLOG(!handle, ("opened bink file %s", filePath));
				}
				if (handle)
				{
					return createStream( handle, tempFilePath );
				}
			}

			char localizedFilePath[ _MAX_PATH ];
			sprintf( localizedFilePath, VIDEO_LANG_PATH_FORMAT, GetRegistryLanguage().str(), pVideo->m_filename.str(), VIDEO_EXT );
			
			// Try FileSystem first (supports .big archives)
			handle = tryOpenBinkFromFileSystem(localizedFilePath, &tempFilePath);
			if (!handle)
			{
				// Fall back to direct file system access
				handle = BinkOpen(localizedFilePath , BINKPRELOADALL );
				DEBUG_ASSERTLOG(!handle, ("opened localized bink file %s", localizedFilePath));
			}
			if (!handle)
			{
				char filePath[ _MAX_PATH ];
				sprintf( filePath, "%s\\%s.%s", VIDEO_PATH, pVideo->m_filename.str(), VIDEO_EXT );
				
				// Try FileSystem first (supports .big archives)
				handle = tryOpenBinkFromFileSystem(filePath, &tempFilePath);
				if (!handle)
				{
					// Fall back to direct file system access
					handle = BinkOpen(filePath , BINKPRELOADALL );
					DEBUG_ASSERTLOG(!handle, ("opened bink file %s", filePath));
				}
			}
		}

		if (handle)
		{
			DEBUG_LOG(("BinkVideoPlayer::createStream() - About to create stream"));
			stream = createStream( handle, tempFilePath );
		}
	}

	return stream;
}

//============================================================================
// BinkVideoPlayer::load
//============================================================================

VideoStreamInterface*	BinkVideoPlayer::load( AsciiString movieTitle )
{
	return open(movieTitle); // load() used to have the same body as open(), so I'm combining them.  Munkee.
}

//============================================================================
//============================================================================
void BinkVideoPlayer::notifyVideoPlayerOfNewProvider( Bool nowHasValid )
{
	if (!nowHasValid) {
		TheAudio->releaseHandleForBink();
		BinkSetSoundTrack(0, 0);
	} else {
		initializeBinkWithMiles();
	}
}

//============================================================================
//============================================================================
void BinkVideoPlayer::initializeBinkWithMiles()
{
	Int retVal = 0;
	void *driver = TheAudio->getHandleForBink();

	if ( driver )
	{
		retVal = BinkSoundUseDirectSound(driver);
	}
	if( !driver || retVal == 0)
	{
		BinkSetSoundTrack ( 0,0 );
	}
}

//============================================================================
// BinkVideoStream::BinkVideoStream
//============================================================================

BinkVideoStream::BinkVideoStream()
: m_handle(NULL),
	m_memFile(NULL),
	m_tempFilePath(NULL)
{

}

//============================================================================
// BinkVideoStream::~BinkVideoStream
//============================================================================

BinkVideoStream::~BinkVideoStream()
{
	if ( m_handle != NULL )
	{
		BinkClose( m_handle );
		m_handle = NULL;
	}
	
	// Delete temporary file if it was created (extracted from .big archive)
	if ( m_tempFilePath != NULL )
	{
		DeleteFile(m_tempFilePath);
		delete[] m_tempFilePath;
		m_tempFilePath = NULL;
	}
	
	// Clean up memory file if it exists
	if ( m_memFile != NULL )
	{
		delete[] m_memFile;
		m_memFile = NULL;
	}
}

//============================================================================
// BinkVideoStream::update
//============================================================================

void BinkVideoStream::update( void )
{
	BinkWait( m_handle );
}

//============================================================================
// BinkVideoStream::isFrameReady
//============================================================================

Bool BinkVideoStream::isFrameReady( void )
{
	return !BinkWait( m_handle );
}

//============================================================================
// BinkVideoStream::frameDecompress
//============================================================================

void BinkVideoStream::frameDecompress( void )
{
		BinkDoFrame( m_handle );
}

//============================================================================
// BinkVideoStream::frameRender
//============================================================================

void BinkVideoStream::frameRender( VideoBuffer *buffer )
{
	if ( buffer )
	{
		void *mem = buffer->lock();

		u32 flags;

		switch ( buffer->format())
		{
			case VideoBuffer::TYPE_X8R8G8B8:
				flags = BINKSURFACE32;
				break;

			case VideoBuffer::TYPE_R8G8B8:
				flags = BINKSURFACE24;
				break;

			case VideoBuffer::TYPE_R5G6B5:
				flags = BINKSURFACE565;
				break;

			case VideoBuffer::TYPE_X1R5G5B5:
				flags = BINKSURFACE555;
				break;

			default:
				return;
		}

		if ( mem != NULL )
		{

			BinkCopyToBuffer ( m_handle, mem, buffer->pitch(), buffer->height(),
													buffer->xPos(), buffer->yPos(), flags );
			buffer->unlock();
		}
	}

}

//============================================================================
// BinkVideoStream::frameNext
//============================================================================

void BinkVideoStream::frameNext( void )
{
	BinkNextFrame( m_handle );
}

//============================================================================
// BinkVideoStream::frameIndex
//============================================================================

Int BinkVideoStream::frameIndex( void )
{
	return m_handle->FrameNum - 1;
}

//============================================================================
// BinkVideoStream::totalFrames
//============================================================================

Int	BinkVideoStream::frameCount( void )
{
	return m_handle->Frames;
}

//============================================================================
// BinkVideoStream::frameGoto
//============================================================================

void BinkVideoStream::frameGoto( Int index )
{
	BinkGoto(m_handle, index, NULL );
}

//============================================================================
// VideoStream::height
//============================================================================

Int		BinkVideoStream::height( void )
{
	return m_handle->Height;
}

//============================================================================
// VideoStream::width
//============================================================================

Int		BinkVideoStream::width( void )
{
	return m_handle->Width;
}



