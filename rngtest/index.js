import fetch from "node-fetch";

(function f(){
    const res = "1\n2\n2\n3";
    fetch("http://localhost:23112/write",{method:"POST",body:res})
})()


function c(){
    console.log(">")
    fetch("http://localhost:23112/refresh").then(console.log("||"))
}   

for(let i = 0; i < 500; i++){
    setTimeout(c, 5000)
}
