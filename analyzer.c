/*********************************
Insitituto Tecnologico de Costa Rica
Compiladores e Interpretes
Alexis Boza 
Silvia Delgado
2013
**********************************/
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <regex.h>
/*************************
ANALIZADOR SEMANTICO XHTML
**************************/
/**************************************
Atributos definidos para cada etiqueta
***************************************/
int len;//len de un los arreglos de los atributos
int len_v;//len de un los arreglos de los valores
int n_linea;
char *a[] = {"href","name","type","shape"};
char *b[] = {"type","id","class"};//******
char *blockquote[] = {"cite"};
char *body[] = {"background","bgcolor","text","link"};
char *br[] = {"type","id","class"};//*****
char *button[] = {"type","name","value","disabled","autofocus"};
char *caption[] = {"align"};//no lo soporta html5
char *code[] = {"type","id","class"};//*******
char *footer[] = {"type","id","class"};
char *div_[] = {"type","id","class","align"};
char *dl[] = {"type","id","class"};//*****
char *dt[] = {"type","id","class"};//*****
char *dd[] = {"type","id","class"};//*****
char *em[] = {"type","id","class","value"};//*****
char *embed[] = {"type","id","class","height","src","width"};
char *pre[] = {"type","id","class","width"};//no lo soporta html5
char *form[] = {"type","id","class","action","method","name"};
char *headings[] = {"type","id","class","align"};//h1-h6
char *head[] = {"type","id","class"};
char *header[] = {"type","id","class"};
char *hr[] = {"type","id","class","align","size","width"};
char *html[] = {"type","id","class","xmlns"};
char *img[] = {"type","id","class","align","height","src","width"};
char *input[] = {"type","id","class","height","name","size","src","value","width"};
char *li[] = {"type","id","class","value"};
char *link[] = {"type","id","class","href","rel"};
char *meta[] = {"type","id","class","name","content"};
char *object[] = {"type","id","class","align","name","heigh","width"};
char *ol[] = {"type","id","class","start"};
char *option[] = {"type","id","class","value"};
char *p[] = {"type","id","class","align"};
char *span[] = {"type","id","class"};
char *strong[] = {"type","id","class"};
char *style[] = {"type","id","class"};
char *select_[] = {"type","id","class","name","size"};
char *table[] = {"type","id","class","bgcolor","border","align","width"};
char *td[] = {"type","id","class","colspan","rowspan","align","bgcolor","height","width"};
char *th[] = {"type","id","class","colspan","rowspan","align","bgcolor","height","width"};
char *title[] = {"type","id","class"};
char *tr[] = {"type","id","class","bgcolor","align"};
char *textarea[] = {"type","id","class","cols","rows","name"};
char *ul[] = {"type","id","class"};
char *script[] = {"src","type"};

// valores de los atributos globales

char *shape[] = {"default","rect","circle","poly"}; // no lo soporta html5
char *disabled[] = {"disabled"};
char *autofocus[] = {"autofocus"};
char *type_button[] = {"button","reset","submit "};//****
char *method[] = {"get","post"};
char *xmlns[] = {"http://www.w3.org/1999/xhtml"};
char *type_input[] = {"button","checkbox","color","date","datetime","datetime-local","email","file",
"hidden","image","month","number","password","radio","range","reset","search","submit","tel","text",
"time","url","week"};
char *type_li[] = {"1","A","a","I","i","disc","square","circle"};
char *rel[] = {"alternate","archives","author","bookmark","external","first","help","icon","last",
"license","next","nofollow","noreferrer","pingback","prefetch","prev","search","sidebar","stylesheet","tag","up"};
char *border[] = {"1",""};
char *align[] = {"left","right","top","bottom","middle","center","justify"};
char *type_style[] = {"text/css"};
char* color[]={"Black","#000000","Green","#008000","Silver","#C0C0C0","Lime","#00FF00","Gray","#808080","Olive","#808000","White","#FFFFFF",
"Yellow","#FFFF00","Maroon","#800000","Navy","#000080","Red","#FF0000","Blue","#0000FF","Purple","#800080","Teal","#008080","Fuchsia",
"#FF00FF","Aqua","#00FFFF"};

