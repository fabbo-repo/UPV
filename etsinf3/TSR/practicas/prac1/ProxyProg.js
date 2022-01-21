const net = require('net');

if(process.argv.length!==4){
    console.log("Faltan argumentos")
    process.exit(1);
}

var args = process.argv.slice(2); //argumentos

const LOCAL_PORT = 8000;
const LOCAL_PORT2 = 8001;
const LOCAL_IP = '127.0.0.1'; //127.0.0.1
var REMOTE_PORT = args[1]; // 8080 o 80
var REMOTE_IP = args[0]; // 158.42.179.56 o 158.42.4.23

var server = net.createServer(function(socket) {
    let serviceSocket = new net.Socket();
    serviceSocket.connect(parseInt(REMOTE_PORT), REMOTE_IP, function () {
            socket.on('data', function (msg) {
                serviceSocket.write(msg);
            });
            serviceSocket.on('data', function (data) {
                socket.write(data);
            });
    });
}).listen(LOCAL_PORT, LOCAL_IP);
console.log("TCP server accepting connection on port: " + LOCAL_PORT);

var programador = net.createServer(function(c) {
    c.on('data',
        function(data) {
            let p = JSON.parse(data)
            REMOTE_PORT = p.newPort;
            REMOTE_IP = p.newIp;
            console.log("Servidor remoto: Puerto:"+p.newPort+" Ip: "+p.newIp)
            
        });
}).listen(LOCAL_PORT2, LOCAL_IP);
console.log("Waiting for changes: " + LOCAL_PORT2);