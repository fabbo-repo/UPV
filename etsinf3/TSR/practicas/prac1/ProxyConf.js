const net = require('net');

if(process.argv.length!==4){
    console.log("Se necesita Ip del servidor e Ip local")
    process.exit(1);
}

var args = process.argv.slice(2); //argumentos

const LOCAL_PORT = 8000;
const LOCAL_IP = '127.0.0.1';
const REMOTE_PORT = args[1];
const REMOTE_IP = args[0];

const server = net.createServer(function (socket) {
    const serviceSocket = new net.Socket();
    serviceSocket.connect(parseInt(REMOTE_PORT),
        REMOTE_IP, function () {
            socket.on('data', function (msg) {
                serviceSocket.write(msg);
            });
            serviceSocket.on('data', function (data) {
                socket.write(data);
            });
    });
}).listen(LOCAL_PORT, LOCAL_IP);
console.log("TCP server accepting connection on port: " + LOCAL_PORT);