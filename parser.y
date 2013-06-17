/*********************************
Insitituto Tecnologico de Costa Rica
Compiladores e Interpretes
Alexis Boza 
Silvia Delgado
2013
ANALIZADOR SINTACTICO
**********************************/
%{
#include <stdio.h>
#include <assert.h>
#include "tree.c"//Arbol de parsing
#include "analyzer.c"//Analizador semantico
//Importamos la variable yylineno para el conteo de linea
extern yylineno;
%}
/******************************************************************
La declaracion %union define la estructura que el analizador 
lexico utilizara para pasar lexemas al analizador
*******************************************************************/
%union{
  char *str;
}
/******************************************************************
Definicion de los simbolos que representan los valores que seran
devueltos por el analizador lexico y que corresponden con los 
terminales de varias reglas del parser
*******************************************************************/
%token  T_a T_b T_blockquote T_body T_br T_button T_caption T_code T_div T_dl T_dt T_dd T_em T_embed T_footer T_form T_h1 
%token  T_h2 T_h3 T_h4 T_h5 T_h6 T_head T_header T_hr T_html T_img T_input T_li T_link T_meta T_object T_ol T_option T_p 
%token  T_pre T_script T_span T_strong T_style T_select T_table T_td T_th T_title T_tr T_textarea T_ul T_DOCTYPE  T_IDENT  
%token  T_Tag T_TagClose T_FinalTag T_comment_open T_comment_close 
%%
/*************************************************************
Definicion de la gramatica, las reglas se encuentran ordenadas
segun su relevancia (de la mas general a la mas especifica)
**************************************************************/
/***************************************
Elementos Principales del Documento HTML
-!DOCTYPE
-html
-header
-head
-body
-footer
***************************************/
document: 	T_Tag T_DOCTYPE T_html T_TagClose {insertar_nodo("document","T_DOCTYPE");}  
		T_Tag T_html T_TagClose {insertar_nodo("document","T_html");ultimo_tag="html";}//<html>
               {insertar_nodo("T_html","header");} header   //Header Content 
		{insertar_nodo("T_html","head");}head    //Head Content
		{insertar_nodo("T_html","body");}body   //Body Content
		{insertar_nodo("T_html","footer");}footer //Footer Content
		T_FinalTag T_html T_TagClose //</html>
	;
header	: 	T_Tag T_header T_TagClose {insertar_nodo("header","T_header");ultimo_tag="header";}//<header> 
		{insertar_nodo("header","text");}text	//Texto(identificadores) dentro de la etiqueta		
		T_FinalTag T_header T_TagClose  //</header>
       	;

head	: 	T_Tag T_head T_TagClose {insertar_nodo("head","T_head");ultimo_tag="head";}//<head>
		{insertar_nodo("head","title");}title	//Titulo: es necesario en el Head
		{insertar_nodo("head","head_element");}head_element //Conjunto de elementos que pueden aparacer en la etiqueta del head
		T_FinalTag T_head T_TagClose//</head>
	;
body	: 	T_Tag T_body {insertar_nodo("body","T_body");ultimo_tag="body";}
		{insertar_nodo("body","Atribute");} Atribute 
                T_TagClose  //<body>
		{insertar_nodo("body","body_content");}body_content //Conjunto de elementos que pueden aparecer dentro de la etiqueta del body
		T_FinalTag T_body T_TagClose  //</body>
	;
footer	: 	T_Tag T_footer T_TagClose {insertar_nodo("footer","T_footer");ultimo_tag="footer";}//<footer>
		{insertar_nodo("footer","text");} text	//Texto dentro de la etiqueta
		T_FinalTag T_footer T_TagClose //</footer>
	;

/******************************
Elementos de la etiqueta <head>
*******************************/
title	:	T_Tag T_title T_TagClose  {insertar_nodo("title","T_title");ultimo_tag="title";}//<title>
		{insertar_nodo("title","text");}text //Titulo de la pagina
		T_FinalTag T_title T_TagClose//</title>
	;

