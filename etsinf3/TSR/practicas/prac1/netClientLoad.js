const net = require('net');

if(process.argv.length!==4){
    console.log("Se necesita Ip del servidor e Ip local")
    process.exit(1);
}

var args = process.argv.slice(2); //argumentos
var msg = JSON.stringify ({'clientIp':args[1]})

const client = net.connect({port:53660},{host:args[0]},
    function() { //connect listener
        console.log('cliente conectado');
        client.write(msg);
    });

client.on('data',
    function(data) {
        let p = JSON.parse(data)
        console.log("Carga: "+p.load+" del Servidor: "+p.serverIp);
        client.end(); //no more data written to the stream
    });
client.on('end',
    function() {
        console.log('cliente desconectado');
        process.exit(0);
    });