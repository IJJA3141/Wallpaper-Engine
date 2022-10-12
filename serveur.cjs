const systeminformation = require("systeminformation")

async function sys(what) {
  what.array.forEach(name => {
    switch()
    
  });
  let cpu = await systeminformation.currentLoad();
  let gpu = await systeminformation.graphics();
  let mem = await systeminformation.mem();
  let disc = await systeminformation.fsSize();

  let json = {
    cpu: cpu.rawCurrentLoad / 100000,
    gpu: gpu.controllers[0].utilizationGpu,
    mem: (mem.total - mem.free) * 9.31 * 10 ** -10,
    disc: disc,
  };
  return json;
}
const express = require("express");

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

app.get("/api", async (req, res) => {
  console.log("Request is Incoming");
  const jsonContent = JSON.stringify(await sys());
  res.end(jsonContent);
});

app.get("/api/cpu", async (req, res) => {
  console.log("Request is Incoming");
  const jsonContent = JSON.stringify(await sys());
  res.end(jsonContent);
});

app.get("/api/gpu", async (req, res) => {
  console.log("Request is Incoming");
  const jsonContent = JSON.stringify(await sys());
  res.end(jsonContent);
});

app.get("/api/mem", async (req, res) => {
  console.log("Request is Incoming");
  const jsonContent = JSON.stringify(await sys());
  res.end(jsonContent);
});

app.get("/api/disc", async (req, res) => {
  console.log("Request is Incoming");
  const jsonContent = JSON.stringify(await sys());
  res.end(jsonContent);
});

app.listen(PORT, () => {
  console.info("Server is Listening on " + URI + " !");
});

(async function a(){
  console.log(await sys())
})()