head_element
	: 	script {insertar_nodo("head_element","head_element");}head_element //Elemento Script
	|	style {insertar_nodo("head_element","head_element");}head_element //Elemento Style
	|	META {insertar_nodo("head_element","head_element");}head_element  //Elemento meta
	|	LINK {insertar_nodo("head_element","head_element");}head_element  //Elemento link
	|	{insertar_nodo("head_element","epsilon");}epsilon //la etiqueta <head> puede estar vacia por lo que deriva a Epsilon
	;

script	:	T_Tag T_script {insertar_nodo("head_element","script");
                                insertar_nodo("script","T_script");ultimo_tag="script";}
		{insertar_nodo("script","Atribute");}Atribute //Atributos del script 
		T_TagClose//<script>
		{insertar_nodo("script","Atribute");}text //Texto dentro de la etiqueta 
		T_FinalTag T_script T_TagClose//</script>
	;
style	:	T_Tag T_style {insertar_nodo("head_element","style");
                               insertar_nodo("style","T_style");ultimo_tag="style";}
		{insertar_nodo("style","Atribute");}Atribute //Atributos del style
		T_TagClose //<style>
		{insertar_nodo("script","text");}text //Texto dentro de la etiqueta 
		T_FinalTag T_style T_TagClose//</style>
	;
META
	: 	T_Tag T_meta {insertar_nodo("head_element","META");
                              insertar_nodo("META","T_meta");ultimo_tag="meta";}  
		{insertar_nodo("META","Atribute");}Atribute  //Atributos de la etiqueta
		T_TagClose//<meta>
	;
LINK
	:	T_Tag T_link  {insertar_nodo("head_element","LINK");
                               insertar_nodo("LINK","T_link");ultimo_tag="link";} 
		{insertar_nodo("LINK","Atribute");}Atribute  //Atributos de la etiqueta
		T_TagClose//<link>
	;
/**************FIN DE LOS TAGS DEL ENCABEZADO************/

/********************************
Elementos de la etiqueta <body>
*********************************/
body_content
	: 	body_tag
                body_content//Conjunto de etiquetas o elementos que forman el contenido del body
	| 	{insertar_nodo("body_content","text");}text   //texto dentro del body  
	;
body_tag
	: 	heading //Etiquetas de heading (h1-h6)
	|	block  //Etiquetas de cuerpo o bloque
	;
heading		//Etiquetas h1-h6
	:	h1 
	|	h2 
	| 	h3 
	| 	h4 
	| 	h5 
	| 	h6 
	;

h1	:	T_Tag T_h1 {insertar_nodo("body_content","body_tag");
                            insertar_nodo("body_tag","heading");
                            insertar_nodo("heading","h1");
                            insertar_nodo("h1","T_h1");ultimo_tag="h1";}
		{insertar_nodo("h1","Atribute");}Atribute   	//Atributos de la etiqueta
		T_TagClose 	//<h1>
		{insertar_nodo("h1","text");}text 	//Texto dentro de la etiqueta
		T_FinalTag T_h1 T_TagClose	//</h1>
	;
h2	:	T_Tag T_h2 {insertar_nodo("body_content","body_tag");
                            insertar_nodo("body_tag","heading");
                            insertar_nodo("heading","h2");
                            insertar_nodo("h2","T_h2");ultimo_tag="h2";}
		{insertar_nodo("h2","Atribute");}Atribute   	//Atributos de la etiqueta
		T_TagClose 	//<h2>
		{insertar_nodo("h2","text");}text 	//Texto dentro de la etiqueta
		T_FinalTag T_h2 T_TagClose	//</h2>
	;
h3	:	T_Tag T_h3 {insertar_nodo("body_content","body_tag");
                            insertar_nodo("body_tag","heading");
                            insertar_nodo("heading","h3");
                            insertar_nodo("h3","T_h3");ultimo_tag="h3";}
		{insertar_nodo("h3","Atribute");}Atribute   	//Atributos de la etiqueta
		T_TagClose 	//<h3>
		{insertar_nodo("h3","text");}text 	//Texto dentro de la etiqueta
		T_FinalTag T_h3 T_TagClose	//</h3>
	;
