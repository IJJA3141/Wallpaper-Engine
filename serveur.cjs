const systeminformation = require("systeminformation");

async function sys(what = []) {
  let json = {};

  for (let i = 0; i < what.length; i++) {
    if (what[i] == "cpu") {
      let cpu = await systeminformation.currentLoad();
      json.cpu = cpu.rawCurrentLoad / 100000;
    } else if (what[i] == "gpu") {
      var gpu = await systeminformation.graphics();
      json.gpu = gpu.controllers[0].utilizationGpu;
    } else if (what[i] == "mem") {
      var mem = await systeminformation.mem();
      json.mem = (mem.total - mem.free) * 9.31 * 10 ** -10;
    } else if (what[i] == "disc") {
      var disc = await systeminformation.fsSize();
      json.disc = disc;
    }
  }
  
  return json;
}
const express = require("express");

const URI = "http://127.0.0.1:3000/";

const app = express();
const PORT = 3000;

app.use(express.static("public"));
app.use(express.json)
app.use("/css", express.static(__dirname + "public/css"));
app.use("/img", express.static(__dirname + "public/img"));
app.use("/js", express.static(__dirname + "public/js"));
app.set("view engine", "ejs");

app.get("", (req, res) => {
  res.render(__dirname + "/views/index.ejs");
});

app.post("/api", async (req, res) => {
  console.log("Request is Incoming");
  console.log(req.body)
  const jsonContent = JSON.stringify(await sys(req.body));
  res.end(jsonContent);
});

app.listen(PORT, () => {
  console.info("Server is Listening on " + URI + " !");
});

(async function a() {
  console.log(await sys());
})();