/************************+
Funcion que ve el numero de match deacuerdo a la expresion regularbbbbbb
/*************************/
int match(regex_t *pexp, char *sz) {
  regmatch_t matches[1]; 
	if (regexec(pexp, sz, 1, matches, 0) == 0) {
		//printf("\"%s\" caracteres que coinciden: %d - %d\n", sz, matches[0].rm_so, matches[0].rm_eo);
                return 1;
	} else {
		//printf("\"%s\" no coincide :\n", sz);
                return 0;
	}
}
 
/************************+
Validar que solo sean numeros con expresion regular
/**************************/
int numero(char* att,char * expresion){
  int rv;
  int flag;
  regex_t exp; 
  rv = regcomp(&exp, "[0-9]{1,9}(.[0-9]{0,2})?$", REG_EXTENDED);//expresion regular
	if (rv != 0) {
		printf("regcomp failed with %d\n", rv);
	}
	flag=match(&exp, expresion);
     if(flag!=0) return 1;
     else {printf("Error de semántica en la línea %i : El valor '%s' no corresponde al atributo '%s'.\n",n_linea,expresion,att);return 0;}

}

/************************+
Validar que sea URL con expresion regular
/**************************/
int url(char* att,char * expresion){
   int rv;
  int flag;
  regex_t exp; 
  rv = regcomp(&exp, "((ftp|http|https)://)?[a-z,A-Z,0-9,.,:,/,-,_,@,=,#]+[.com]?(/[a-z,A-Z,0-9,.,:,/,-,_,@,=,#]+)?", REG_EXTENDED);//expresion regular
	if (rv != 0) {
		printf("regcomp failed with %d\n", rv);
	}
	flag=match(&exp, expresion);
     if(flag!=0){ return 1;}
     else {printf("Error de semántica en la línea %i: El valor '%s' no corresponde al atributo '%s'.\n",n_linea,expresion,att);return 0;}
}

/************************+
Validar que sean pixeles con expresion regular
/**************************/
int pixels(char* att,char * expresion){
   int rv;
  int flag;
  regex_t exp; 
  rv = regcomp(&exp, "[0-9]{1,9}(.[0-9]{0,2})?$", REG_EXTENDED);//expresion regular
	if (rv != 0) {
		printf("regcomp failed with %d\n", rv);
	}
	flag=match(&exp, expresion);
     if(flag!=0) return 1;
     else {printf("Error de semántica en la línea %i : El valor '%s' no corresponde al atributo '%s'.\n",n_linea,expresion,att);return 0;}
}

/************************+
Validar que sea un nombre o texto 
/**************************/
int texto(char* att,char * expresion){
   int rv;
  int flag;
  regex_t exp; 
  rv = regcomp(&exp, "[a-zA-ZñÑ/]+", REG_EXTENDED);//expresion regular
	if (rv != 0) {
		printf("regcomp failed with %d\n", rv);
	}
	flag=match(&exp, expresion);
     if(flag!=0) return 1;
     else {printf("Error de semántica en la línea %i : El valor '%s' no corresponde al atributo '%s'.\n",n_linea,expresion,att);return 0;}
}

