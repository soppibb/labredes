#include "tcp.h"

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdint.h>
#include <stdio.h>

void tcp_server_create(struct tcp_server_t *server, int port) {
    // Crear socket de escucha (se guarda en server->listen_sock)
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1) {
        // No se puede crear el socket del server
        fprintf(stderr, "Socket failed to create\n");
        exit(1);
    }
    server->listen_sock = fd;
    // Bindear socket a puerto
    server->server_addr.sin_family = AF_INET;
    server->server_addr.sin_port = htons(port);
    server->server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(fd, (struct sockaddr *)&server->server_addr,
             sizeof(server->server_addr)) == -1) {
        // No se puede bindear el socket
        fprintf(stderr, "Socket failed to bind\n");
        exit(1);
    }
    // Escuchar conexiones entrantes
    if (listen(fd, BACKLOG) == -1) {
        // No se puede escuchar en el socket del servidor
        fprintf(stderr, "Socket failed to listen\n");
        exit(1);
    }
}

int tcp_server_accept(struct tcp_server_t *server,
                      struct sockaddr_in *client_addr,
                      socklen_t *client_addr_len) {
    // Aceptar primera conexion entrante (guardar dirección del cliente en
    // client_addr)
    int fd = accept(server->listen_sock, (struct sockaddr *)client_addr,
                    client_addr_len);
    if (fd == -1) {
        fprintf(stderr, "Cannot accept connection\n");
        exit(1);
    }
    // Retorna descriptor de archivo del socket de comunicación con el cliente
    return fd;
}

void tcp_client_connect(struct tcp_client_t *client, const char *host,
                        int port) {
    // Crear socket de cliente (se guarda en client->sock)
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1) {
        // No se puede crear el socket de cliente
        fprintf(stderr, "Socket failed to create\n");
        exit(1);
    }
    client->sock = fd;
    client->server_addr.sin_family = AF_INET;
    client->server_addr.sin_port = htons(port);
    if (inet_pton(AF_INET, host, &client->server_addr.sin_addr) != 1) {
        // No se puede resolver la direccion ip
        fprintf(stderr, "Address failed to resolve\n");
        exit(1);
    }
    // Conectar con host y puerto indicados (se guarda en client->server_addr y
    // se usa en llamada a connect())
    if (connect(fd, (struct sockaddr *)&client->server_addr,
                sizeof(client->server_addr)) == -1) {
        // No se puede conectar al servidor
        fprintf(stderr, "Cannot connect to the server\n");
        exit(1);
    }
}

void tcp_send(int sock, const void *data, size_t size) {
    write(sock, data, size);
}

void tcp_send_size(int sock, uint32_t n) {
    uint32_t size = htonl(n);
    write(sock, (uint8_t *)&size, sizeof(uint32_t));
}

void tcp_recv(int sock, void *data, size_t size) {
    read(sock, data, size);
}

void tcp_recv_size(int sock, uint32_t *value) {
    uint8_t buff[sizeof(uint32_t)];
    read(sock, buff, sizeof(uint32_t));
    uint32_t size = *(uint32_t *)buff;
    size = ntohl(size);
    *value = size;
}

void tcp_close(int sock) {
    close(sock);
}
