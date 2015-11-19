delim	[ \t\n]
ws	{delim}+
digito	[0-9]
num	{digito}+(\.{digito}*(E[+-]?{digito}+)?)?
literal \".*\"
id      (\_|[a-zA-Z])([a-zA-Z]|[0-9]|\_)*

%%
{ws}	{}
"void"    {return TVOID;}
"int"     {return TINT;}
"String"  {return TSTRING;}
"return"  {return TRETURN;}
"if"      {return TIF;}
"else"    {return TELSE;}
"while"   {return TWHILE;}
"print"   {return TPRINT;}
"read"    {return TREAD;}
{id}      {strcpy(yylval.id,yytext);return TID;}

"+"	  {return TADD;}
"-"	  {return TSUB;}
"*"	  {return TMUL;}
"/"	  {return TDIV;}

"("	  {return TAPAR;}
")"	  {return TFPAR;}
"{"	  {return TACHA;}
"}"	  {return TFCHA;}
";"       {return TPONTOEVIRGULA;}
","       {return TVIRGULA;}

"=="      {return TCOMPARACAOIGUAL;}
"<="      {return TMENORIGUAL;}
">="      {return TMAIORIGUAL;}
"<"       {return TMENOR;}
">"       {return TMAIOR;}
"!="      {return TDIFERENTE;}

"&&"      {return TAND;}
"||"      {return TOR;}
"!"       {return TNOT;}
"="       {return TIGUAL;}

{literal} {return TLITERAL;}


{num}	{yylval.constante=atof(yytext); return TNUM;}

. 	{printf("Erro antes %s\n", yytext); exit(0);}


