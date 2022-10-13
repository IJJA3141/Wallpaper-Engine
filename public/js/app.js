var __awaiter = (this && this.__awaiter) || function (thisArg, _arguments, P, generator) {
    function adopt(value) { return value instanceof P ? value : new P(function (resolve) { resolve(value); }); }
    return new (P || (P = Promise))(function (resolve, reject) {
        function fulfilled(value) { try { step(generator.next(value)); } catch (e) { reject(e); } }
        function rejected(value) { try { step(generator["throw"](value)); } catch (e) { reject(e); } }
        function step(result) { result.done ? resolve(result.value) : adopt(result.value).then(fulfilled, rejected); }
        step((generator = generator.apply(thisArg, _arguments || [])).next());
    });
};
import { batteryBox } from "./class/batteryBox.js";
import { getData } from "./functions/fetchApi.js";
const taskbar = document.getElementById("taskbar");
const desktop = document.getElementById("desktop");
taskbar === null || taskbar === void 0 ? void 0 : taskbar.setAttribute("style", "width: " + window.innerWidth + "px;");
desktop === null || desktop === void 0 ? void 0 : desktop.setAttribute("style", "width: " +
    window.innerWidth +
    "px; height: " +
    (window.innerHeight * 97) / 100 +
    "px;");
const d = document.createElement("div");
d.className = "div";
d.setAttribute("style", "width: " +
    200 +
    "px; height: " +
    200 +
    "px; top:" +
    200 +
    "px; left:" +
    200 +
    "px;");
const t = new batteryBox(40);
desktop === null || desktop === void 0 ? void 0 : desktop.appendChild(d);
d.appendChild(t.obj);
(function name() {
    return __awaiter(this, void 0, void 0, function* () {
        let r = yield getData(["mem", "disc"]);
        console.log(r);
    });
})();
