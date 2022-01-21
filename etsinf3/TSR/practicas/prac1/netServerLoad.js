const net = require('net');
const fs = require('fs');

const server = net.createServer(
    function(c) { //connection listener
        console.log('server: cliente conectado');

        c.on('end',
            function() {
                console.log('server: cliente desconectado, fin de conexión...');
                process.exit(0);
            });

        c.on('data',
            function(data) {
                let p = JSON.parse(data)
                console.log("IPCliente: "+p.clienteIp)
                let msg = JSON.stringify({'serverIp':c.localAddress,
                    'load':getLoad()})
                c.write(msg); // send resp
                c.end(); // close socket
            });
    });

server.listen(53660, 
    function() { //listening listener
        console.log('server abierto');
    });

function getLoad(){
    data=fs.readFileSync("/proc/loadavg"); //requiere fs
    var tokens = data.toString().split(' ');
    var min1 = parseFloat(tokens[0])+0.01;
    var min5 = parseFloat(tokens[1])+0.01;
    var min15 = parseFloat(tokens[2])+0.01;
    return min1*10+min5*2+min15;
};