h4	:	T_Tag T_h4 {insertar_nodo("body_content","body_tag");
			    insertar_nodo("body_tag","heading");
                            insertar_nodo("heading","h4");
                            insertar_nodo("h4","T_h4");ultimo_tag="h4";}
		{insertar_nodo("h4","Atribute");}Atribute   	//Atributos de la etiqueta
		T_TagClose 	//<h4>
		{insertar_nodo("h4","text");}text 	//Texto dentro de la etiqueta
		T_FinalTag T_h4 T_TagClose	//</h4>
	;
h5	:	T_Tag T_h5 {insertar_nodo("body_content","body_tag");
                            insertar_nodo("body_tag","heading");
                            insertar_nodo("heading","h5");
                            insertar_nodo("h5","T_h5");ultimo_tag="h5";}
		{insertar_nodo("h5","Atribute");}Atribute   	//Atributos de la etiqueta
		T_TagClose 	//<h5>
		{insertar_nodo("h5","text");}text 	//Texto dentro de la etiqueta
		T_FinalTag T_h5 T_TagClose	//</h5>
	;
h6	:	T_Tag T_h6 {insertar_nodo("body_content","body_tag");
			    insertar_nodo("body_tag","heading");
                            insertar_nodo("heading","h6");
                            insertar_nodo("h6","T_h6");ultimo_tag="h6";}
		{insertar_nodo("h6","Atribute");}Atribute   	//Atributos de la etiqueta
		T_TagClose 	//<h6>
		{insertar_nodo("h6","text");}text 	//Texto dentro de la etiqueta
		T_FinalTag T_h6 T_TagClose	//</h6>
	;
block		//Etiquetas o elementos de bloque o contenido 
	:	paragraph  
	| 	list 
	| 	preformatted  
	| 	div 
	| 	blockquote 
	| 	HR 
	|	table 
	|	button 
	| 	span 
	| 	embed 
	|	object 
	| 	comment 
	|	form
	|	BR
	|	IMG	
	|	bold
	|	emphasize
	| 	strong
	|	code
	|	anchor
	;
paragraph
	:	T_Tag T_p {insertar_nodo("body_content","body_tag");
                           insertar_nodo("body_tag","block");
                           insertar_nodo("block","paragraph");
                           insertar_nodo("paragraph","T_p");ultimo_tag="p";}
		{insertar_nodo("paragraph","Atribute");}Atribute  	//Atributos de la etiqueta 
		T_TagClose  	//<p>
		{insertar_nodo("paragraph","text");}text  		//Texto dentro de la etiqueta
		T_FinalTag T_p T_TagClose	//</p>	
	;

list		//Listas XHTML ordenadas y desordenadas
        :	unordered_list	//Desordenadas
	|	ordered_list	//Ordenadas
	|	def_list	//Descriptivas
	;

unordered_list	//Listas Desordenadas
	:	T_Tag T_ul {insertar_nodo("body_content","body_tag");
                            insertar_nodo("body_tag","block");
                           insertar_nodo("block","list");
                           insertar_nodo("list","unordered_list");
                           insertar_nodo("unordered_list","def_list");} 
		{insertar_nodo("unordered_list","Atribute");}Atribute	//Atributos de la etiqueta
		T_TagClose  	//<ul>
		{insertar_nodo("unordered_list","list_item");}list_item	//Item de la lista 
		T_FinalTag T_ul T_TagClose	//</ul>	
	;

