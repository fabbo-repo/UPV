const zmq = require('zeromq')
let cli=[], req=[], workers=[]
let countReqW = {} //tabla hash
let countTotalReq = 0;
let sc = zmq.socket('router') // frontend
let sw = zmq.socket('router') // backend

if(process.argv.length!==4){
	console.log("Se necesita puerto servidor y puerto cliente.")
	process.exit(1)
} 

var args = process.argv.slice(2)
let portFrontend = args[0]
let portBackend = args[1] 

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
	if (c=='') {
		workers.push(w);
		countReqW[w]=0;
		return
	}
	if (cli.length>0) { 
		sw.send([w,'',
			cli.shift(),'',req.shift()])
	} 
	else {
		workers.push(w)
	}
	countTotalReq++;
	countReqW[w]++;
	sc.send([c,'',r,countTotalReq])
})

let fn = () => {
	console.log("Total de peticiones "
		+countTotalReq);
	for(w in countReqW)
		console.log("Peticiones de "
			+w+":"+countReqW[w])
}

setInterval(fn, 5000);