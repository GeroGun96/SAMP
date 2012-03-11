Timer:Slow()
{
	new hour;
	new minute;
	new second;
	gettime(hour, minute, second);
	FormatNew:hourString[3]("%2d", hour);
	FormatNew:minuteString[3]("%2d", minute);
	if (hour < 10)
	{
		hourString[0] = '0';
	}
	if (minute < 10)
	{
		minuteString[0] = '0';
	}
	FormatNew:clockString[6]("%s:%s", hourString, minuteString);
	TextDrawSetString(textDrawClock, clockString);
	SetWorldTime(hour);
	mysql_ping();
	if (fexist(FILE_UPDATENOTIFICATION))
	{
		new string[256];
		new File:file = fopen(FILE_UPDATENOTIFICATION, io_read);
		fread(file, string);// Skip "------------------------------------------------------------------------"
		fread(file, string);// Read "rXXX | user | yyyy-mm-dd hh:ii:ss +xxxx (ddd, dd mmm yyyy) | x line(s)"
		new revisionString[10];
		new committerName[100];
		new commitDate[50];
		new lineCount[20];
		sscanf(string, "p|ssss", revisionString, committerName, commitDate, lineCount);
		new revision = Str2Val(revisionString);
		if (revision > COMPILER_SVN_REVISION)
		{
			printf("Detected update to revision %d", revision);
			Format:string("Es steht ein Update auf Revision %d zur Verf�gung!", revision);
			SendClientMessageToAdmins(PERMISSION_SERVERADMIN, COLOR_SYSTEM, string);
			Format:string("Committer: %s", committerName);
			SendClientMessageToAdmins(PERMISSION_SERVERADMIN, COLOR_SYSTEM, string);
			fread(file, string);// Skip ""
			SendClientMessageToAdmins(PERMISSION_SERVERADMIN, COLOR_SYSTEM, "*** SVN Changelog:");
			while (fread(file, string))
			{
				RemoveNewLine(string);
				if (strlen(string) && strcmp(string, "------------------------------------------------------------------------"))
				{
					Format:string("> %s", string);
					SendClientMessageToAdmins(PERMISSION_SERVERADMIN, COLOR_SYSTEM, string);
				}
			}
		}
		fclose(file);
		fremove(FILE_UPDATENOTIFICATION);
	}
}