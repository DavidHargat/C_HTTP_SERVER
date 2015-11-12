# Http-Server-C

A static HTTP server written in C with basic configuration options.


## build

`clone https://github.com/DavidHargat/Http-Server-C`

`make`

should output: `build/app`

## run

`build/app -p <port>`

## options

**required**

`-p <number>` - port number 

**optional**

`-v` - verbose mode

## dependencies

Linux (implemented with GNU sockets)

gcc - https://gcc.gnu.org
