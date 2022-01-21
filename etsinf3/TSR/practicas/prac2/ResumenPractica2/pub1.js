let pub = require('zeromq').socket('pub')
if (process.argv.length < 5) throw "Need at least 3 arguments"

pub.bind('tcp://*:' + process.argv[2])
let count = process.argv [3]
let msg = process.argv.slice(4)
let countT = {}

function emite() {    
    if (--count < 0) process.exit()
    let m=msg.shift()
    countT[m] = (countT[m] == undefined) ? 1 : countT[m] + 1
    // SAME AS: countT[m] = (!countT[m]) ? 1 : countT[m] + 1
    
    pub.send(m + " " + countT[m])
    msg.push(m) // rotatorio
}
setInterval(emite,1000) // every second