ordered_list	//Listas Ordenadas
	:	T_Tag T_ol {insertar_nodo("body_content","body_tag");
                            insertar_nodo("body_tag","block");
                           insertar_nodo("block","list");
                           insertar_nodo("list","ordered_list");
                           insertar_nodo("ordered_list","T_ol");ultimo_tag="ol";}
		{insertar_nodo("ordered_list","Atribute");}Atribute	//Atributos de la etiqueta 
		T_TagClose  	//<ol>
		{insertar_nodo("ordered_list","list_item");} list_item 	//Item de la Lista
		T_FinalTag T_ol T_TagClose	//</ol>
	;

def_list	//Listas Descriptivas
	:	T_Tag T_dl {insertar_nodo("body_content","body_tag");
                           insertar_nodo("body_tag","block");
                           insertar_nodo("block","list");
                           insertar_nodo("list","def_list");
                           insertar_nodo("def_list","T_dl");ultimo_tag="dl";}
		{insertar_nodo("def_list","Atribute");}Atribute 	//Atributos de la etiqueta
		T_TagClose  	//<dl>
		{insertar_nodo("def_list","def_list_item");}def_list_item 	//Item de la Lista
		T_FinalTag T_dl T_TagClose 	//</dl>
     
	;

list_item	//Un Item de una lista puede poseer solo texto o sublistas
	:	//Item con solo texto
		T_Tag T_li  {insertar_nodo("list_item","T_li");ultimo_tag="li";}
		{insertar_nodo("list_item","Atribute");}Atribute  	//Atributos de la etiqueta
		T_TagClose  	//<li>
		{insertar_nodo("list_item","text");}text  		//Texto dentro de la etiqueta
                
                T_FinalTag T_li T_TagClose 	//</li>
                list_item
        
	|	epsilon		//Puede derivar en epsilon
	;



def_list_item	//Items de las listas descriptivas
	:	dt 
                {insertar_nodo("def_list_item","def_list_item");}def_list_item	//Define terminos/nombres
	| 	dd  
                {insertar_nodo("def_list_item","def_list_item");}def_list_item	//Descripcion de cada termino/nombre
	|	epsilon
	;

dt	:	T_Tag T_dt  T_TagClose {insertar_nodo("def_list_item","dt");
                                        insertar_nodo("dt","T_dt");ultimo_tag="dt";}	//<dt>
		{insertar_nodo("dt","text");}text 	//Texto dentro de la etiqueta
		T_FinalTag T_dt T_TagClose	//</dt>
	;
dd	:	T_Tag T_dd  T_TagClose	{insertar_nodo("def_list_item","dd");
                                         insertar_nodo("dd","T_dd");ultimo_tag="dd";}//<dd>
		{insertar_nodo("dd","text");}text //Texto dentro de la etiqueta
		T_FinalTag T_dd T_TagClose	//</dd>
	;
preformatted
	:	T_Tag T_pre  T_TagClose{insertar_nodo("body_content","body_tag");
                                        insertar_nodo("body_tag","block");
                                        insertar_nodo("block","preformatted");
                                	insertar_nodo("preformatted","T_pre");ultimo_tag="pre";}//<pre>
		{insertar_nodo("preformatted","text");}text 	//Texto dentro de la etiqueta
		T_FinalTag T_pre T_TagClose	//</pre>
	;

div	:	T_Tag T_div {insertar_nodo("body_content","body_tag");
                             insertar_nodo("body_tag","block");
                             insertar_nodo("block","div");
                             insertar_nodo("div","T_div");ultimo_tag="div";}
		{insertar_nodo("div","Atribute");}Atribute 	//Atributos de la etiqueta
		T_TagClose 	//<div>
		{insertar_nodo("div","body_content");}body_content 	//Un div puede contener varios elementos
		T_FinalTag T_div T_TagClose		//</div>
	;

blockquote
	:	T_Tag T_blockquote {insertar_nodo("body_content","body_tag");
                                    insertar_nodo("body_tag","block");
                                    insertar_nodo("block","blockquote");
                                    insertar_nodo("blockquote","T_blockquote");ultimo_tag="blockquote";}
		{insertar_nodo("blockquote","Atribute");}Atribute	//Atributos de la etiqueta 
		T_TagClose 	//<blockquote>
		{insertar_nodo("blockquote","block");}block 	//blockquote en XHTML este debe contener elementos de bloque
		T_FinalTag T_blockquote T_TagClose	//</blockquote>
	;

