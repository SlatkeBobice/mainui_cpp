/*
Copyright (C) 1997-2001 Id Software, Inc.

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/

#include "Framework.h"
#include "Bitmap.h"
#include "PicButton.h"
#include "YesNoMessageBox.h"
#include "keydefs.h"
#include "TabView.h"

#define ART_BANNER	     	"gfx/shell/head_config"

class CMenuOptions: public CMenuFramework
{
private:
	void _Init( void ) override;

public:
	typedef CMenuFramework BaseClass;
	CMenuOptions() : CMenuFramework("CMenuOptions") { }

	// update dialog
	CMenuYesNoMessageBox msgBox;
};

/*
=================
CMenuOptions::Init
=================
*/
void CMenuOptions::_Init( void )
{
	banner.SetPicture( ART_BANNER );

	msgBox.Link( this );

	AddItem( banner );
	AddButton( L( "Управление" ), L( NULL ),
		PC_CONTROLS, UI_Controls_Menu, QMF_NOTIFY );
	AddButton( L( "Звук" ), L( NULL ),
		PC_AUDIO, UI_Audio_Menu, QMF_NOTIFY );
	AddButton( L( "Видео" ), L( NULL ),
		PC_VIDEO, UI_Video_Menu, QMF_NOTIFY );
	AddButton( L( "Применить" ), L( NULL ),
		PC_DONE, VoidCb( &CMenuOptions::Hide ), QMF_NOTIFY );
}

ADD_MENU( menu_options, CMenuOptions, UI_Options_Menu );
