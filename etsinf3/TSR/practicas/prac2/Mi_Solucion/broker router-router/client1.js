const zmq = require('zeromq')
let req = zmq.socket('req');
if(process.argv.length!==5){
	console.log("Faltan argumentos.")
	process.exit(1)
} 

var args = process.argv.slice(2)
let connection = args[0]
let nick = args[1] 
let res = args[2] 

req.identity=nick

req.connect(connection)
req.on('message', (msg,n)=> {
	console.log('Respuesta: '+msg+' '+n)
	process.exit(0);
})
req.send(res)
