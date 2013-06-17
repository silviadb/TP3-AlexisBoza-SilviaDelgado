%{
#include "y.tab.h"
#include <stdio.h>
#include <math.h>
int flag = 0;/*valor default 0(fuera del tag tag) y 1( dentro del tag)*/
%} 
/*definiciones*/
%option yylineno
DocType !DOCTYPE
Size size
Char char
Tag <
TagClose >
FinalTagClose "</"
CommentOpenTag "<!--"
CommentCloseTag "-->"
Ident  [a-z,A-Z,0-9,".",":",",",";","/","\-","_",'\\',"@","{","}","(",")","=","\""]+
/*fin definiciones*/
%%
a {if(flag == 1) return  T_a;}
b {if(flag == 1) return  T_b;}
blockquote {if(flag == 1) return  T_blockquote;}
body {if(flag == 1) return T_body;}
br {if(flag == 1) return  T_br;}
button {if(flag == 1) return  T_button;}
caption {if(flag == 1) return  T_caption;}
code {if(flag == 1) return  T_code;}
div {if(flag == 1) return  T_div;}
dl {if(flag == 1) return  T_dl;}
dt {if(flag == 1) return  T_dt;}
dd {if(flag == 1) return  T_dd;}
em {if(flag == 1) return  T_em;}
embed {if(flag == 1) return  T_embed;}
footer {if(flag == 1) return  T_footer;}
form {if(flag == 1) return  T_form;}
h1 {if(flag == 1) return  T_h1;}
h2 {if(flag == 1) return  T_h2;}
h3 {if(flag == 1) return  T_h3;}
h4 {if(flag == 1) return  T_h4;}
h5 {if(flag == 1) return  T_h5;}
h6 {if(flag == 1) return  T_h6;}
head {if(flag == 1) return  T_head;}
header {if(flag == 1) return  T_header;}
hr {if(flag == 1) return  T_hr;}
html {if(flag == 1) return  T_html;}
img {if(flag == 1) return  T_img;}
input {if(flag == 1) return  T_input;}
li {if(flag == 1) return  T_li;}
link {if(flag == 1) return  T_link;}
meta {if(flag == 1) return  T_meta;}
object {if(flag == 1) return  T_object;}
ol {if(flag == 1) return  T_ol;}
option {if(flag == 1) return  T_option;}
p {if(flag == 1) return  T_p;}
pre {if(flag == 1) return  T_pre;}
script {if(flag == 1) return  T_script;}
span {if(flag == 1) return  T_span;}
strong {if(flag == 1) return  T_strong;}
style {if(flag == 1) return  T_style;}
select {if(flag == 1) return  T_select;}
table {if(flag == 1) return  T_table;}
td {if(flag == 1) return  T_td;}
th {if(flag == 1) return  T_th;}
title {if(flag == 1) return  T_title;} 
tr {if(flag == 1) return  T_tr;}
textarea {if(flag == 1) return  T_textarea;}
ul {if(flag == 1) return  T_ul;}
{DocType} {if(flag == 1) return  T_DOCTYPE;}
{Ident} {yylval.str=strdup(yytext);return T_IDENT;}
{Tag} {flag=1;return  T_Tag ;}
{TagClose} {flag=0;return  T_TagClose;}
{FinalTagClose} {flag=1; return  T_FinalTag;}
{CommentOpenTag} {flag=1;return  T_comment_open;}
{CommentCloseTag} {flag=0;return  T_comment_close;}
[" "\t\n]+  ;
.  fprintf(stderr,"Error: Unrecognized character: %s at line: %d\n",yytext,yylineno) ; /*cualquier otro caracter no es aceptado */
%%
