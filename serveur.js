const systeminformation = require("systeminformation")

const express = require("express");
const { json } = require("stream/consumers");
const { stringify } = require("querystring");

const URI = "http://127.0.0.1:3000/";

const app = express();
const PORT = 3000;

app.use(express.static("public"));
app.use("/css", express.static(__dirname + "public/css"));
app.use("/img", express.static(__dirname + "public/img"));
app.use("/js", express.static(__dirname + "public/js"));
app.set("view engine", "ejs");

app.get("", (req, res) => {
  
  res.render(__dirname + "/views/index.ejs");
});

app.get("/api", async (req, res)=>{
  res.send({data: await getData()})
})

app.listen(PORT, () => {
  console.info("Hi!");
});

function getData(){
  let res = new Promise
  let data = JSON.parse({})

  // add data from api
  systeminformation.cpuCache().then(response => data.push({cpu: response}))
  systeminformation.graphics().then(response=> data.push({cpu: response}))
  
  res.resolve(stringify(data))
}