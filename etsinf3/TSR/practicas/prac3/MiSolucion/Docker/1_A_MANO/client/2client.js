const zmq = require('zeromq')
let req = zmq.socket('req');

var args = process.argv.slice(2)
if (args.length < 1) {
  console.log ("node myclient brokerURL")
  process.exit(-1)
}
var bkURL = args[0]

console.log(bkURL)

var x = 0

req.connect(bkURL)
req.on('message', (msg)=> {
  console.log('resp: '+msg)
  x++
  if(x==10)process.exit(0);
})

for(let i = 0; i < 10; i++)
  req.send('Hola')
