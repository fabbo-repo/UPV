// Broker for clients
const zmq  = require('zeromq')
let sc     = zmq.socket('router') // frontend
let bw     = zmq.socket('dealer') // dealer!! for other broker
let pend=[]
let w=0  // Keep numer of available workers.

sc.bind('tcp://*:9998')
bw.bind('tcp://*:8000')

bw.on('message', (c,r) => {
    if (c!='') sc.send([c,'',r])
    w++
    if (pend.length) {
        w--
        bw.send([c,r])
    }
})

sc.on('message', (c,sep,m) => {
    if (w>0) {
        w--
        bw.send([c,m])
    } else {
        pend.push([c,m])
    }
})