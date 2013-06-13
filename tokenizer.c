#include <stdio.h>
#include <string.h>
/*************************
ANALIZADOR SEMANTICO XHTML
**************************/
/**************************************
Atributos definidos para cada etiqueta
***************************************/
int len;
char *a[] = {"href","name","type"};
char *b[] = {"type","id","class"};
char *blockquote[] = {"cite"};
char *body[] = {"background","bgcolor","text","link"};
char *br[] = {"type","id","class"};
char *button[] = {"type","id","class","name","type","value","disabled","autofocus"};
char *caption[] = {"align"};
char *code[] = {"type","id","class"};
char *footer[] = {"type","id","class"};
char *div[] = {"type","id","class","align"};
char *dl[] = {"type","id","class"};
char *dt[] = {"type","id","class"};
char *dd[] = {"type","id","class"};
char *em[] = {"type","id","class","value"};
char *embed[] = {"type","id","class","height","src","width"};
char *pre[] = {"type","id","class","width"};
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
char *select[] = {"type","id","class","name","size"};
char *table[] = {"type","id","class","bgcolor","border","align","width"};
char *td[] = {"type","id","class","colspan","rowspan","align","bgcolor","height","width"};
char *th[] = {"type","id","class","colspan","rowspan","align","bgcolor","height","width"};
char *title[] = {"type","id","class"};
char *tr[] = {"type","id","class","bgcolor","align"};
char *textarea[] = {"type","id","class","cols","rows","name"};
char *ul[] = {"type","id","class"};
char *script[] = {"src"};


/**********************************
verificar_etiqueta:
Verifica la validez de un atributo
dentro de una etiqueta.
***********************************/
int verificar_atributo(char* etiqueta[],char* atributo,char* nombre){
printf("Lenght of array %d\n",len);
int i = 0;
char *tag;
for(;i<len;i++){
	if(strcmp(atributo,etiqueta[i])==0){
		return 1;//Significa que si es un atributo valido
	}
		
}
printf("AtributeError: La etiqueta '%s' no posee el atributo '%s'\n",nombre,atributo);
return 0 ;//Atributo no valido
}

