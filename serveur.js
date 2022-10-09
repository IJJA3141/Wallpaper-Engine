const express = require("express");
const app = express();
const PORT = 3000;

app.use(express.static("public"));
app.use("/css", express.static(__dirname + "public/css"));
app.use("/img", express.static(__dirname + "public/img"));
app.use("/js", express.static(__dirname + "public/js"));
app.set('view engine', 'ejs');

app.get("", (req, res) => {
  res.render(__dirname + "/views/index");
});

app.listen(PORT, ()=>{console.info("Hi!")});