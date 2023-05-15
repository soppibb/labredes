# Laboratorio 1 redes de computadores
Integrantes: Sofía Bravo
## Dependencias:
- libsodium
- CMake
## Instrucciones de compilación:
```
mkdir build 
cd build
cmake ..
make
```
## Modo de uso:
### Generar clave secreta
```
./keygen <output>
```
### Encriptar archivo
```
./encrypt <key_file> <in_file> <out_file>
```
### Desencriptar
```
./decrypt <key_file> <in_file> <out_file>
```
 
### Iniciar servidor
```
./server 
```

### Conectarse al servidor
```
./client <ip> <archivo>
```

ip: Direccion ipv4 del servidor
archivo : Direccion del archivo que se desea enviar
