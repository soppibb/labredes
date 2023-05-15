#include <stdio.h>
#include <stdlib.h>

#include "tcp.h"
#include "util.h"

int main(int argc, const char *argv[]) {
    // Verificar que los parametros cli esten correctos
    if (argc < 3) {
        printf("usage: %s <ip> <file>", argv[0]);
        exit(0);
    }
    const char *ip = argv[1];
    const char *file_name = argv[2];
    int port = DEFAULTPORT;
    
    FILE *file = fopen(file_name, "r");
    int fsize = file_size(file);

    struct tcp_client_t server;
    // Conectarse al sevidor en la ip y puerto seleccionados
    tcp_client_connect(&server, ip, port);
    // Enviar el tamaño del nombre del archivo
    tcp_send_size(server.sock, strlen(argv[2]) + 1);
    // Enviar el nombre del archivo
    tcp_send(server.sock, file_name, strlen(argv[2]) + 1);
    // Enviar el tamaño del archivo
    tcp_send_size(server.sock, fsize);

    // Imprimir info del archivo que se esta enviando
    printf("Sending...\n");
    printf("file name: %s\n", file_name);
    printf("file size: %d bytes\n", fsize);

    // Enviar archivo
    tcp_send_file(server.sock, file, fsize);

    fclose(file);
    tcp_close(server.sock);

    return 0;
}
