#include "cmd.h"
#include <stdio.h>
#include <string.h>

#include "cmds/cmd_common.h"

#define REGISTER_GLOBAL_COMMAND(IDENTIFIER, NAME, DESCRIPTION, FUNC) Command IDENTIFIER(NAME, DESCRIPTION, FUNC);

Command* Command::g_cmds = NULL;
#if _DEBUG
REGISTER_GLOBAL_COMMAND(g_cmd_test, "test", "An empty test command", Cmd_Test_f);
#endif
REGISTER_GLOBAL_COMMAND(g_cmd_help, "help", "Print usage information", Cmd_Help_f);
REGISTER_GLOBAL_COMMAND(g_cmd_ents, "ents", "Extract the entity string from a fastfile", Cmd_Ents_f);
REGISTER_GLOBAL_COMMAND(g_cmd_extract_ff, "extract-ff", "Extract assets from *.ff files", Cmd_Extract_FF_f);
REGISTER_GLOBAL_COMMAND(g_cmd_extract_iwd, "extract-iwd", "Extract assets from *.iwd files", Cmd_Extract_IWD_f);

#undef REGISTER_GLOBAL_COMMAND

Command::Command(const char* name, const char* description,  cmd_func_t func) : func(func)
{
	this->SetOwner(this);
	
	if(!Command::g_cmds)
	{
		g_cmds = this;
	}
	else
	{
		g_cmds->AddToEnd(this);
	}
	
	this->name = name;
	this->desc = description;
	this->flags = ARG_COMMAND;
}

int Command::Exec(int argc, char** argv) const
{
#if _DEBUG
	printf("Executing command: '%s' with the following arguments:\n", this->name);
	for(int i = 0; i < argc; i++)
	{
		printf("  [%d] %s\n", i, argv[i]);
	}
	printf("\n");
#endif

	return this->func(argc, argv);
}

Command* Command::GlobalCommands(void)
{
	return Command::g_cmds;
}

//
// Attempts to resolve a command from a given argument string
// Returns NULL if there is no match
//
Command* Command::ResolveCommand(const char* str)
{
	for(Command* cmd = Command::g_cmds; cmd; cmd = cmd->NextElem())
	{
		if(strcmp(cmd->Name(), str) == 0)
		{
			return cmd;
		}
	}
	
	return NULL;
}