form
 	:	
		T_Tag T_form {insertar_nodo("body_content","body_tag");
                              insertar_nodo("body_tag","block");
                              insertar_nodo("block","form");
                              insertar_nodo("form","T_form");ultimo_tag="form";}
		{insertar_nodo("form","Atribute");}Atribute	//Atributos de la etiqueta 
		T_TagClose 	//<form>
		{insertar_nodo("form","form_field");}form_field   	//Elementos de la etiqueta <form>
		T_FinalTag T_form T_TagClose	//</form>
	;

form_field	//Elementos del form
	:	INPUT {insertar_nodo("form_field","form_field");}form_field
	| 	select {insertar_nodo("form_field","form_field");}form_field
	| 	textarea {insertar_nodo("form_field","form_field");}form_field
	|	{insertar_nodo("form_field","epsilon");}epsilon
	;

INPUT   :	T_Tag T_input {insertar_nodo("form_field","INPUT");
                               insertar_nodo("INPUT","T_input");ultimo_tag="input";}
		{insertar_nodo("INPUT","Atribute");}Atribute 	//Atributos de la etiqueta
		T_TagClose	//<input>  
	;

select
	:	T_Tag T_select {insertar_nodo("form_field","select");
                                insertar_nodo("select","T_select");ultimo_tag="select";}
		{insertar_nodo("select","Atribute");}Atribute 	//Atributos de la etiqueta
		T_TagClose  	//<select>
		{insertar_nodo("select","select_option");}select_option  	//Opciones del select
		T_FinalTag T_select T_TagClose	//</select>
	;

select_option
	:	T_Tag T_option {insertar_nodo("select_option","T_option");ultimo_tag="option";}
		{insertar_nodo("select_option","Atribute");}Atribute 	//Atributos de la etiqueta
		T_TagClose 	//<option>
		{insertar_nodo("select_option","text");}text 		//Texto dentro de la etiqueta
		T_FinalTag T_option T_TagClose select_option	//</option>
	|	{insertar_nodo("select_option","epsilon");}epsilon	//Puede no tener por lo que deriva en Epsilon
	;

textarea
	:	T_Tag T_textarea {insertar_nodo("form_field","textarea");
                                  insertar_nodo("textarea","T_textarea");ultimo_tag="textarea";}
		{insertar_nodo("textarea","Atribute");}Atribute	//Atributos de la etiqueta 
		T_TagClose  	//<textarea>
		{insertar_nodo("textarea","text");}text 		//Texto dentro de la etiqueta
		T_FinalTag T_textarea T_TagClose	//</textarea>
	;

BR
	:	T_Tag T_br {insertar_nodo("body_content","body_tag");
                            insertar_nodo("body_tag","block");
                            insertar_nodo("block","BR");
                            insertar_nodo("BR","T_br");ultimo_tag="br";}
		{insertar_nodo("BR","Atribute");}Atribute 	//Atributos de la etiqueta
		T_TagClose	//<br> 
	;
HR	:	T_Tag T_hr {insertar_nodo("body_content","body_tag");
                            insertar_nodo("body_tag","block");
                            insertar_nodo("block","HR");
                            insertar_nodo("HR","T_hr");ultimo_tag="hr";}
		{insertar_nodo("HR","Atribute");}Atribute 	//Atributos de la etiqueta
		T_TagClose	//<hr>
	;
IMG	:	T_Tag T_img {insertar_nodo("body_content","body_tag");
                             insertar_nodo("body_tag","block");
                             insertar_nodo("block","IMG");
                             insertar_nodo("IMG","T_img");ultimo_tag="img";}
		{insertar_nodo("IMG","Atribute");}Atribute	//Atributos de la etiqueta 
		T_TagClose	//<img>
	;


