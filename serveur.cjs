const fs = require("fs");

function readNotes() {
  return fs.readFileSync("./public/data/notes.txt");
}

function writeToNotes(text) {
  fs.writeFileSync("./public/data/notes.txt", text, {
    encoding: "utf8",
    flag: "w",
  });
}

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
      json.mem = {
        used: (mem.total - mem.free) * 9.31 * 10 ** -10,
        total: mem.total * 9.31 * 10 ** -10,
      };
    } else if (what[i] == "disc") {
      var disc = await systeminformation.fsSize();
      json.disc = disc;
    }
  }

  return json;
}

const express = require("express");
const bp = require("body-parser");

const URI = "http://127.0.0.1:3000/";

const app = express();
const PORT = 3000;

app.use(express.static("public"));
app.use("/css", express.static(__dirname + "public/css"));
app.use("/img", express.static(__dirname + "public/img"));
app.use("/js", express.static(__dirname + "public/js"));
app.use(bp.json({ extended: true }));
app.set("view engine", "ejs");

app.get("", (req, res) => {
  res.render(__dirname + "/views/index.ejs");
});

app.post("/api", async (req, res) => {
  console.log("Request is Incoming");
  console.log(req.body);
  let jsonContent = JSON.stringify(await sys(req.body));
  res.end(jsonContent);
});

app.post("/notes", (req, res) => {
  console.log("Request is Incoming");
  console.log(req.body);
  writeToNotes(req.body)
  res.end();
});

app.get("/notes", (req, res) => {
  console.log("Request is Incoming");
  let jsonContent = JSON.stringify(readNotes())
  res.end(jsonContent);
});

app.listen(PORT, () => {
  console.info("Server is Listening on " + URI + " !");
});
