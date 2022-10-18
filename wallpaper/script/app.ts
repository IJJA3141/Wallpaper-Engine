//import { batteryBox } from "./class/batteryBox.js";
import { audioBox } from "./class/audio.js";
import { rectagle } from "./class/rectagle.js";

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

const d = new audioBox(new rectagle(100, 100, 100, 100))
desktop?.appendChild(d.obj)

/*
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

desktop?.appendChild(d);
*/