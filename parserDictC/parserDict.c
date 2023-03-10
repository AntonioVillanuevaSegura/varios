/*Antonio Villanueva Segura
* on a un fichier externe type {key}:{value} \n 
* p.e
* LOGIN :axiome
* PASWORD:concept
* {key}:{value}
* 
* Tout d'abord  on filtre les caractères indésirables space,tabulations ..filter(char *str)
* et nous voulons filtrer pour récupérer les clés{KEY} et les valeurs{VALUE}
* Ensuite, on peut demander  getValue(char *ligne) && getKey(char *ligne) dans chaque ligne
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Fichier avec structure de dictionnaire {key}:{value}
#define FICHIER "data.txt"
#define LONGUEUR_MAX 64 //Longueur maximale d'une ligne à lire

//Structure de base type dictionnaire
struct dict{
	char key[64];
	char value[64];
};

char* isCommentaire(char *src){
// La ligne doit contenir deux points pour être de type {key} :{value}
// et une longueur minimale key:value a:1 == strlen -> 3	
	if (strlen(src)<3 ){return NULL;}
	return strrchr (src,':');
}

void filter(char *str){
	//Filtrer les caractères inférieurs à l'espace
	if ( isCommentaire (str) == NULL){
		*str='\0';
		return;
	}
	char* src = str;
	char* dst = str;

	while (*src != '\0') {//n'a pas atteint la fin ?

		if (*src >0x20) {//Filter caractères inferieurs à l'espace 0x20
		  *dst = *src;
		  dst++;
		}
		src++;//src en dernière position
	}
	*dst = '\0';//ajoute fin de chaîne
	src=dst;
	
}

char* getValue(char *ligne,char *dst){
	//Dans un système {key}:{value} renvoie "value" ...et dst
	if (strlen(ligne)<3 && ligne!=NULL){return NULL;}
	char *src=strchr ( ligne , ':' );//commence après le côlon	
	src++;//:
	while (( *src != '\0') && (*src != '\n')){
		*dst = *src;//copie le contenu de src vers dst
		dst++;
		src++;
	} 

	//*dst='\0';
	*dst=0;	
	return dst;
}

char* getKey(char *ligne,char *dst){
	//Dans un système {key}:{value} renvoie "key" ..et dst
	if (strlen(ligne)<3 && ligne!=NULL){return NULL;}
	char *src=ligne;
	while ((*src != ':') && ( *src != '\0') && (*src != '\n')){
		*dst = *src;
		dst++;
		src++;
	} 

	//*dst='\0';
	*dst=0;		
	return dst;
}

void printDict (struct dict *ptr,int longueur){
	//Imprime le tableau de type de dictionnaire {key}:{value}
	for (int i=0;i<longueur;i++){			
		printf ("%d {key} %s = %s {value} \n",i,ptr->key, ptr->value);
		ptr++;
	}
}


int main() {
	
	FILE *fptr;
		
	int lignes=0;//nombre de lignes avec information  {key}:{value}
    char ligne[LONGUEUR_MAX]; //Ligne lue depuis le fichier externe
    char key[64];//chaîne temporaire pour lire une clé {key}
    char value[64];//chaîne temporaire pour lire un valeur {value}

    
	//Ouverture du fichier
	if( (fptr = fopen(FICHIER,"r")) == NULL)//ouvrir le fichier en lecture
	{
	  printf("Error! %s",FICHIER);   
	  exit(1);             
	}	
	
	
	//Analyse des nombres des lignes de dictionnaire
	while (fgets(ligne, LONGUEUR_MAX, fptr)){ //lire une ligne	
		filter(ligne);
		if (strrchr (ligne,':')!=NULL){lignes++;}
	}
	
	
	struct dict base[lignes];//Crée le dictionnaire
	
	//printf ("Nombre de lignes %d" ,lignes);//DEBUG nombre de lignes
	rewind(fptr);//Rembobiner le fichier

	
	int index=0;    
	while (fgets(ligne, LONGUEUR_MAX, fptr)){ //lire une ligne	
		
		filter(ligne);//Nettoyage ligne spaces,tabs ,commentaires .. etc 
		
		if (strrchr (ligne,':')!=NULL){//C'est une ligne de type {key} :{value} ?
			
			//memset(key,0,strlen(key));//key[0]='\0' RESET 
			//memset(value,0,strlen(value));//value[0]='\0'	

			//Get {Key}: {value}
			getKey(ligne,(char *)&key);
			getValue(ligne,(char *) &value);
			
			
			//memset(base[index].key,0,64);//key[0]='\0'
			//memset(base[index].value,0,64);//value[0]='\0'				
					
			//Copie la clé{key} et la valeur{value} dans la structure
			strcpy (base[index].key, key);	//memcpy(dest, org ,strlen(org));	
			strcpy (base[index].value, value);//memcpy(dest, org ,strlen(org));			

			index++;//Nouvel index dans la structure du dictionnaire	
		}
	
	}
    
    
    printf ("Num. lignes %d \n",lignes);
	printDict (base,lignes);
	
	fclose(fptr);//fermeture FICHIER 	
    return EXIT_SUCCESS;
}
