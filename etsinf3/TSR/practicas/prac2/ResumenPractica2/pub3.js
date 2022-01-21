let pub = require('zeromq').socket('pub')
if (process.argv.length < 5) throw "Need at least 3 arguments"

let [port, maxCount] = process.argv.slice(2)
msg = process.argv.slice(4)

pub.bind('tcp://*:' + port)
let countT = []
let count = 0


console.log ("port: " + port + ", maxCount: " + maxCount +  ", msg: " + msg.toString())
// Same code as pub2
process.exit (1)
