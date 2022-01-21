const zmq = require('zeromq')
let cli=[], req=[], workers=[]
let sc = zmq.socket('router') // frontend
let sw = zmq.socket('router') // backend

if(process.argv.length!==4){
	console.log("Se necesita puerto servidor y puerto cliente.")
	process.exit(1)
} 

var args = process.argv.slice(2)
let portFrontend = args[0]
let portBackend = args[1] 
let n = 0;

sc.bind('tcp://*:'+portFrontend)
sw.bind('tcp://*:'+portBackend)
sc.on('message',(c,sep,m)=> {
	if (workers.length==0) { 
		cli.push(c); req.push(m)
	} 
	else {
		sw.send([workers.shift(),'',c,'',m])
	}
})
sw.on('message',(w,sep,c,sep2,r)=> {
	if (c=='') {workers.push(w); return}
	n++;
	if (cli.length>0) { 
		sw.send([w,'',
			cli.shift(),'',req.shift()])
	} else {
		workers.push(w)
	}
	sc.send([c,'',r,n])
})
