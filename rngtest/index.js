import fetch from "node-fetch";

const obj = "ligne1//n//ligne2//n//s";

fetch("http://localhost:18080/write", {
    method: "POST",
    body: JSON.stringify(obj)
}
)