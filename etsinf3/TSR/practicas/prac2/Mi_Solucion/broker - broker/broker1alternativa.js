const zmq = require('zeromq')
let cli=[], req=[]
let sc = zmq.socket('router') // frontend
let b2 = zmq.socket('dealer') // conexion a brokerv2
sc.bind('tcp://*:9998')
b2.connect('tcp://localhost:9997')

sc.on('message',(c,sep,m)=> {
	b2.send([c,m])
})

b2.on('message',(c,w,r)=> {
	if (w=='wait') {
		cli.push(c); req.push(r);
		return
	}
    if (cli.length>0) { 
		b2.send([cli.shift(),req.shift()])
	}
	sc.send([c,'',r])
})
