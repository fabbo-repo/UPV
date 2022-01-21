const zmq = require('zeromq')

let args = process.argv.slice(2)
if(args.length() < 2){
	console.log("Argumentos incorrectos")
	process.exit(1)
}
let port = args[0]
let numMensajes = args[1]

let pub = zmq.socket('pub')
let msg = args.slice(2)

pub.bind('tcp://*:'+port)

function fn(i,n) {
	return () => {
		let m = msg[0]
		let message = "Tras "+i+" segundos: "+i+" "+m+" "+n
		console.log(message)
		pub.send(message)
		msg.shift(); msg.push(m)
	}
}

let n = 1;

for(let i = 1; i <= numMensajes; i++){
	setTimeout(fn(i,n),i*1000)
	if(i%msg.length == 0) n++
}
