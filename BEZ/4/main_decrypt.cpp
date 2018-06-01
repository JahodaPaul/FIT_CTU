// Pavel Jahoda

#include <stdlib.h>
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <string>
#include <iostream>

int main(int argc, char** argv) {
    //CTENI OBRAZKU


    //NACIST VSTUP
    std::string vstupNazevSouboru = std::string{argv[1]} + "_zasifrovany.bmp";
    std::string vystupNazevSouboru = std::string{argv[1]} + "_desifrovany.bmp";
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

    // CTENI DAT
    fseek(inputFile, zac, SEEK_SET);
    unsigned char* img = (unsigned char*) malloc(length*sizeof(unsigned char));
    fread(img, sizeof(unsigned char), length, inputFile);

    //vystup
    unsigned char* out_img = (unsigned char*) calloc(length*sizeof(unsigned char), sizeof(unsigned char));

    int stLength = 0;
    int tmpLength = 0;










    EVP_PKEY * privKey;
    FILE * fileOfPrivateKey = fopen("privKey.pem","r");
    privKey = PEM_read_PrivateKey(fileOfPrivateKey, NULL, NULL, NULL);
    unsigned char * my_ek = (unsigned char *) malloc(EVP_PKEY_size(privKey)); // allocate space for encrypted symmet. key
//    my_ek[0] = '1';my_ek[1]='0';my_ek[2]='0';
    int my_ekl; // enc. sym. key length
//    unsigned char iv[EVP_MAX_IV_LENGTH] = "inicial. vektor"; // buffer for the init. vector
//    int inlen;//todo inicialize


    char cipherName[30]; //= "aes-128-ecb";//"EVP_aes_128_ecb";


    int ivLength;
//    FILE * test = fopen("test","r");
    stLength = length + zac;
//    std::cout << zac <<" " << stLength << std::endl;
    fseek(inputFile,stLength,SEEK_SET);
    fscanf(inputFile,"%d %d",&my_ekl,&ivLength);
    fread(cipherName,sizeof(char),30,inputFile);
//    printf("%s",cipherName);


    unsigned char * iv = (unsigned char*)malloc(ivLength*sizeof(unsigned char));

//    fread(&my_ekl,4,1,inputFile);
//    std::cout << my_ekl << std::endl;
    fread(my_ek,sizeof(unsigned char),my_ekl,inputFile);
    fread(iv,sizeof(unsigned char),ivLength,inputFile);
//    fread(iv,sizeof(unsigned char),EVP_MAX_IV_LENGTH,test)

//    EVP_PKEY_CTX * pubkeyCTX = EVP_PKEY_CTX_new(pubkey, NULL);
//    EVP_PKEY_encrypt_init(pubkeyCTX);
//    EVP_PKEY_CTX_set_rsa_padding(pubkeyCTX, RSA_OAEP_PADDING);
//    EVP_PKEY_encrypt(pubkeyCTX,my_ek,my_ekl,in,inlen);



    OpenSSL_add_all_ciphers();

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    //... declare context ctx and type as in previous lab
    //TODO mozna zmenit EVP_aes_128_ecb()
    const EVP_CIPHER * cipher = EVP_get_cipherbyname(cipherName);


    EVP_OpenInit( ctx, cipher, my_ek, my_ekl, iv, privKey); // use only 1 public key
    // send type, my_ek, my_ekl, iv to the recipient with the ciphertext
//    printf("%s",my_ek);

    EVP_OpenUpdate(ctx, out_img, &stLength, img, length);
    EVP_OpenFinal(ctx, out_img + stLength, &tmpLength);
    stLength += tmpLength;




    //ZAPSAT ZASIFROVANY OBRAZEK
    EVP_CIPHER_CTX_free(ctx);

    fwrite(out_img, sizeof(unsigned char), stLength, outputFile);
    free(out_img);

    return 0;
}
