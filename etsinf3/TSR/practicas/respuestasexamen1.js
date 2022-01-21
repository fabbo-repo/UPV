//3)   node publicador 8888 5 Ana Furio Chuvi Jorge

//3a
console.log("3a")
let port = process.argv[2];
let num = process.argv[3];
let temas = process.argv[4];
console.log(port + ' / ' + num + ' / ' + temas); //   8888 / 5 / Ana

//3b
console.log("3b")
let args = process.argv.slice(2);
port = args.shift();
num = args.shift();
temas = args.shift();
console.log(port + ' / ' + num + ' / ' + temas);  //   8888 / 5 / Ana

//3d
console.log("3d")
port = process.argv[2];
num = process.argv[3];
temas = process.argv.slice(4);
console.log(port + ' / ' + num + ' / ' + temas); //   8888 / 5 / Ana,Furio,Chuvi,Jorge

















//4a
console.log("\n4a")
var c = 0;
setInterval(()=>{
  console.log(++c)
  if(c==5){return}
},2000)                    //Incremento de 1 cada 2 segundo sin parar hasta infinito

//4b
console.log("\n4b")
c = 0;
setInterval(()=>{
  console.log(++c)
  if(c==5){process.exit(0)}
},2000)                   //Incremento de 1 cada 2 segundo hasta 5 que inmediatamente para

//4c
console.log("\n4c")
function upto1(n){
  for(let c = 1;c<=n;c++){
    console.log(c);
  }
  process.exit(0);

}
setInterval(upto1(5),2000)  //Incremento de 1 hasta 5 de golpe sin intervalo y termina

//4d
console.log("\n4d")
function upto2(n){
  let c = 0;
  return () => {console.log(++c);if(c==n)process.exit(0)}
}
setInterval(upto2(5),2000) //Incremento de 1 cada 2 segundo hasta 5 que inmediatamente para





















let v = [1,2,3,4,5];

//5a
console.log("5a")
for(let ne=1;ne<=2;ne++){
  for(let e=0;e<v.length;e++){
    console.log(((ne-1)*v.length)+(e+1),v[e],ne)
  }
}
// 1 1 1
// 2 2 1
// 3 3 1
// 4 4 1
// 5 5 1
// 6 1 2
// 7 2 2
// 8 3 2
// 9 4 2
// 10 5 2


//5b
console.log("5b")
for(let n=0;n<=2*v.length;n++){
    console.log(n+1,v[n%v.length],1+Math.trunc(n/v.length))
}
// 1 1 1
// 2 2 1
// 3 3 1
// 4 4 1
// 5 5 1
// 6 1 2
// 7 2 2
// 8 3 2
// 9 4 2
// 10 5 2
// 11 1 3


//5c
console.log("5c")
for(let ne=1;ne<=2;ne++){
  for(let e=0;e<v.length;e++){
    let elem = v.shift();
    v.push(elem)
    console.log(ne*(e+1),elem,ne)
  }
}
// 1 1 1
// 2 2 1
// 3 3 1
// 4 4 1
// 5 5 1
// 2 1 2
// 4 2 2
// 6 3 2
// 8 4 2
// 10 5 2



//20

console.log("20")
let total = 0;
let totalW = {}
setInterval (() => {
  console.log("Total peticiones: " + total);
  for(let w in totalW){
    console.log("Total del worker " + w + " : " + totalW[w])
  }
},1000);
