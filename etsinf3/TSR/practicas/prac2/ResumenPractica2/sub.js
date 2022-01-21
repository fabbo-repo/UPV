let sub = require('zeromq').socket('sub')
if (process.argv.length < 3) throw "Need 2 arguments"
sub.connect('tcp://127.0.0.1:' + process.argv[2])
sub.subscribe(process.argv[3]) 
sub.on('message', m => console.log(m+''))