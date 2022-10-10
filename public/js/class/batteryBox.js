class percentageBar {
    constructor(height, leftTextContent = "", midTextContent = "", rightTextContent = "", innerBarColor = "var(--blue)") {
        this.obj = document.createElement("div");
        this.innerBar = document.createElement("div");
        this.leftText = document.createElement("p");
        this.midText = document.createElement("p");
        this.rightText = document.createElement("p");
        this.obj.setAttribute("style", "height: " + height + "px;");
        this.leftText.id = "leftBatteryText";
        this.midText.id = "MidBatteryText";
        this.rightText.id = "rightBatteryText";
        this.obj.className = "percentageBar";
        this.innerBar.className = "bar";
        this.leftText.className = "batteryInText";
        this.midText.className = "batteryInText";
        this.rightText.className = "batteryInText";
        this.innerBarWidthAndWidth(100, innerBarColor);
        this.leftTextContent(leftTextContent);
        this.midTextContent(midTextContent);
        this.rightTextContent(rightTextContent);
        this.obj.appendChild(this.innerBar);
        this.obj.appendChild(this.leftText);
        this.obj.appendChild(this.midText);
        this.obj.appendChild(this.rightText);
    }
    innerBarWidthAndWidth(battery, color) {
        this.innerBar.setAttribute("style", "width: calc(" + battery + "% - 4px); background-color: " + color + ";");
    }
    leftTextContent(text) {
        this.leftText.innerHTML = text;
    }
    midTextContent(text) {
        this.midText.innerHTML = text;
    }
    rightTextContent(text) {
        this.rightText.innerHTML = text;
    }
}
class batteryBox {
    constructor(height) {
        this.obj = document.createElement("div");
        this.bar = new percentageBar(height, "", "100%", "", "var(--green)");
        this.text = document.createElement("p");
        this.obj.setAttribute("style", "height: " + (height + 60) + "px; width: 100%; bottom: 0px;");
        this.text.className = "batteryOutText";
        this.text.innerHTML = "Battery:";
        this.obj.appendChild(this.bar.obj);
        this.obj.appendChild(this.text);
    }
    upDateBattery(battery) {
        this.bar.midTextContent(battery + "%");
        if (battery > 40) {
            this.bar.innerBarWidthAndWidth(battery, "var(--green)");
        }
        else {
            this.bar.innerBarWidthAndWidth(battery, "var(--red)");
        }
    }
}
export { batteryBox };
