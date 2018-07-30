#include "../includes.h"
#include "../UTILS/interfaces.h"
#include "../SDK/IEngine.h"
#include "../SDK/CClientEntityList.h"
#include "../SDK/CInputSystem.h"
#include "../UTILS/render.h"
#include "../SDK/ConVar.h"
#include "Components.h"
#include "..\ImGui\imgui.h"
#include <d3d9.h>
#include "menu_framework.h"
#include "../HOOKS/hooks.h"
int menutab;

int AutoCalc(int va)
{
	if (va == 1)
		return va * 35;
	else if (va == 2)
		return va * 34;
	else
		return va * 25 + 7.5;
}

namespace MENU
{
	void InitColors()
	{
		using namespace PPGUI_PP_GUI;


		colors[WINDOW_BODY] = CColor(22, 22, 22);
		colors[WINDOW_TITLE_BAR] = CColor(28, 28, 28, 0); //255, 75, 0
		colors[WINDOW_TEXT] = CColor(137, 180, 48);

		colors[GROUPBOX_BODY] = CColor(40, 40, 40, 0);
		colors[GROUPBOX_OUTLINE] = CColor(60, 60, 60);
		colors[GROUPBOX_TEXT] = WHITE;

		colors[SCROLLBAR_BODY] = SETTINGS::settings.menu_col;

		colors[SEPARATOR_TEXT] = WHITE;
		colors[SEPARATOR_LINE] = CColor(60, 60, 60, 255);

		colors[CHECKBOX_CLICKED] = CColor(162, 204, 47);//HOTPINK
		colors[CHECKBOX_NOT_CLICKED] = CColor(60, 60, 60, 255);
		colors[CHECKBOX_TEXT] = WHITE;

		colors[BUTTON_BODY] = CColor(40, 40, 40, 255);
		colors[BUTTON_TEXT] = WHITE;

		colors[COMBOBOX_TEXT] = LIGHTGREY;
		colors[COMBOBOX_SELECTED] = CColor(40, 40, 40, 255);
		colors[COMBOBOX_SELECTED_TEXT] = WHITE;
		colors[COMBOBOX_ITEM] = CColor(20, 20, 20, 255);
		colors[COMBOBOX_ITEM_TEXT] = LIGHTGREY;

		colors[SLIDER_BODY] = CColor(40, 40, 40, 255);
		colors[SLIDER_VALUE] = CColor(137, 180, 48);//HOTPINK
		colors[SLIDER_TEXT] = WHITE;

		colors[TAB_BODY] = CColor(21, 21, 19);
		colors[TAB_TEXT] = CColor(255, 255, 255, 255);
		colors[TAB_BODY_SELECTED] = CColor(40, 40, 40, 150); //HOTPINK
		colors[TAB_TEXT_SELECTED] = CColor(137, 180, 48);

		colors[VERTICAL_TAB_BODY] = CColor(22, 22, 22, 120);
		colors[VERTICAL_TAB_TEXT] = CColor(255, 255, 255, 255);
		colors[VERTICAL_TAB_OUTLINE] = CColor(22, 22, 22, 150); //HOTPINK
		colors[VERTICAL_TAB_BODY_SELECTED] = CColor(22, 22, 22, 255); //HOTPINK
		colors[VERTICAL_TAB_TEXT_SELECTED] = CColor(137, 180, 48);

		colors[COLOR_PICKER_BODY] = CColor(50, 50, 50, 0);
		colors[COLOR_PICKER_TEXT] = WHITE;
		colors[COLOR_PICKER_OUTLINE] = CColor(0, 0, 0, 0);
	}

