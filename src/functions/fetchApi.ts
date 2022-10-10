import fetch from "node-fetch";

async function getData() {
  return await fetch("http://127.0.0.1:3000/api");
}

export { getData };
