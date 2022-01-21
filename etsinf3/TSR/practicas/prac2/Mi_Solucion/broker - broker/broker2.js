const zmq = require('zeromq')
let workers=[], bv1=0
let b1 = zmq.socket('router') // conexion a brokerv1
let sw = zmq.socket('router') // backend
b1.bind('tcp://*:9997')
sw.bind('tcp://*:9999')

b1.on('message',(b,c,m)=> {
	if(bv1==0) bv1 = b;

	if (workers.length==0) return
	
	if(c=='') {b1.send([bv1,'',''])}
	else {
		sw.send([workers.shift(),'',c,'',m])
	}
})

sw.on('message',(w,sep,c,sep2,r)=> {
	if (c=='') {
		workers.push(w); 
		return}
	workers.push(w)
	b1.send([bv1,c,r])
})
