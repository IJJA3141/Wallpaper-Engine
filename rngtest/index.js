import fetch from "node-fetch";

(function f(){
    const res = "1//n//2//N//3//N//4//N//5//N//6//N//7E";
    fetch("http://localhost:18080/write",{method:"POST",body:res})
})()

function c(){
    console.log(">")
    fetch("http://localhost:18080/refresh").then(console.log("||"))
}   

for(let i = 0; i < 500; i++){
    setTimeout(c, 5000)
}