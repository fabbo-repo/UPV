// Broker for workers.
const zmq  = require('zeromq')
let sw     = zmq.socket('router') // backend
let bc     = zmq.socket('dealer') // dealer!! for other broker
let workers=[]

sw.bind('tcp://*:9999')
bc.connect('tcp://localhost:8000')

bc.on('message', (c,m) => {
   sw.send ([workers.shift(),'',c,'',m])
})

sw.on('message', (w,sep,c,sep2,r) => {
   workers.push (w); 
   bc.send ([c,r])
})
