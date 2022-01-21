const zmq = require('zeromq')
let sc = zmq.socket('router') // frontend
let sw = zmq.socket('dealer') // backed
sc.bind('tcp://*:9998')
sw.bind('tcp://*:9999')
sc.on('message',(...m)=> { 
    // En m tendremos el array con los segmentos que se reciben.
    // Como se trata de un socket router se recibe como primer 
    // segmento la id del socket cliente que nos ha enviado el mensaje
    // y segundo segmento un '' (string vacio) ya que del 
    // otro lado se conecta un socket req y el resto de segmentos
    // corresponderan al mensaje  
    console.log(m.toString());
    // sw es un socket dealer por lo que enviara todos los segmentos de m,
    // del otro lado se conecta un socket rep que guardará el envoltorio,
    // en este caso el envoltorio incluye la id del cliente y al responder
    // la reenviará.
    sw.send(m)})
sw.on('message',(...m)=> {
    // rep al responder envia el envoltorio más el o los segmentos de respuesta
    // y sabemos que en el envoltorio esta la id del cliente que necesita
    // el socket router para responder, por ello enviamos todo el mensaje por
    // router
    console.log(m.toString());
    sc.send(m)})
