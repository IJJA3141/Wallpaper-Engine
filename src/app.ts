import { batteryBox } from "./class/batteryBox.js";
import { div } from "./class/div.js";
import { getData, data } from "./functions/fetchApi.js";

const taskbar: HTMLElement = document.getElementById("taskbar");
const desktop: HTMLElement = document.getElementById("desktop");

taskbar.setAttribute("style", "width: " + window.innerWidth + "px;");
desktop.setAttribute(
  "style",
  "width: " +
    window.innerWidth +
    "px; height: " +
    (window.innerHeight * 97) / 100 +
    "px;"
);

const d = new div(desktop, 100, 100, 100, 100);

const t = new batteryBox(40);

d.obj.appendChild(t.obj);

(async function name() {
  let r:data = await getData(["mem", "disc"]);
  console.log(r)
})();