/************************************
verificar:
Funcion que valida el atributo y
el valor asignado a este atributo,por
medio de funciones auxiliares.
*************************************/
int verificar(char* tag, char* att){
if (strcmp(tag,"a")==0){
	len=(sizeof(a)/sizeof(a[0]));
	verificar_atributo(a,att,"a");}
else if (strcmp(tag,"b")==0){
	len=(sizeof(b)/sizeof(b[0]));
	verificar_atributo(b,att,"b");}
else if (strcmp(tag,"blockquote")==0){
	len=(sizeof(blockquote)/sizeof(blockquote[0]));
	verificar_atributo(blockquote,att,"blockquote");}
else if (strcmp(tag,"body")==0){
	len=(sizeof(body)/sizeof(body[0]));
	verificar_atributo(body,att,"body");}
else if (strcmp(tag,"br")==0){
	len=(sizeof(br)/sizeof(br[0]));
	verificar_atributo(br,att,"br");}
else if (strcmp(tag,"button")==0){
	len=(sizeof(button)/sizeof(button[0]));
	verificar_atributo(button,att,"button");}
else if (strcmp(tag,"caption")==0){
	len=(sizeof(caption)/sizeof(caption[0]));
	verificar_atributo(caption,att,"caption");}
else if (strcmp(tag,"code")==0){
	len=(sizeof(code)/sizeof(code[0]));
	verificar_atributo(code,att,"code");}
else if (strcmp(tag,"footer")==0){
	len=(sizeof(footer)/sizeof(footer[0]));
	verificar_atributo(footer,att,"footer");}
else if (strcmp(tag,"div")==0){
	len=(sizeof(div)/sizeof(div[0]));
	verificar_atributo(div,att,"div");}
else if (strcmp(tag,"dl")==0){
	len=(sizeof(dl)/sizeof(dl[0]));
	verificar_atributo(dl,att,"dl");}
else if (strcmp(tag,"dt")==0){
	len=(sizeof(dt)/sizeof(dt[0]));
	verificar_atributo(dt,att,"dt");}
else if (strcmp(tag,"dd")==0){
	len=(sizeof(dd)/sizeof(dd[0]));
	verificar_atributo(dd,att,"dd");}
else if (strcmp(tag,"em")==0){
	len=(sizeof(em)/sizeof(em[0]));
	verificar_atributo(em,att,"em");}
else if (strcmp(tag,"embed")==0){
	len=(sizeof(embed)/sizeof(embed[0]));
	verificar_atributo(embed,att,"embed");}
else if (strcmp(tag,"pre")==0){
	len=(sizeof(pre)/sizeof(pre[0]));
	verificar_atributo(pre,att,"pre");}
else if (strcmp(tag,"form")==0){
	len=(sizeof(form)/sizeof(form[0]));
	verificar_atributo(form,att,"form");}
else if (strcmp(tag,"headings")==0){
	len=(sizeof(headings)/sizeof(headings[0]));
	verificar_atributo(headings,att,"headings");}
else if (strcmp(tag,"head")==0){
	len=(sizeof(head)/sizeof(head[0]));
	verificar_atributo(head,att,"head");}
else if (strcmp(tag,"header")==0){
	len=(sizeof(header)/sizeof(header[0]));
	verificar_atributo(header,att,"header");}
else if (strcmp(tag,"hr")==0){
	len=(sizeof(hr)/sizeof(hr[0]));
	verificar_atributo(hr,att,"hr");}
else if (strcmp(tag,"html")==0){
	len=(sizeof(html)/sizeof(html[0]));
	verificar_atributo(html,att,"html");}
else if (strcmp(tag,"img")==0){
	len=(sizeof(img)/sizeof(img[0]));
	verificar_atributo(img,att,"img");}
else if (strcmp(tag,"input")==0){
	len=(sizeof(input)/sizeof(input[0]));
	verificar_atributo(input,att,"input");}
else if (strcmp(tag,"li")==0){
	len=(sizeof(li)/sizeof(li[0]));
	verificar_atributo(li,att,"li");}
else if (strcmp(tag,"link")==0){
	len=(sizeof(link)/sizeof(link[0]));
	verificar_atributo(link,att,"link");}
else if (strcmp(tag,"meta")==0){
	len=(sizeof(meta)/sizeof(meta[0]));
	verificar_atributo(meta,att,"meta");}
else if (strcmp(tag,"object")==0){
	len=(sizeof(object)/sizeof(object[0]));
	verificar_atributo(object,att,"object");}
else if (strcmp(tag,"ol")==0){
	len=(sizeof(ol)/sizeof(ol[0]));
	verificar_atributo(ol,att,"ol");}
else if (strcmp(tag,"option")==0){
	len=(sizeof(option)/sizeof(option[0]));
	verificar_atributo(option,att,"option");}
else if (strcmp(tag,"p")==0){
	len=(sizeof(p)/sizeof(p[0]));
	verificar_atributo(p,att,"p");}
else if (strcmp(tag,"span")==0){
	len=(sizeof(span)/sizeof(span[0]));
	verificar_atributo(span,att,"span");}
else if (strcmp(tag,"strong")==0){
	len=(sizeof(strong)/sizeof(strong[0]));
	verificar_atributo(strong,att,"strong");}
else if (strcmp(tag,"style")==0){
	len=(sizeof(style)/sizeof(style[0]));
	verificar_atributo(style,att,"style");}
else if (strcmp(tag,"select")==0){
	len=(sizeof(select)/sizeof(select[0]));
	verificar_atributo(select,att,"select");}
else if (strcmp(tag,"table")==0){
	len=(sizeof(table)/sizeof(table[0]));
	verificar_atributo(table,att,"table");}
else if (strcmp(tag,"td")==0){
	len=(sizeof(td)/sizeof(td[0]));
	verificar_atributo(td,att,"td");}
else if (strcmp(tag,"th")==0){
	len=(sizeof(th)/sizeof(th[0]));
	verificar_atributo(th,att,"th");}
else if (strcmp(tag,"title")==0){
	len=(sizeof(title)/sizeof(title[0]));
	verificar_atributo(title,att,"title");}
else if (strcmp(tag,"tr")==0){
	len=(sizeof(tr)/sizeof(tr[0]));
	verificar_atributo(tr,att,"tr");}
else if (strcmp(tag,"textarea")==0){
	len=(sizeof(textarea)/sizeof(textarea[0]));
	verificar_atributo(textarea,att,"textarea");}
else if (strcmp(tag,"ul")==0){
	len=(sizeof(ul)/sizeof(ul[0]));
	verificar_atributo(ul,att,"ul");}
else if (strcmp(tag,"script")==0){
	len=(sizeof(script)/sizeof(script[0]));
	verificar_atributo(script,att,"script");}
else{ 
	printf("Etiqueta invalida\n");
	return 0;}


}

/************************************
analizar:
Funcion principal que controla el
analisis semantico.
*************************************/
int analizar(char* tag, char* attr ){
char *atributo;
char *valor;
atributo = strtok(attr, "=");
//VERIFICAMOS QUE EL ATRIBUTO SEA VALIDO PARA ESE TAG
verificar(tag,attr);
//LUEGO SI PASA ESTA PRUEBA VALIDAMOS EL VALOR DEL ATRIBUTO
valor = strtok(NULL,  " ,");
}

int main() {
char var[]= "src=\"scripts/preloadImages.js\"";
char var1[]= "rel=\"stylesheet\"";
char var2[]= "name=\"opcion\"";
char var3[]= "href=\"http//www.facebook.com\"";
char var4[]= "type=\"text/css\"";
char var5[]= "nam=\"description\"";
analizar("script",var);
analizar("link",var1);
//analizar("select",var2);
//analizar("a",var3);
//analizar("style",var4);
//analizar("meta",var5);
return 0;
}
