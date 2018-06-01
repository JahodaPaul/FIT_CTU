// Pavel Jahoda

#include <stdlib.h>
#include <openssl/evp.h>
#include <string.h>
#include <string>
#include <iostream>

//0	2	Magické číslo (ASCII znaky BM)
//2	4	Délka souboru (unsigned int)
//6	4	2x 2B rezervováno
//10	4	Pozice začátku obrazových dat zac
//14	…	Informace o formátu …
//…	…	Barevná paleta (nepovinné) …
//zac	do konce souboru	Obrazová data

int main(int argc, char** argv) {
  //NACIST VSTUP
  std::string vstupNazevSouboru = std::string{argv[1]} + "_" + std::string{argv[2]} + ".bmp";
  std::string vystupNazevSouboru = std::string{argv[1]} + "_" + std::string{argv[2]} + "_dec.bmp";
  FILE * inputFile = fopen(vstupNazevSouboru.c_str(), "rb");
  FILE * outputFile = fopen(vystupNazevSouboru.c_str(), "wb");
  
  unsigned int length, zac;

  fseek(inputFile, 10, SEEK_SET);
  fread(&zac,4, 1, inputFile);

  fseek(inputFile, 2, SEEK_SET);
  fread(&length, 4, 1, inputFile);
  length -= zac;

  //KOPIROVANI HLAVICKY
  fseek(inputFile, 0, SEEK_SET);
  unsigned int headerLength = zac;
  unsigned char* header = (unsigned char*) calloc(headerLength*sizeof(unsigned char), sizeof(unsigned char));
  fread(header, sizeof(unsigned char), headerLength, inputFile); 
  fwrite(header, sizeof(unsigned char), headerLength, outputFile);
  free(header);

  //CTENI DAT
  fseek(inputFile, zac, SEEK_SET);
  unsigned char* img = (unsigned char*) malloc(length*sizeof(unsigned char));
  fread(img, sizeof(unsigned char), length, inputFile);

  unsigned char* out_img = (unsigned char*) calloc(length*sizeof(unsigned char), sizeof(unsigned char));

  unsigned char key[EVP_MAX_KEY_LENGTH] = "Muj tajny klic";  // klic pro sifrovani
  unsigned char iv[EVP_MAX_IV_LENGTH] = "inicial. vektor";  // inicializacni vektor

  OpenSSL_add_all_ciphers();
  int otLength = 0;
  
  EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();

  int res;

  if(std::string{argv[2]} == "ecb"){
    res = EVP_DecryptInit_ex(ctx, EVP_aes_128_ecb(), NULL, key, iv);
  } else {
    res = EVP_DecryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key, iv);
  }
  if(res != 1) exit(6);

  res = EVP_DecryptUpdate(ctx, out_img, &otLength,  img, length);  // desifrovani st
  if(res != 1) exit(7);
  fwrite(out_img, sizeof(unsigned char), otLength, outputFile);
  free(img);

  res = EVP_DecryptFinal(ctx, out_img, &otLength);  // dokonceni (ziskani zbytku z kontextu)

  EVP_CIPHER_CTX_free(ctx);

  fwrite(out_img, sizeof(unsigned char), otLength, outputFile);
  free(out_img);
}
