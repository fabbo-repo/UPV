const zmq = require('zeromq')
let req = zmq.socket('req')
//req.identity = 'Worker1'
req.identity = 'Worker'+getRandomArbitrary(0, 11)+getRandomArbitrary(10, 20)

var args = process.argv.slice(2)
if (args.length < 1) {
  console.log ("node myclient brokerURL")
  process.exit(-1)
}
var bkURL   = args[0]
req.connect(bkURL)
req.on('message', (c,sep,msg)=> {
	setTimeout(()=> {
		req.send([c,'','resp'])
	}, 1000)
})
req.send(['','',''])

function getRandomArbitrary(min, max) {
	return Math.random() * (max - min) + min;
  }