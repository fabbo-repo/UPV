let pub = require('zeromq').socket('pub')
if (process.argv.length < 5) throw "Need at least 3 arguments"

let args = process.argv.slice(2)
pub.bind('tcp://*:' + args[0])
let maxCount = args [1]
let msg = args.slice(2)
let countT = []
let count = 0

function emite() {    
    if (count >= maxCount) process.exit()
    let idx = count % msg.length
    countT [idx] = !countT [idx] ? 1 : countT [idx]  + 1

    let m=msg.shift()
    pub.send(m + " " + countT[idx])
    msg.push(m) // rotatorio
    count++
}
setInterval(emite,1000) // every second

