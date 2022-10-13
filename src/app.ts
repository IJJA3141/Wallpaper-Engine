import { batteryBox } from "./class/batteryBox.js";
import { getData, data } from "./functions/fetchApi.js";

const taskbar: HTMLElement | null = document.getElementById("taskbar");
const desktop: HTMLElement | null = document.getElementById("desktop");

taskbar?.setAttribute("style", "width: " + window.innerWidth + "px;");
desktop?.setAttribute(
  "style",
  "width: " +
    window.innerWidth +
    "px; height: " +
    (window.innerHeight * 97) / 100 +
    "px;"
);

const d = document.createElement("div");
d.className = "div"
d.setAttribute(
  "style",
  "width: " +
    200 +
    "px; height: " +
    200 +
    "px; top:" +
    200 +
    "px; left:" +
    200 +
    "px;"
);

const t = new batteryBox(40);

desktop?.appendChild(d);
d.appendChild(t.obj);

(async function name() {
  let r: data = await getData(["mem", "disc"]);
  console.log(r);
})();
