const { batteryBox } = require("./public/js/app.js");
const { ReactDOM } = require("react-dom")

const URI = "http://127.0.0.1:3000/";

const express = require("express");
const app = express();
const PORT = 3000;

app.use(express.static("public"));
app.use("/css", express.static(__dirname + "public/css"));
app.use("/img", express.static(__dirname + "public/img"));
app.use("/js", express.static(__dirname + "public/js"));
app.set("view engine", "ejs");

app.get("", (req, res) => {
  res.render(__dirname + "/views/index");
  const taskbar = document.getElementById("taskbar");
  const desktop = document.getElementById("desktop");
  
  console.log(taskbar)

  taskbar.setAttribute("style", "width: " + window.innerWidth + "px;");
  desktop.setAttribute(
    "style",
    "width: " +
    window.innerWidth +
    "px; height: " +
    (window.innerHeight * 97) / 100 +
    "px;"
    );
    ReactDOM.render(desktop)
/*
  const t = new batteryBox(40);
  const test = document.createElementNS("div");
  
  test.setAttribute("style", "height: 500px; width: 500px;");
  
  test.appendChild(t)

  desktop.appendChild(test);*/
});

app.listen(PORT, () => {
  console.info("Hi!");
});
