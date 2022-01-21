const zmq = require('zeromq')
let workers=[]
let b1 = zmq.socket('dealer') // conexion a brokerv1
let sw = zmq.socket('router') // backend
b1.bind('tcp://*:9997')
sw.bind('tcp://*:9999')

b1.on('message',(c,m)=> {
	if (workers.length==0) 
		b1.send([c,'wait',m])
	else
		sw.send([workers.shift(),'',c,'',m])
})

sw.on('message',(w,sep,c,sep2,r)=> {
	if (c=='') {
		workers.push(w); 
		return}
	workers.push(w)
	b1.send([c,'',r])
})
