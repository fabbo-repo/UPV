const net = require('net');

if(process.argv.length!==5){
    console.log("Faltan argumentos")
    process.exit(1);
}
//0->Ip proxy   1->Ip nueva servidor    2->Puerto nuevo servidor
var args = process.argv.slice(2); //argumentos
var msg = JSON.stringify ({'newIp':args[1],'newPort':args[2]})

const client = net.connect({port: 8001, address: args[0]},
    function() { //connect listener
        client.write(msg);
        console.log('Ip y Puerto enviada al Proxy');
        client.end();
    });