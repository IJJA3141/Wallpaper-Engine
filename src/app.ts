import { batteryBox } from "./class/batteryBox.js";
import { div } from "./class/div.js";
import { getData } from "./functions/fetchApi.js";

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

const d = new div(desktop, 500, 500, 100, 100);

const t = new batteryBox(40);

d.obj.appendChild(t.obj);

setTimeout(() => {
  t.upDateBattery(30);
}, 1000);

console.log(getData());