table
	:	T_Tag T_table {insertar_nodo("body_content","body_tag");
                               insertar_nodo("body_tag","block");
                               insertar_nodo("block","table");
                               insertar_nodo("table","T_table");ultimo_tag="table";}
		{insertar_nodo("table","Atribute");}Atribute 	//Atributos de la etiqueta
		T_TagClose 	//<table>
		{insertar_nodo("table","caption");}caption 	//caption de la etiqueta <table>
		{insertar_nodo("table","tr");}tr  		//TableRow
		T_FinalTag T_table T_TagClose	//</table>
	;

caption
	:	T_Tag T_caption {insertar_nodo("caption","T_caption");ultimo_tag="caption";}
		{insertar_nodo("caption","Atribute");}Atribute 	//Atributos de la etiqueta
		T_TagClose 	//<caption>
		{insertar_nodo("caption","text");}text 		//Texto dentro de la etiqueta
		T_FinalTag T_caption T_TagClose		//<caption>
	;

tr	:	T_Tag T_tr {insertar_nodo("tr","T_tr");ultimo_tag="tr";}
		{insertar_nodo("tr","Atribute");}Atribute 	//Atributos de la etiqueta
		T_TagClose 	//<tr>
		{insertar_nodo("tr","th_or_td");}th_or_td 	//th or td
		T_FinalTag T_tr T_TagClose tr	//</tr>
	|	epsilon	//Puede no tener por lo que deriva a Epsilon
	;

th_or_td
	:       T_Tag T_th T_TagClose{insertar_nodo("th_or_td","T_th");ultimo_tag="th";} //<th>
		 {insertar_nodo("th_or_td","body_content");}body_content 	//Elementos de contenido
		T_FinalTag T_th T_TagClose //</th>
        |       T_Tag T_td T_TagClose{insertar_nodo("th_or_td","T_td");ultimo_tag="td";} //<td>
		 {insertar_nodo("th_or_td","body_content");}body_content 	//Elementos de contenido
		T_FinalTag T_td T_TagClose //</td>
	;
bold:	        T_Tag T_b T_TagClose {insertar_nodo("body_content","body_tag");
                                      insertar_nodo("body_tag","block");
                                      insertar_nodo("block","bold");
                                      insertar_nodo("bold","T_b");ultimo_tag="b";}//<b>  
		{insertar_nodo("bold","text");}text  //Texto dentro de la etiqueta
		T_FinalTag T_b T_TagClose	//</b>
	;
emphasize
	:	T_Tag T_em T_TagClose {insertar_nodo("body_content","body_tag");
                                       insertar_nodo("body_tag","block");
                                       insertar_nodo("block","emphasize");
                                       insertar_nodo("emphasize","T_em");ultimo_tag="em";}//<embed>
		{insertar_nodo("emphasize","text");}text  	//Texto dentro de la etiqueta
		T_FinalTag T_em T_TagClose	//</embed>
	;

strong
	:	T_Tag T_strong T_TagClose {insertar_nodo("body_content","body_tag");
                                           insertar_nodo("body_tag","block");
                                           insertar_nodo("block","strong");
                                           insertar_nodo("strong","T_strong");ultimo_tag="strong";}	//<strong>
		{insertar_nodo("strong","text ");}text  //Texto dentro de la etiqueta
		T_FinalTag T_strong T_TagClose	//</strong>
	;
code
	:	T_Tag T_code T_TagClose {insertar_nodo("body_content","body_tag");
                                         insertar_nodo("body_tag","block");
                                         insertar_nodo("block","code");
                                         insertar_nodo("code","T_code");ultimo_tag="code";}		//<code> 
		{insertar_nodo("code","text");}text  	//Texto dentro de la etiqueta
		T_FinalTag T_code T_TagClose	//</code>
	;

