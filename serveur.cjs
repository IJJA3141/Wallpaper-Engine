const systeminformation = require("systeminformation");

const express = require("express");
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

app.get("/api", (req, res) => {
  console.log("Request is Incoming");

  const responseData = {
    message: "Hello, GFG Learner",
    articleData: {
      articleName: "How to send JSON response from NodeJS",
      category: "NodeJS",
      status: "published",
    },
    endingMessage: "Visit Geeksforgeeks.org for more",
  };

  const jsonContent = JSON.stringify(responseData);
  res.end(jsonContent);   
});

app.listen(PORT, () => {
  console.info("Server is Listening on " + URI + " !");
});
