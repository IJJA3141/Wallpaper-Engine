import fetch from "node-fetch";

const obj = "ligne1//n//ligne2//n//sfdsaaek//n//fkadeal";

fetch("http://localhost:18080/write", {
    method: "POST",
    body: JSON.stringify(obj)
}
)

function c(){
    console.log(">")
    fetch("http://localhost:18080/refresh");
    console.log("||")
}

fetch("http://localhost:18080/getConst");

function f(){
    setTimeout(c, 5000)
}

for(let i = 0; i < 10000; i++){
    f();
}