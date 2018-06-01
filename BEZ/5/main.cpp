#include <iostream>
#include <openssl/ssl.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <memory>

//-lssl
using namespace std;

int main(){
    char buffer[4096];
    int err = 0;
    int nread = 0, nwritten = 0;
    SSL_CTX * context = nullptr;
    SSL * ssl = nullptr;

    SSL_library_init();

    int fd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);

    if (fd < 0) exit(0);

    //connect to fit cvut cz
    sockaddr_in sa;
    memset(&sa,0,sizeof(sa));

    sa.sin_addr.s_addr = inet_addr("147.32.232.248");//("fit.cvut.cz"); 147.32.232.248
    sa.sin_family = AF_INET;
    //sa.sin_len = sizeof(sa);
    sa.sin_port = htons(443);

    err=connect(fd,(sockaddr*)&sa, sizeof(sa));

    if (err < 0) exit(0);

    context = SSL_CTX_new(SSLv23_client_method());
    if(!context) exit(0);


    // ban old protocols
    SSL_CTX_set_options(context, SSL_OP_NO_SSLv2 | SSL_OP_NO_SSLv3 | SSL_OP_NO_TLSv1);

    ssl = SSL_new(context);

    SSL_set_fd(ssl,fd);
    err = SSL_connect(ssl);

    if(err <= 0) exit(0);

    //extract certificate
    X509 * cert = SSL_get_peer_certificate(ssl);

    remove("cert.pem");
    FILE * cert_file = fopen("cert.pem","wa");
    PEM_write_X509(cert_file,cert);
    fclose(cert_file);
    
    //BIO *o = BIO_new_fp(stdout,BIO_NOCLOSE);
    //X509_print_ex(o, cert, XN_FLAG_COMPAT, X509_FLAG_COMPAT);
    //remove("cert_info.txt");
    //FILE * cert_info = fopen("cert_info.txt","wa");
    //X509_print_ex_fp(cert_info,cert,XN_FLAG_COMPAT,X509_FLAG_COMPAT);
    //fclose(cert_info);

    nwritten = SSL_write(ssl,"GET /student/odkazy HTTP 1.1\r\nHost: fit.cvut.cz\r\n\r\n",sizeof("GET /student/odkazy HTTP 1.1\r\nHost: fit.cvut.cz\r\n\r\n"));

    if(nwritten <= 0) exit(0);
    // read the bytes

    //unique_ptr<char[]> buf(new char[4096]);
    //while( (nread = SSL_read(ssl,buf.get(),4096)) > 0){
    //    cout.write(buf.get(),nread);
    //}
    FILE *out;
    remove("out.txt");
    out = fopen("out.txt", "wa");

    while((nread = SSL_read(ssl, buffer, sizeof(buffer)))>0){
        fwrite(buffer, sizeof(char), nread, out);
    }

    fclose(out);

    SSL_shutdown(ssl);
    close(fd);

    return 0;
}
