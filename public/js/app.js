//import { batteryBox } from "./class/batteryBox.js";
import { audioBox } from "./class/audio.js";
import { rectagle } from "./class/rectagle.js";
const taskbar = document.getElementById("taskbar");
const desktop = document.getElementById("desktop");
taskbar === null || taskbar === void 0 ? void 0 : taskbar.setAttribute("style", "width: " + window.innerWidth + "px;");
desktop === null || desktop === void 0 ? void 0 : desktop.setAttribute("style", "width: " +
    window.innerWidth +
    "px; height: " +
    (window.innerHeight * 97) / 100 +
    "px;");
const d = new audioBox(new rectagle(100, 100, 100, 100));
desktop === null || desktop === void 0 ? void 0 : desktop.appendChild(d.obj);
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
