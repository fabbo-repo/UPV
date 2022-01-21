const zmq = require('zeromq')
let reqs=[], workers=[]
let sc = zmq.socket('router') // frontend
let sw = zmq.socket('router') // backend

if (process.argv.length < 4) throw "Need 2 arguments"    
let [portC, portW] = process.argv.slice(2)
sc.bind('tcp://*:' + portC, err => {if (err) throw err})
sw.bind('tcp://*:' + portW, err => {if (err) throw err})

sc.on('message',(c, sep, r)=> {
	if (workers.length==0) { 
		reqs.push ([c, r]) // Use a vector.
	} else {
		sw.send ([ workers.shift(),'',c, r ])
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

	if (reqs.length>0) {
		let theReq = reqs.shift(); 
		sw.send([w,'', theReq[0], theReq[1]])
	} else {
		workers.push(w)
	}
	
    if (c != '') { // SAME AS: if (!c)
        total++; 
        totalW[w] = !totalW[w] ? 1 : totalW[w] + 1;
        sc.send(toSendC = [c,'',r])
	}
})
