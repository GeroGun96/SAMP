public OnPlayerConnect(playerid)
{
	ResetPlayerVariables(playerid);
	if (IsPlayerNPC(playerid))
	{
		new npcName[MAX_PLAYER_NAME];
		GetPlayerName(playerid, npcName, sizeof(npcName));
		strdel(npcName, 0, 4);
		MySQLQuery("SELECT * FROM `npcs` WHERE `Name` = '%s'", MySQLEscapeString(npcName));
		mysql_store_result();
		SetPlayerSkin(playerid, strval(GetMySQLField("Skin")));
		if (strval(GetMySQLField("StartOnConnect")))
		{
			new color1;
			new color2;
			new modelID;
			new playbackType;
			new vehicleID;
			modelID = strval(GetMySQLField("VehicleModelID"));
			if (modelID)
			{
				playbackType = PLAYER_RECORDING_TYPE_DRIVER;
				color1 = random(127);
				color2 = random(127);
				vehicleID = CreateVehicleEx(modelID, 0.0, 0.0, 0.0, 0.0, color1, color2, 0);
				PutPlayerInVehicle(playerid, vehicleID, 0);
			}
			else
			{
				playbackType = PLAYER_RECORDING_TYPE_ONFOOT;
			}
			StartNPCPlayback(playerid, GetMySQLField("Recording"), playbackType, strval(GetMySQLField("AutoRepeat")));
		}
		mysql_free_result();
	}
	else
	{
		MySQLQuery("SELECT * FROM `users` WHERE `Username` = '%s'", MySQLEscapeString(GetPlayerNameEx(playerid)));
		mysql_store_result();
		if (strval(GetMySQLField("UserID")))
		{
			TogglePlayerSpectating(playerid, true);
			ShowDialog(playerid, DIALOG_LOGIN);
		}
		else
		{
			ShowDialog(playerid, DIALOG_REGISTER_PASSWORD1);
		}
		mysql_free_result();
		SendDeathMessage(INVALID_PLAYER_ID, playerid, 200);
		SendClientMessage(playerid, COLOR_SYSTEM, "Willkommen auf GRG Server!");
		FormatNew:string[70]("Auf diesem Server l�uft aktuell Revision %d unserer Gamemode.", COMPILER_SVN_REVISION);
		SendClientMessage(playerid, COLOR_SYSTEM, string);
		Format:string("%s hat den Server betreten", GetPlayerNameEx(playerid));
		SendClientMessageToAllExcept(playerid, COLOR_JOINLEAVE, string);
		IRC_Say(ircBot, IRC_CHANNEL, string);
		textDrawSpeedoName[playerid] = TextDrawCreate(480, 385, "_");
		TextDrawAlignment(textDrawSpeedoName[playerid], 1);
		TextDrawLetterSize(textDrawSpeedoName[playerid], 0.3, 0.9);
		TextDrawFont(textDrawSpeedoName[playerid], 1);
		TextDrawSetShadow(textDrawSpeedoName[playerid], 2);
		textDrawSpeedoColumn2[playerid] = TextDrawCreate(580, 385, "_");
		TextDrawAlignment(textDrawSpeedoColumn2[playerid], 1);
		TextDrawLetterSize(textDrawSpeedoColumn2[playerid], 0.3, 0.9);
		TextDrawFont(textDrawSpeedoColumn2[playerid], 1);
		TextDrawSetShadow(textDrawSpeedoColumn2[playerid], 2);
		textDrawRadioStation[playerid] = TextDrawCreate(320, 20, "_");
		TextDrawAlignment(textDrawRadioStation[playerid], 2);
		TextDrawBackgroundColor(textDrawRadioStation[playerid], 0x000000ff);
		TextDrawFont(textDrawRadioStation[playerid], 2);
		TextDrawLetterSize(textDrawRadioStation[playerid], 0.4, 1.6);
		TextDrawColor(textDrawRadioStation[playerid], 0x906010ff);
		TextDrawSetOutline(textDrawRadioStation[playerid], 1);
		TextDrawSetProportional(textDrawRadioStation[playerid], 2);
		TextDrawSetShadow(textDrawRadioStation[playerid], 1);
		TextDrawShowForPlayer(playerid, textDrawClock);
	}
	return true;
}