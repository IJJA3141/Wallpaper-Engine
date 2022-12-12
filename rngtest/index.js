import fetch from "node-fetch";

function c(){
    console.log(">")
    fetch("http://localhost:18080/refresh");
    console.log("||")
}

for(let i = 0; i < 500; i++){
    setTimeout(c, 5000)
}