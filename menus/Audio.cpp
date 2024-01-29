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
#include "Slider.h"
#include "Bitmap.h"
#include "PicButton.h"
#include "CheckBox.h"
#include "SpinControl.h"
#include "StringArrayModel.h"

#define ART_BANNER			"gfx/shell/head_audio"

class CMenuAudio : public CMenuFramework
{
public:
	typedef CMenuFramework BaseClass;

	CMenuAudio() : CMenuFramework("CMenuAudio") { }

private:
	void _Init() override;
	void _VidInit() override;
	void GetConfig();
	void VibrateChanged();
	void SaveAndPopMenu() override;

	void LerpingCvarWrite();

	CMenuSlider	soundVolume;
	CMenuSlider	musicVolume;
	CMenuSlider	suitVolume;
	CMenuSlider	vibration;
	CMenuSpinControl lerping;
	CMenuCheckBox noDSP;
	CMenuCheckBox useAlphaDSP;
	CMenuCheckBox muteFocusLost;
};

/*
=================
CMenuAudio::GetConfig
=================
*/
void CMenuAudio::GetConfig( void )
{
	soundVolume.LinkCvar( "volume" );
	musicVolume.LinkCvar( "MP3Volume" );
	suitVolume.LinkCvar( "suitvolume" );
	vibration.LinkCvar( "vibration_length" );

	lerping.LinkCvar( "s_lerping", CMenuEditable::CVAR_VALUE );
	noDSP.LinkCvar( "dsp_off" );
	useAlphaDSP.LinkCvar( "dsp_coeff_table" );
	muteFocusLost.LinkCvar( "snd_mute_losefocus" );
}

/*
=================
CMenuAudio::SetConfig
=================
*/
void CMenuAudio::SaveAndPopMenu()
{
	soundVolume.WriteCvar();
	musicVolume.WriteCvar();
	suitVolume.WriteCvar();
	lerping.WriteCvar();
	noDSP.WriteCvar();
	useAlphaDSP.WriteCvar();
	muteFocusLost.WriteCvar();

	CMenuFramework::SaveAndPopMenu();
}

/*
=================
CMenuAudio::Init
=================
*/
void CMenuAudio::_Init( void )
{
	static const char *lerpingStr[] =
	{
		L( "Отрубить" ), L( "Баланс" ), L( "Качественно" )
	};

	banner.SetPicture(ART_BANNER);

	soundVolume.SetNameAndStatus( L( "Громкость игры" ), L( NULL ) );
	soundVolume.Setup( 0.0, 1.0, 0.05f );
	soundVolume.onChanged = CMenuEditable::WriteCvarCb;
	soundVolume.SetCoord( 320, 280 );

	musicVolume.SetNameAndStatus( L( "Громкость музыки" ), L( NULL ) );
	musicVolume.Setup( 0.0, 1.0, 0.05f );
	musicVolume.onChanged = CMenuEditable::WriteCvarCb;
	musicVolume.SetCoord( 320, 340 );

	suitVolume.SetNameAndStatus( L( "Громкость костюма" ), L( NULL ) );
	suitVolume.Setup( 0.0, 1.0, 0.05f );
	suitVolume.onChanged = CMenuEditable::WriteCvarCb;
	suitVolume.SetCoord( 320, 400 );

	static CStringArrayModel model( lerpingStr, V_ARRAYSIZE( lerpingStr ));
	lerping.SetNameAndStatus( L( "Интерпол звука" ), L( NULL ) );
	lerping.Setup( &model );
	lerping.onChanged = CMenuEditable::WriteCvarCb;
	lerping.font = QM_SMALLFONT;
	lerping.SetRect( 320, 470, 300, 32 );

	noDSP.SetNameAndStatus( L( "Выкл. звуковые эффектики" ), L( NULL ) );
	noDSP.onChanged = CMenuEditable::WriteCvarCb;
	noDSP.SetCoord( 320, 520 );

	useAlphaDSP.SetNameAndStatus( L( "Использовать эффектики из альфы" ), L( NULL ));
	useAlphaDSP.onChanged = CMenuEditable::WriteCvarCb;
	useAlphaDSP.SetCoord( 320, 570 );

	muteFocusLost.SetNameAndStatus( L( "Заткнуть когда фоном" ), L( NULL ) );
	muteFocusLost.onChanged = CMenuEditable::WriteCvarCb;
	muteFocusLost.SetCoord( 320, 620 );

	AddItem( banner );
	AddButton( L( "Применить" ), L( NULL ), PC_DONE,
		VoidCb( &CMenuAudio::SaveAndPopMenu ) );
	AddItem( soundVolume );
	AddItem( musicVolume );
	AddItem( suitVolume );
	AddItem( lerping );
	AddItem( noDSP );
	AddItem( useAlphaDSP );
	AddItem( muteFocusLost );
}

void CMenuAudio::_VidInit( )
{
	GetConfig();
}

ADD_MENU( menu_audio, CMenuAudio, UI_Audio_Menu );
