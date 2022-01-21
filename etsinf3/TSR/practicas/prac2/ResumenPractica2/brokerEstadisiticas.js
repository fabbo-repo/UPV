const zmq = require('zeromq')
let reqs=[], workers=[]
let sc = zmq.socket('router') // frontend
let sw = zmq.socket('router') // backend

if (process.argv.length < 4) throw "Need 2 arguments"    
let [portC, portW] = process.argv.slice(2)
sc.bind('tcp://*:' + portC, err => {if (err) throw err})
sw.bind('tcp://*:' + portW, err => {if (err) throw err})

sc.on('message',(c, sep, r)=> {
	console.log ("From client: " + [c,sep,r].join())

	if (workers.length==0) { 
		reqs.push ([c, r]) // Use a vector.
	} else {
        let toSendW = [ workers.shift(),'',c, r ]
        console.log ("Sending to Worker: " + toSendW.join())
		sw.send (toSendW)
	}
})


let total = 0
let totalW = {} // Use a hashtable

setInterval (() => {
    console.log ("Total peticiones: " + total)
    for (let w in totalW) { // Watch loop style !
        console.log ("Total del worker " + w + " : " + totalW[w])
    }
}, 5000)


sw.on('message',(w, sep, c, sep2, r) => {

	console.log ("From worker: " + [w,sep,c,sep2,r].join())
    //if (c=='') {workers.push(w); return}

	if (reqs.length>0) {
		let theReq = reqs.shift(); 
        let toSendW = [w,'', theReq[0], theReq[1]]
        console.log ("Sending to Worker: " + toSendW.join())        
		sw.send(toSendW)
	} else {
		workers.push(w)
	}
	
    //sc.send([c,'',r])
    if (c == '') { // SAME AS: if (!c)
        totalW [w] = 0
    } else {
        let toSendC = [c,'',r]
        console.log ("Sending to Client: " + toSendC.join())    
        total++; 
        totalW[w]++;
        sc.send(toSendC)
	}
})