	void Do()
	{
		static bool menu_open = false;

		if (UTILS::INPUT::input_handler.GetKeyState(VK_INSERT) & 1)
		{
			menu_open = !menu_open;
			static const auto cvar = INTERFACES::cvar->FindVar("cl_mouseenable");
			if (menu_open)
				cvar->SetValue(0);
			else
				cvar->SetValue(1);

			INTERFACES::InputSystem->EnableInput(!menu_open);


		}

		if (UTILS::INPUT::input_handler.GetKeyState(UTILS::INPUT::input_handler.keyBindings(SETTINGS::settings.flip_int)) & 1)
			SETTINGS::settings.flip_bool = !SETTINGS::settings.flip_bool;

		if (UTILS::INPUT::input_handler.GetKeyState(UTILS::INPUT::input_handler.keyBindings(SETTINGS::settings.quickstopkey)) & 1)
			SETTINGS::settings.stop_flip = !SETTINGS::settings.stop_flip;

		if (UTILS::INPUT::input_handler.GetKeyState(UTILS::INPUT::input_handler.keyBindings(SETTINGS::settings.overridekey)) & 1)
			SETTINGS::settings.overridething = !SETTINGS::settings.overridething;


		InitColors();
		if (menu_hide)
		{

		}
		else
		{
			if (menu_open)
			{
				using namespace PPGUI_PP_GUI;
				if (!menu_open) return;

				DrawMouse();

				SetFont(FONTS::menu_window_font);
				WindowBegin("OOF", Vector2D(200, 200), Vector2D(600, 400));

				std::vector<std::string> tabs = { "aimbot", "visuals", "misc", "antiaim", "config" };
				std::vector<std::string> aim_mode = { "rage", "legit" };
				std::vector<std::string> acc_mode = { "head", "body aim", "hitscan" };
				std::vector<std::string> chams_mode = { "none", "visible", "invisible" };
				std::vector<std::string> aa_pitch = { "none", "emotion", "fake down", "fake up", "fake zero" };
				std::vector<std::string> aa_mode = { "none", "backwards", "sideways", "backjitter", "lowerbody", "legit troll", "rotational", "autodirectional", "freestanding", "pysenAA" };
				std::vector<std::string> aa_fake = { "none", "backjitter", "random", "local view", "opposite", "rotational" };
				std::vector<std::string> configs = { "default", "legit", "autos", "scouts", "pistols", "awps", "nospread" };
				std::vector<std::string> box_style = { "none", "full", "debug" };
				std::vector<std::string> media_style = { "perfect", "random" };
				std::vector<std::string> delay_shot = { "off", "lag compensation" };
				std::vector<std::string> fakelag_mode = { "factor", "adaptive" };
				std::vector<std::string> key_binds = { "none", "mouse1", "mouse2", "mouse3", "mouse4", "mouse5", "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "f1", "f2", "f3", "f4", "f5", "f6", "f7", "f8", "f9", "f10", "f11", "f12" };
				std::vector<std::string> hitmarker = { "none", "gamesense", "bameware", "custom" };
				std::vector<std::string> antiaimmode = { "standing", "moving", "jumping" };
				std::vector<std::string> glow_styles = { "regular", "pulsing", "outline" };
				std::vector<std::string> local_chams = { "none","sim fakelag: normal", "non-sim fakelag", "sim fakelag: color" };
				std::vector<std::string> chams_type = { "metallic", "basic" };
				std::vector<std::string> team_select = { "enemy", "team" };
				std::vector<std::string> crosshair_select = { "none", "static", "recoil" };
				std::vector<std::string> autostop_method = { "head", "hitscan" };
				std::vector<std::string> override_method = { "set", "key-press" };
				std::string config;


				SplitWindow(5);
				SetLine(1);
				GroupboxBegin2("", 100, 350, 0);

				switch (VerticalTab("OOF", tabs, OBJECT_FLAGS::FLAG_NONE))
				{
				case 0:
				{
					menutab = 0;
					break;
				}
				case 1:
				{
					menutab = 1;
					break;
				}
				case 2:
				{
					menutab = 2;
					break;
				}
				case 3:
				{
					menutab = 3;
					break;
				}
				case 4:
				{
					menutab = 4;
					break;
				}
				}
				GroupboxEnd();

				SetLine(2);

				GroupboxBegin2("", 450, 350, 0);
				if (menutab == 0)// RAGE
				{
					Checkbox("enable aimbot", SETTINGS::settings.aim_bool);
					if (SETTINGS::settings.aim_bool)
					{

						Combobox("aimbot type", aim_mode, SETTINGS::settings.aim_type);
						Combobox("aimbot mode", acc_mode, SETTINGS::settings.acc_type);
						Checkbox("Resolver enable", SETTINGS::settings.resolve_bool);
						Checkbox("more aimpoints", SETTINGS::settings.multi_bool);
						Checkbox("Auto-revolver", SETTINGS::settings.auto_revolver_enabled);
						Checkbox("Velocity-Prediction", SETTINGS::settings.vecvelocityprediction);
						Checkbox("HS when in air", SETTINGS::settings.hsinair);
						Combobox("delay shot", delay_shot, SETTINGS::settings.delay_shot);
						Slider("minimum hit-chance", 0, 100, SETTINGS::settings.chance_val);
						Slider("minimum damage", 1, 100, SETTINGS::settings.damage_val);
						Slider("head scale", 0, 1, SETTINGS::settings.point_val);
						Slider("body scale", 0, 1, SETTINGS::settings.body_val);



					}
				}

				else if (menutab == 1)//VISUALS
				{
									
					Checkbox("enable visuals", SETTINGS::settings.esp_bool);
					if (SETTINGS::settings.esp_bool)
					{
						

						Checkbox("draw enemy box", SETTINGS::settings.box_bool);
						Checkbox("draw enemy name", SETTINGS::settings.name_bool);
						Checkbox("draw enemy weapon", SETTINGS::settings.weap_bool);
						Checkbox("draw enemy flags", SETTINGS::settings.info_bool);
						Checkbox("draw enemy health", SETTINGS::settings.health_bool);
						Checkbox("draw enemy ammo", SETTINGS::settings.ammo_bool);  
						Checkbox("render spread", SETTINGS::settings.spread_bool);
						Checkbox("remove smoke", SETTINGS::settings.smoke_bool);
						Checkbox("remove scope", SETTINGS::settings.scope_bool);
						Checkbox("remove zoom", SETTINGS::settings.removescoping);
						Checkbox("lby indicator", SETTINGS::settings.lbyenable);
						Checkbox("fix zoom sensitivity", SETTINGS::settings.fixscopesens);
						Checkbox("bullet tracers", SETTINGS::settings.beam_bool);
						Checkbox("local glow", SETTINGS::settings.glowlocal);
						Combobox("local glow style", glow_styles, SETTINGS::settings.glowstylelocal);
						Checkbox("thirdperson", SETTINGS::settings.tp_bool);
						Combobox("thirdperson key", key_binds, SETTINGS::settings.thirdperson_int);
						Combobox("model team selection", team_select, SETTINGS::settings.chamsteamselection);
						Combobox("model type", chams_type, SETTINGS::settings.chamstype);
						Combobox("enemy coloured models", chams_mode, SETTINGS::settings.chams_type);
						Combobox("crosshair", crosshair_select, SETTINGS::settings.xhair_type);
						Combobox("local chams", local_chams, SETTINGS::settings.localchams);
						Combobox("hitmarker sound", hitmarker, SETTINGS::settings.hitmarker_val);			
						Slider("viewmodel fov", 0, 179, SETTINGS::settings.viewfov_val, 0);
						Slider("render fov", 0, 179, SETTINGS::settings.fov_val, 0);
						Slider("night value", 0, 100, SETTINGS::settings.daytimevalue, 0);


					}


				}

				else if (menutab == 2)//MISC
				{

					Checkbox("enable misc", SETTINGS::settings.misc_bool);
					if (SETTINGS::settings.misc_bool)
					{

						Checkbox("auto bunnyhop", SETTINGS::settings.bhop_bool);
						Checkbox("auto strafer", SETTINGS::settings.strafe_bool);
						Checkbox("Meme Walk", SETTINGS::settings.astro);
						Checkbox("enable fakelag", SETTINGS::settings.lag_bool);
						Combobox("fakelag type", fakelag_mode, SETTINGS::settings.lag_type);
						Slider("standing lag", 1, 14, SETTINGS::settings.stand_lag);
						Slider("moving lag", 1, 14, SETTINGS::settings.move_lag);
						Slider("jumping lag", 1, 14, SETTINGS::settings.jump_lag);
					}

				}

				else if (menutab == 3)//ANTIAIM
				{
					Checkbox("enable misc", SETTINGS::settings.aa_bool);
					if (SETTINGS::settings.aa_bool)
					{
						Combobox("antiaim mode", antiaimmode, SETTINGS::settings.aa_mode);
						switch (SETTINGS::settings.aa_mode)
						{
						case 0:
							Combobox("antiaim pitch - standing", aa_pitch, SETTINGS::settings.aa_pitch_type);
							Combobox("antiaim real - standing", aa_mode, SETTINGS::settings.aa_real_type);
							Combobox("antiaim fake - standing", aa_fake, SETTINGS::settings.aa_fake_type);
							break;
						case 1:
							Combobox("antiaim pitch - moving", aa_pitch, SETTINGS::settings.aa_pitch1_type);
							Combobox("antiaim real - moving", aa_mode, SETTINGS::settings.aa_real1_type);
							Combobox("antiaim fake - moving", aa_fake, SETTINGS::settings.aa_fake1_type);
							break;
						case 2:
							Combobox("antiaim pitch - jumping", aa_pitch, SETTINGS::settings.aa_pitch2_type);
							Combobox("antiaim real - jumping", aa_mode, SETTINGS::settings.aa_real2_type);
							Combobox("antiaim fake - jumping", aa_fake, SETTINGS::settings.aa_fake2_type);
							break;
						}



						Combobox("flip key", key_binds, SETTINGS::settings.flip_int);
						//Checkbox("fake angle chams", SETTINGS::settings.aa_fakeangchams_bool);
						Checkbox("anti-aim arrows", SETTINGS::settings.rifk_arrow);
						switch (SETTINGS::settings.aa_mode)
						{
						case 0:
							Slider("real additive", -180, 180, SETTINGS::settings.aa_realadditive_val);
							Slider("fake additive", -180, 180, SETTINGS::settings.aa_fakeadditive_val);
							Slider("lowerbodyyaw delta", -180, 180, SETTINGS::settings.delta_val);
							Checkbox("lby flick up", SETTINGS::settings.lbyflickup);
							break;
						case 1:
							Slider("real additive ", -180, 180, SETTINGS::settings.aa_realadditive1_val);
							Slider("fake additive", -180, 180, SETTINGS::settings.aa_fakeadditive1_val);
							Slider("lowerbodyyaw delta", -180, 180, SETTINGS::settings.delta1_val);
							Checkbox("lby flick up", SETTINGS::settings.lbyflickup1);
							break;
						case 2:
							Slider("real additive", -180, 180, SETTINGS::settings.aa_realadditive2_val);
							Slider("fake additive", -180, 180, SETTINGS::settings.aa_fakeadditive2_val);
							Slider("lowerbodyyaw delta", -180, 180, SETTINGS::settings.delta2_val);
							Checkbox("lby flick up", SETTINGS::settings.lbyflickup2);
							break;
						}



						Slider("rotate fake °", 0, 180, SETTINGS::settings.spinanglefake);
						Slider("rotate fake %", 0, 100, SETTINGS::settings.spinspeedfake);

						switch (SETTINGS::settings.aa_mode)
						{
						case 0:
							Slider("rotate standing °", 0, 180, SETTINGS::settings.spinangle);
							Slider("rotate standing %", 0, 100, SETTINGS::settings.spinspeed);
							break;
						case 1:
							Slider("rotate moving °", 0, 180, SETTINGS::settings.spinangle1);
							Slider("rotate moving %", 0, 100, SETTINGS::settings.spinspeed1);
							break;
						case 2:
							Slider("rotate jumping °", 0, 180, SETTINGS::settings.spinangle2);
							Slider("rotate jumping %", 0, 100, SETTINGS::settings.spinspeed2);
							break;
						}
					}

				}
				else if (menutab == 4)//CONFIG
				{
					switch (Combobox("config", configs, SETTINGS::settings.config_sel))
					{
					case 0: config = "default"; break;
					case 1: config = "legit"; break;
					case 2: config = "auto_hvh"; break;
					case 3: config = "scout_hvh"; break;
					case 4: config = "pistol_hvh"; break;
					case 5: config = "awp_hvh"; break;
					case 6: config = "nospread_hvh"; break;
					}

					if (Button("Load Config"))
					{
						SETTINGS::settings.Load(config);

						INTERFACES::cvar->ConsoleColorPrintf(CColor(200, 255, 0, 255), "[stackhack] ");
						GLOBAL::Msg("Configuration loaded.    \n");
					}

					if (Button("Save Config"))
					{
						SETTINGS::settings.Save(config);

						INTERFACES::cvar->ConsoleColorPrintf(CColor(200, 255, 0, 255), "[stackhack] ");
						GLOBAL::Msg("Configuration saved.    \n");
					}

				}
				GroupboxEnd();

				WindowEnd();



				int w, h;
				static int x, y;

				INTERFACES::Engine->GetScreenSize(w, h);
				static bool init = false;
				if (init == false) {
					x = w / 2 - (400 / 2);
					y = h / 2 - (200 / 2);
					init = true;
				}
			}
		}
	}
}