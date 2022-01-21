const zmq = require('zeromq')
const ansInterval = 2000     // answer timeout. If exceeded, worker failed

let who=[], req=[] 	     // pending request (client,message)
let workers=[], failed={}    // available & failed workers
let tout={} 		     // timeouts for attended requests

let sc = zmq.socket('router') // frontend
let sw = zmq.socket('router') // backend
sc.bind("tcp://*:9998", (err)=>{
   console.log(err?"sc binding error":"accepting client requests")
})
sw.bind("tcp://*:9999", (err)=>{
   console.log(err?"sw binding error":"accepting worker requests")
})

function dispatch(c,m) {
  if (workers.length)               // if available workers,
      sendToW(workers.shift(),c,m)  //    send request to first worker
  else {                            // no available workers
      who.push(c); req.push(m)      //    set as pending
  }  	
}
function resend(w,c,m) {
	return function() {         // ansInterval finished and no response
		failed[w]=true      // Si se llega hacer un resend de w significa que w ha fallado
		dispatch(c,m)       // Se busca algun otro worker para enviar este mensaje del cliente c
	}
}
function sendToW(w,c,m) {
	sw.send([w,'',c,'',m])
	tout[w]=setTimeout(resend(w,c,m), ansInterval) }

sc.on('message', (c,sep,m) => dispatch(c,m))

sw.on('message', (w,sep,c,sep2,r) => {
     if (failed[w]) return 	    // Aqui se descartan los mensajes si este worker se supone que ha fallado
     if (tout[w]) { 		    // No ha fallado por lo que se elimina el timeout
     	clearTimeout(tout[w])  	    //    cancel timeout
     	delete tout[w]
     }
     if (c) sc.send([c,'',r]) 	    // If it was a response, send resp to client
     if (who.length) 		    // Si hay clientes esperando, le dice a w que atienda
     	sendToW(w,who.shift(),req.shift()) //    le dice a w que atienda a who
     else
     	workers.push(w) 	    // worker se queda a la espera de peticiones
})