anchor	
	:	T_Tag T_a {insertar_nodo("body_content","body_tag");
                           insertar_nodo("body_tag","block");
                           insertar_nodo("block","anchor");
                           insertar_nodo("anchor","T_a");ultimo_tag="a";}
		{insertar_nodo("anchor","Atribute");}Atribute	//Atributos de la etiqueta 
		T_TagClose 	//<anchor>
		{insertar_nodo("anchor","text");} text 		//Texto dentro de la etiqueta
		T_FinalTag T_a T_TagClose	//</anchor>
	;
button 
        :	T_Tag T_button {insertar_nodo("body_content","body_tag");
                                insertar_nodo("body_tag","block");
                                insertar_nodo("block","button");
                                insertar_nodo("button","T_button");ultimo_tag="button";}
		{insertar_nodo("button","Atribute");}Atribute 	//Atributos de la etiqueta
		T_TagClose 	//<button>
		{insertar_nodo("button","text");}text 		//Texto dentro de la etiqueta
		T_FinalTag T_button T_TagClose	//<button>
        ;
span 
        :	T_Tag T_span {insertar_nodo("body_content","body_tag");
                              insertar_nodo("body_tag","block");
                              insertar_nodo("block","span");
                              insertar_nodo("span","T_span");ultimo_tag="span";}
		{insertar_nodo("span","Atribute");}Atribute 	//Atributos de la etiqueta
		T_TagClose 	//<span>
		{insertar_nodo("span","text");}text 		//Texto dentro de la etiqueta
		T_FinalTag T_span T_TagClose	//</span>
        ;
embed 
        :	T_Tag T_embed {insertar_nodo("body_content","body_tag");
                               insertar_nodo("body_tag","block");
                               insertar_nodo("block","embed");
                               insertar_nodo("embed","T_embed");ultimo_tag="embed";}
		{insertar_nodo("embed","Atribute");}Atribute 	//Atributos de la etiqueta
		T_TagClose 	//<embed>
		{insertar_nodo("embed","text");}text 		//Texto dentro de la etiqueta
		T_FinalTag T_embed T_TagClose	//<embed>
        ;
object 
        :	T_Tag T_object {insertar_nodo("body_content","body_tag");
                                insertar_nodo("body_tag","block");
                                insertar_nodo("block","object");
                                insertar_nodo("object","T_object");ultimo_tag="object";}
		{insertar_nodo("object","Atribute");}Atribute 	//Atributos de la etiqueta
		T_TagClose 	//<object>
		{insertar_nodo("object","text");}text 		//Texto dentro de la etiqueta
		T_FinalTag T_object T_TagClose	//</embed>
        ;
comment :	T_comment_open {insertar_nodo("body_content","body_tag");
                                insertar_nodo("body_tag","block");
                                insertar_nodo("block","comment");}	//<!-- 
		body_content //Cualquier tipo de contenido
		T_comment_close	//-->
	;

/*******************************FIN DE LOS TAGS DEL BODY****************************************/

text	:	T_IDENT {insertar_nodo("text",yylval.str);}
                {insertar_nodo("text","text");}text	//{insertar_nodo(etiqueta,yylval.str);}//Texto 
	| 	epsilon 	//puede derivar a epsilon
	;

Atribute : 	T_IDENT {insertar_nodo("Atribute",yylval.str);
                         analizar(ultimo_tag,yylval.str,yylineno);}
                {insertar_nodo("Atribute","Atribute");}Atribute 	//Atributo
	|	  epsilon		//puede derivar a epsilon
	;
epsilon :	//Epsilon declarada como una regla solo por comprension
	;
%%
int main(){
/**************PARSING**************/
        i=0;
        Agrega_nodo(&root,"document");
	yyparse();
        if(i==0){
	imprimir_arbol (root);
        liberar_arbol (root);}
        else{
    	liberar_arbol (root);}
	return 0; 
}
/*******************************
Errores Sintacticos
********************************/
yyerror (char *s) {i=1; fprintf(stderr,"Syntax Error at line: %d\n",yylineno);}
