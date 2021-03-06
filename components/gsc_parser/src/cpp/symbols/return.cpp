#include "return.h"

Return::Return(void) : expr(NULL)
{
	this->type = S_TYPE_STATEMENT_RETURN;
}

Return::Return(Expression* expr, YYLTYPE loc) : expr(expr)
{
	this->type = S_TYPE_STATEMENT_RETURN;
	this->location = loc;
	this->children = (expr) ? expr : NULL;
}

Return::~Return()
{
}

void Return::PrintInfo() const
{
	printf("%s with %d children at %d(%d) - %d(%d)\n",
		SYMBOL_TYPE_STRING(type),
		this->children ? this->children->Size() + 1 : 0,
		location.start.line,
		location.start.character,
		location.end.line,
		location.end.character);
}