/**********************************
verificar_etiqueta:
Verifica la validez de un atributo
dentro de una etiqueta.
***********************************/
int verificar_atributo(char* etiqueta[],char* atributo,char* nombre/*,int n_linea*/){
//printf("Lenght of array %d\n",len);
int i = 0;
char *tag;
for(;i<len;i++){
	if(strcmp(atributo,etiqueta[i])==0){
		return 1;//Significa que si es un atributo valido
	}
		
}
printf("Error de semántica en la línea %i : La etiqueta '%s' no posee el atributo '%s'.\n",n_linea,nombre,atributo);
return 0 ;//Atributo no valido
}
/**********************************
verificar_valor:
Verifica la validez de un valor
para un atributo
***********************************/
int verificar_valor(char* etiqueta[],char* valor,char* nombre/*,int n_linea*/){
//printf("Lenght of array %d\n",len);
int i = 0;
char *tag;
for(;i<len_v;i++){
	if(strcmp(valor,etiqueta[i])==0){
		return 1;//Significa que si es un atributo valido
	}
		
}
printf("Error de semántica en la línea %i : El valor '%s' no corresponde al atributo '%s'.\n",n_linea,valor,nombre);
return 0 ;//Atributo no valido
}
/************************************
verificar:
Funcion que valida el atributo y
el valor asignado a este atributo,por
medio de funciones auxiliares.
*************************************/
void verificar(char* tag, char* att,char* valor){
int atr;
if (strcmp(tag,"a")==0){
	len=(sizeof(a)/sizeof(a[0]));
	atr=verificar_atributo(a,att,"a");
        if(atr==1){
             if(strcmp(att,"href")==0)
                  url(att,valor);
             else if(strcmp(att,"shape")==0){
                  len_v=(sizeof(shape)/sizeof(shape[0]));
                  verificar_valor(shape,valor,"shape"); }
             else texto(att,valor);// acepta los valores de los atributos generales , que son texto "type","id","class"
}}
else if (strcmp(tag,"b")==0){
	len=(sizeof(b)/sizeof(b[0]));
	atr=verificar_atributo(b,att,"b");
        if(atr==1){
             texto(att,valor);// acepta los valores de los atributos generales , que son texto "type","id","class"
             }}
else if (strcmp(tag,"blockquote")==0){
	len=(sizeof(blockquote)/sizeof(blockquote[0]));
	atr=verificar_atributo(blockquote,att,"blockquote");
	if(atr==1){
             url(att,valor); //cite ->url
             }}
else if (strcmp(tag,"body")==0){
	len=(sizeof(body)/sizeof(body[0]));
	atr=verificar_atributo(body,att,"body");
        if(atr==1){
	len_v=(sizeof(color)/sizeof(color[0]));
        verificar_valor(color,valor,att);}}
else if (strcmp(tag,"br")==0){
	len=(sizeof(br)/sizeof(br[0]));
	atr=verificar_atributo(br,att,"br");
        if(atr==1){
	     texto(att,valor);// acepta los valores de los atributos generales , que son texto "type","id","class"
}}
else if (strcmp(tag,"button")==0){
	len=(sizeof(button)/sizeof(button[0]));
	atr=verificar_atributo(button,att,"button");
	if(atr==1){
             if(strcmp(att,"disabled")==0){
                  len_v=(sizeof(disabled)/sizeof(disabled[0]));
                  verificar_valor(disabled,valor,"disabled");}
	     else if(strcmp(att,"autofocus")==0){
                  len_v=(sizeof(autofocus)/sizeof(autofocus[0]));
                  verificar_valor(autofocus,valor,"autofocus");}
             else texto(att,valor);  // acepta los valores de los atributos generales , que son texto "type","id","class"
}}
else if (strcmp(tag,"caption")==0){
	len=(sizeof(caption)/sizeof(caption[0]));
	atr=verificar_atributo(caption,att,"caption");
        if(atr==1){
	len_v=(sizeof(align)/sizeof(align[0]));
        verificar_valor(align,valor,"align");}}
else if (strcmp(tag,"code")==0){
	len=(sizeof(code)/sizeof(code[0]));
	atr=verificar_atributo(code,att,"code");
        if(atr==1){
	     texto(att,valor);// acepta los valores de los atributos generales , que son texto "type","id","class"
}}
else if (strcmp(tag,"footer")==0){
	len=(sizeof(footer)/sizeof(footer[0]));
	atr=verificar_atributo(footer,att,"footer");
  if(atr==1){
	     texto(att,valor);
}}
else if (strcmp(tag,"div")==0){
	len=(sizeof(div_)/sizeof(div_[0]));
	atr=verificar_atributo(div_,att,"div");
        if(atr==1){
           if(strcmp(att,"align")==0 ){
                  len_v=(sizeof(align)/sizeof(align[0]));
                  verificar_valor(align,valor,"align");}
             else texto(att,valor);  // acepta los valores de los atributos generales , que son texto "type","id","class"
}}
else if (strcmp(tag,"dl")==0){
	len=(sizeof(dl)/sizeof(dl[0]));
	atr=verificar_atributo(dl,att,"dl");
         if(atr==1){
	     texto(att,valor);// acepta los valores de los atributos generales , que son texto "type","id","class"
}}
else if (strcmp(tag,"dt")==0){
	len=(sizeof(dt)/sizeof(dt[0]));
	atr=verificar_atributo(dt,att,"dt");
         if(atr==1){
	     texto(att,valor);// acepta los valores de los atributos generales , que son texto "type","id","class"
}}
else if (strcmp(tag,"dd")==0){
	len=(sizeof(dd)/sizeof(dd[0]));
	atr=verificar_atributo(dd,att,"dd");
         if(atr==1){
	     texto(att,valor);// acepta los valores de los atributos generales , que son texto "type","id","class"
}}
else if (strcmp(tag,"em")==0){
	len=(sizeof(em)/sizeof(em[0]));
	atr=verificar_atributo(em,att,"em");
          if(atr==1){
	     texto(att,valor);// acepta los valores de los atributos generales , que son texto "type","id","class"
}}
else if (strcmp(tag,"embed")==0){
	len=(sizeof(embed)/sizeof(embed[0]));
	atr=verificar_atributo(embed,att,"embed");
       if(atr==1){
            if(strcmp(att,"height")==0 | strcmp(att,"width")==0 )
                  pixels(att,valor);
             else if(strcmp(att,"src")==0)
                  url(att,valor);
	     else texto(att,valor);// acepta los valores de los atributos generales , que son texto "type","id","class"
}}
else if (strcmp(tag,"pre")==0){
	len=(sizeof(pre)/sizeof(pre[0]));
	atr=verificar_atributo(pre,att,"pre");
        if(atr==1){
            if(strcmp(att,"width")==0 )
                  pixels(att,valor);
             else 
                  texto(att,valor);// acepta los valores de los atributos generales , que son texto "type","id","class"

}}
else if (strcmp(tag,"form")==0){
	len=(sizeof(form)/sizeof(form[0]));
	atr=verificar_atributo(form,att,"form");
	if(atr==1){
            if(strcmp(att,"method")==0 ){
                  len_v=(sizeof(method)/sizeof(method[0]));
                  verificar_valor(method,valor,"method");}
             else if(strcmp(att,"action")==0)
                  url(att,valor);
	     else texto(att,valor); // acepta los valores de los atributos generales , que son texto "type","id","class"
}}
else if (strcmp(tag,"headings")==0){
	len=(sizeof(headings)/sizeof(headings[0]));
	atr=verificar_atributo(headings,att,"headings");
         if(atr==1){
           if(strcmp(att,"align")==0 ){
                  len_v=(sizeof(align)/sizeof(align[0]));
                  verificar_valor(align,valor,"align");}
             else {
			texto(att,valor); // acepta los valores de los atributos generales , que son texto "type","id","class"
                  }
}}
else if (strcmp(tag,"head")==0){
	len=(sizeof(head)/sizeof(head[0]));
	atr=verificar_atributo(head,att,"head");
        if(atr==1){
	     texto(att,valor); // acepta los valores de los atributos generales , que son texto "type","id","class"
}}
else if (strcmp(tag,"header")==0){
	len=(sizeof(header)/sizeof(header[0]));
	atr=verificar_atributo(header,att,"header");
        if(atr==1){
	     texto(att,valor); // acepta los valores de los atributos generales , que son texto "type","id","class"
}}
else if (strcmp(tag,"hr")==0){
	len=(sizeof(hr)/sizeof(hr[0]));
	atr=verificar_atributo(hr,att,"hr");
        if(atr==1){
             if(strcmp(att,"size")==0 | strcmp(att,"width")==0  )
                   pixels(att,valor);
           else if(strcmp(att,"align")==0 ){
                  len_v=(sizeof(align)/sizeof(align[0]));
                  verificar_valor(align,valor,"align");}
             else texto(att,valor);  // acepta los valores de los atributos generales , que son texto "type","id","class"
}}
else if (strcmp(tag,"html")==0){
	len=(sizeof(html)/sizeof(html[0]));
	atr=verificar_atributo(html,att,"html");
        if(atr==1){
           if(strcmp(att,"xmlns")==0 ){
                  len_v=(sizeof(xmlns)/sizeof(xmlns[0]));
                  verificar_valor(xmlns,valor,"xmlns");}
             else texto(att,valor); // acepta los valores de los atributos generales , que son texto "type","id","class"
}}
else if (strcmp(tag,"img")==0){
	len=(sizeof(img)/sizeof(img[0]));
	atr=verificar_atributo(img,att,"img");
        if(atr==1){
             if(strcmp(att,"align")==0){
                  len_v=(sizeof(align)/sizeof(align[0]));
                  verificar_valor(align,valor,"align");}
             else if(strcmp(att,"height")==0 | strcmp(att,"width")==0)
                  pixels(att,valor);
             else if(strcmp(att,"src")==0)
                   url(att,valor);
             else  texto(att,valor);  // acepta los valores de los atributos generales , que son texto "type","id","class"   
 }}
else if (strcmp(tag,"input")==0){
	len=(sizeof(input)/sizeof(input[0]));
	atr=verificar_atributo(input,att,"input");
         if(atr==1){
            if(strcmp(att,"height")==0 | strcmp(att,"width")==0 | strcmp(att,"size")==0)
                  pixels(att,valor);
             else if(strcmp(att,"src")==0)
                   url(att,valor);
             else  texto(att,valor);     // acepta los valores de los atributos generales , que son texto "type","id","class"
 }}
else if (strcmp(tag,"li")==0){
	len=(sizeof(li)/sizeof(li[0]));
	atr=verificar_atributo(li,att,"li");
           if(atr==1){
	     texto(att,valor);// acepta los valores de los atributos generales , que son texto "type","id","class"
}}
else if (strcmp(tag,"link")==0){
	len=(sizeof(link)/sizeof(link[0]));
	atr=verificar_atributo(link,att,"link");
        if(atr==1){
            if(strcmp(att,"href")==0)
                  url(att,valor);
             else if(strcmp(att,"rel")==0) {
                   len_v=(sizeof(rel)/sizeof(rel[0]));
                  verificar_valor(rel,valor,"rel");}
             else  texto(att,valor);  // acepta los valores de los atributos generales , que son texto "type","id","class" 
}}
else if (strcmp(tag,"meta")==0){
	len=(sizeof(meta)/sizeof(meta[0]));
	atr=verificar_atributo(meta,att,"meta");
       if(atr==1){
	     texto(att,valor);// acepta los valores de los atributos generales , que son texto "type","id","class"
}}
else if (strcmp(tag,"object")==0){
	len=(sizeof(object)/sizeof(object[0]));
	atr=verificar_atributo(object,att,"object");
        if(atr==1){
             if(strcmp(att,"hight")==0 | strcmp(att,"width")==0  )
                   pixels(att,valor);
           else if(strcmp(att,"align")==0 ){
                  len_v=(sizeof(align)/sizeof(align[0]));
                  verificar_valor(align,valor,"align");}
             else texto(att,valor);// acepta los valores de los atributos generales , que son texto "type","id","class"
}}
else if (strcmp(tag,"ol")==0){
	len=(sizeof(ol)/sizeof(ol[0]));
	atr=verificar_atributo(ol,att,"ol");
        if(atr==1){
           if(strcmp(att,"start")==0 )
                  numero(att,valor);
             else texto(att,valor);  // acepta los valores de los atributos generales , que son texto "type","id","class"
}}
else if (strcmp(tag,"option")==0){
	len=(sizeof(option)/sizeof(option[0]));
	atr=verificar_atributo(option,att,"option");
        if(atr==1){
	     texto(att,valor);// acepta los valores de los atributos generales , que son texto "type","id","class"
}}
else if (strcmp(tag,"p")==0){
	len=(sizeof(p)/sizeof(p[0]));
	atr=verificar_atributo(p,att,"p");
        if(atr==1){
           if(strcmp(att,"align")==0 ){
                  len_v=(sizeof(align)/sizeof(align[0]));
                  verificar_valor(align,valor,"align");}
             else texto(att,valor);  // acepta los valores de los atributos generales , que son texto "type","id","class"
}}
else if (strcmp(tag,"span")==0){
	len=(sizeof(span)/sizeof(span[0]));
	atr=verificar_atributo(span,att,"span");
        if(atr==1){
	     texto(att,valor);   // acepta los valores de los atributos generales , que son texto "type","id","class"
}}
else if (strcmp(tag,"strong")==0){
	len=(sizeof(strong)/sizeof(strong[0]));
	atr=verificar_atributo(strong,att,"strong");
        if(atr==1){
	     texto(att,valor);   // acepta los valores de los atributos generales , que son texto "type","id","class"
}}
else if (strcmp(tag,"style")==0){
	len=(sizeof(style)/sizeof(style[0]));
	atr=verificar_atributo(style,att,"style");
        if(atr==1){
	     texto(att,valor);
}}
else if (strcmp(tag,"select")==0){
	len=(sizeof(select_)/sizeof(select_[0]));
	atr=verificar_atributo(select_,att,"select");
        if(atr==1){
           if(strcmp(att,"size")==0 )
                  pixels(att,valor);                  
             else texto(att,valor);   // acepta los valores de los atributos generales , que son texto "type","id","class"
}}
else if (strcmp(tag,"table")==0){
	len=(sizeof(table)/sizeof(table[0]));
	atr=verificar_atributo(table,att,"table");
        if(atr==1){
             if(strcmp(att,"bgcolor")==0){
                  len_v=(sizeof(color)/sizeof(color[0]));
                  verificar_valor(color,valor,"bgcolor"); }
             else if(strcmp(att,"border")==0){
                  len_v=(sizeof(border)/sizeof(border[0]));
                  verificar_valor(border,valor,"border"); }
             else if(strcmp(att,"align")==0){
                  len_v=(sizeof(align)/sizeof(align[0]));
                  verificar_valor(align,valor,"align"); }
             else if(strcmp(att,"width")==0)
                   pixels(att,valor);
             else texto(att,valor);// acepta los valores de los atributos generales , que son texto "type","id","class"
}}
else if (strcmp(tag,"td")==0){
	len=(sizeof(td)/sizeof(td[0]));
	atr=verificar_atributo(td,att,"td");
        if(atr==1){
             if(strcmp(att,"colspan")==0 | strcmp(att,"rowspan")==0){
                  numero(att,valor); }
             else if(strcmp(att,"bgcolor")==0){
                  len_v=(sizeof(color)/sizeof(color[0]));
                  verificar_valor(color,valor,"bgcolor"); }
             else if(strcmp(att,"align")==0){
                  len_v=(sizeof(align)/sizeof(align[0]));
                  verificar_valor(align,valor,"align"); }
             else if(strcmp(att,"width")==0 | strcmp(att,"height")==0)
                   pixels(att,valor);
             else texto(att,valor);// acepta los valores de los atributos generales , que son texto "type","id","class"
}}
else if (strcmp(tag,"th")==0){
	len=(sizeof(th)/sizeof(th[0]));
	atr=verificar_atributo(th,att,"th");
        if(atr==1){
             if(strcmp(att,"colspan")==0 | strcmp(att,"rowspan")==0){
                  numero(att,valor); }
             else if(strcmp(att,"bgcolor")==0){
                  len_v=(sizeof(color)/sizeof(color[0]));
                  verificar_valor(color,valor,"bgcolor"); }
             else if(strcmp(att,"align")==0){
                  len_v=(sizeof(align)/sizeof(align[0]));
                  verificar_valor(align,valor,"align"); }
             else if(strcmp(att,"width")==0 | strcmp(att,"height")==0)
                   pixels(att,valor);
             else texto(att,valor);// acepta los valores de los atributos generales , que son texto "type","id","class"
}}
else if (strcmp(tag,"title")==0){
	len=(sizeof(title)/sizeof(title[0]));
	atr=verificar_atributo(title,att,"title");
        if(atr==1){
	     texto(att,valor);
}}
else if (strcmp(tag,"tr")==0){
	len=(sizeof(tr)/sizeof(tr[0]));
	atr=verificar_atributo(tr,att,"tr");
         if(atr==1){
           if(strcmp(att,"bgcolor")==0 ){
                  len_v=(sizeof(color)/sizeof(color[0]));
                  verificar_valor(color,valor,"bgcolor"); }
             else texto(att,valor);  // acepta los valores de los atributos generales , que son texto "type","id","class"
}}
else if (strcmp(tag,"textarea")==0){
	len=(sizeof(textarea)/sizeof(textarea[0]));
	atr=verificar_atributo(textarea,att,"textarea");
        if(atr==1){
           if(strcmp(att,"cols")==0 | strcmp(att,"rows")==0)
                  numero(att,valor);
             else texto(att,valor);// acepta los valores de los atributos generales , que son texto "type","id","class"
}}
else if (strcmp(tag,"ul")==0){
	len=(sizeof(ul)/sizeof(ul[0]));
	atr=verificar_atributo(ul,att,"ul");
        if(atr==1){
	     texto(att,valor);// acepta los valores de los atributos generales , que son texto "type","id","class"
}}
else if (strcmp(tag,"script")==0){
	len=(sizeof(script)/sizeof(script[0]));
	atr=verificar_atributo(script,att,"script");
        if(atr==1){
	     url(att,valor);
}}
else{ 
	printf("Etiqueta invalida\n");
	}


}

/************************************
analizar:
Funcion principal que controla el
analisis semantico.
*************************************/
int analizar(char* tag, char* attr,int n_line){
	char *atributo;
	char *valor;
        n_linea=n_line;
	atributo = strtok(attr, "=");
	//VERIFICAMOS QUE EL ATRIBUTO SEA VALIDO PARA ESE TAG
	//verificar(tag,attr);
	//LUEGO SI PASA ESTA PRUEBA VALIDAMOS EL VALOR DEL ATRIBUTO
	valor = strtok(NULL,  "\"\"");
	 verificar(tag,attr,valor);
}

/*int main() {
char var[]= "src=\"scripts/preloadImages.js\"";
char var1[]= "rel=\"stylesheet\"";
char var2[]= "name=\"opcion\"";
char var3[]= "href=\"http://www.facebook.com\"";
char var4[]= "type=\"text/css\"";
char var5[]= "name=\"description\"";
analizar("script",var);
analizar("link",var1);
analizar("select",var2);
analizar("a",var3);
analizar("style",var4);
analizar("meta",var5);
return 0;
}*/
