let tables = []

function fun(y){
    return x=>x*y
}

for(var i=1; i<11; i++)
    tables[i]=fun(i)

console.log(tables[5](2))
console.log(tables[9](2))