#include <stdio.h>

#include "tcp.h"

int main(void) {
    int port = DEFAULTPORT;

    // Crear servidor
    struct tcp_server_t server;
    tcp_server_create(&server, port);
    printf("starting server at port %d\n", port);

    while (1) {
        // Aceptar la conexion con el cliente
        struct sockaddr_in client_addr;
        socklen_t client_addr_len;
        int sock = tcp_server_accept(&server, &client_addr, &client_addr_len);

        printf("Connected\n");

        // Recibir el tamaño del nombre del archivo
        int name_size;
        tcp_recv_size(sock, &name_size);

        // Recibir el nombre del archivo
        char file_name[name_size];
        tcp_recv(sock, file_name, name_size);

        // Recibir el tamaño del archivo
        int fsize;
        tcp_recv_size(sock, &fsize);

        // Imprimir informacion del archivo que se esta recibiendo
        printf("Recieving...\n");
        printf("file name: %s\n", file_name);
        printf("file size: %d bytes\n", fsize);

        // Recibir los contenidos del archivo
        FILE *file = fopen(file_name, "w+");
        tcp_recv_file(sock, file, fsize);
        fclose(file);
        tcp_close(sock);
        break;
    }

    return 0;
}
