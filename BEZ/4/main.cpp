// Pavel Jahoda

#include <stdlib.h>
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <string>
#include <iostream>

int main(int argc, char** argv) {
    //CTENI OBRAZKU


    //NACIST VSTUP
    std::string vstupNazevSouboru = std::string{argv[1]} + ".bmp";
    std::string vystupNazevSouboru = std::string{argv[1]} + "_zasifrovany.bmp";
    FILE * inputFile = fopen(vstupNazevSouboru.c_str(), "rb");
    FILE * outputFile = fopen(vystupNazevSouboru.c_str(), "wb");

    unsigned int length, zac;

    fseek(inputFile, 10, SEEK_SET);
    fread(&zac,4, 1, inputFile);


    fseek(inputFile, 2, SEEK_SET);
    fread(&length, 4, 1, inputFile);
    length -= zac;
//    std::cout << length << std::endl;

    //KOPIROVANI HLAVICKY
    fseek(inputFile, 0, SEEK_SET);
    unsigned int headerLength = zac;
    unsigned char* header = (unsigned char*) calloc(headerLength*sizeof(unsigned char), sizeof(unsigned char));
    fread(header, sizeof(unsigned char), headerLength, inputFile);
    fwrite(header, sizeof(unsigned char), headerLength, outputFile);
    free(header);

    // CTENI DAT
    fseek(inputFile, zac, SEEK_SET);
    unsigned char* img = (unsigned char*) malloc(length*sizeof(unsigned char));
    fread(img, sizeof(unsigned char), length, inputFile);

    //vystup
    unsigned char* out_img = (unsigned char*) calloc(length*sizeof(unsigned char), sizeof(unsigned char));

    int stLength = 0;
    int tmpLength = 0;












    EVP_PKEY * pubkey;
    FILE * fileOfPublicKey = fopen("pubKey.pem","r");
    pubkey = PEM_read_PUBKEY(fileOfPublicKey, NULL, NULL, NULL);
    unsigned char * my_ek = (unsigned char *) malloc(EVP_PKEY_size(pubkey)); // allocate space for encrypted symmet. key
//    my_ek[0] = '1';my_ek[1]='0';my_ek[2]='0';
    int my_ekl; // enc. sym. key length
    unsigned char iv[EVP_MAX_IV_LENGTH] = "inicial. vektor"; // buffer for the init. vector
//    int inlen;//todo inicialize

//    EVP_PKEY_CTX * pubkeyCTX = EVP_PKEY_CTX_new(pubkey, NULL);
//    EVP_PKEY_encrypt_init(pubkeyCTX);
//    EVP_PKEY_CTX_set_rsa_padding(pubkeyCTX, RSA_OAEP_PADDING);
//    EVP_PKEY_encrypt(pubkeyCTX,my_ek,my_ekl,in,inlen);



    OpenSSL_add_all_ciphers();

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    //... declare context ctx and type as in previous lab
    //TODO mozna zmenit EVP_aes_128_ecb()
    const char cipherName[30] = "aes-128-ecb";
    const EVP_CIPHER * cipher = EVP_get_cipherbyname(cipherName);


    EVP_SealInit( ctx, cipher, &my_ek, &my_ekl, iv, &pubkey, 1); // use only 1 public key
    // send type, my_ek, my_ekl, iv to the recipient with the ciphertext
//    printf("%s",my_ek);

    EVP_SealUpdate(ctx, out_img, &stLength, img, length);
    EVP_SealFinal(ctx, out_img + stLength, &tmpLength);
    stLength += tmpLength;





    //ZAPSAT ZASIFROVANY OBRAZEK
    EVP_CIPHER_CTX_free(ctx);
    fseek(outputFile,zac,SEEK_SET);
    fwrite(out_img, sizeof(unsigned char), stLength, outputFile);
    free(out_img);

//    FILE * test = fopen("test","w");
    stLength+=zac;
    int ivLength = EVP_MAX_IV_LENGTH;
//    std::cout << my_ekl << std::endl;
    fseek(outputFile, stLength, SEEK_SET);
//    fwrite(&my_ekl,4,1,outputFile);
    fprintf(outputFile,"%d %d",my_ekl,ivLength);
    fwrite(cipherName,sizeof(char),30,outputFile);
    fwrite(my_ek,sizeof(unsigned char),my_ekl,outputFile);
//    printf("%s",cipherName);

    fwrite(iv,sizeof(unsigned char),ivLength,outputFile);
    fseek(outputFile, 2, SEEK_SET), fwrite(&stLength, 4, 1, outputFile);
//    std::cout << zac <<" " << stLength << std::endl;

    return 0;
}