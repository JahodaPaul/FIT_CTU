#include <stdio.h>
#include <string.h>
#include <iostream>
#include <openssl/evp.h>
#include <string>

char pole[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
 
int main(int argc, char *argv[]){

  char text[] = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
  

  int i;
  
  char hashFunction[] = "sha256";  // zvolena hashovaci funkce ("sha1", "md5" ...)
 
  EVP_MD_CTX ctx;  // struktura kontextu
  const EVP_MD *type; // typ pouzite hashovaci funkce
  unsigned char hash[EVP_MAX_MD_SIZE]; // char pole pro hash - 64 bytu (max pro sha 512)
  int length;  // vysledna delka hashe
 
  /* Inicializace OpenSSL hash funkci */
  OpenSSL_add_all_digests();
  /* Zjisteni, jaka hashovaci funkce ma byt pouzita */
  type = EVP_get_digestbyname(hashFunction);
 
  /* Pokud predchozi prirazeni vratilo -1, tak nebyla zadana spravne hashovaci funkce */
  if(!type) {
    printf("Hash %s neexistuje.\n", hashFunction);
    exit(1);
  }
  for(int j=0;j<100000000;j++){

      std::string tmp = std::to_string(j);
      for(int o=0;o<tmp.size();o++){
          text[o] = tmp[o];
      }

  /* Provedeni hashovani */
  EVP_DigestInit(&ctx, type);  // nastaveni kontextu
  EVP_DigestUpdate(&ctx, text, strlen(text));  // zahashuje text a ulozi do kontextu
  EVP_DigestFinal(&ctx, hash, (unsigned int *) &length);  // ziskani hashe z kontextu
 
  /* Vypsani vysledneho hashe */	
  if(hash[0] == 170 && hash[1] == 187){
        printf("%s","hash:");printf("\n");
        for(i = 0; i < length; i++){
            printf("%02x", hash[i]);
        }
	printf("\n");
    printf("%s","text v hexa:");printf("\n");
	for(int l =0;l<strlen(text);l++){
	     int tmp = char(text[l]);
	     int first = tmp/16;
	     int second = tmp%16;
	     	
        printf("%c",pole[first]);
		printf("%c",pole[second]);
	}
    	printf("\n");
      exit(0);
      
  }
} 

  exit(0);
}
