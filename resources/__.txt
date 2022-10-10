const taskbar: Element = document.getElementById("taskbar");
const desktop: Element = document.getElementById("desktop");

taskbar.setAttribute("style", "width: " + window.innerWidth + "px;");
desktop.setAttribute(
  "style",
  "width: " +
    window.innerWidth +
    "px; height: " +
    (window.innerHeight * 97) / 100 +
    "px;"
);

class percentageBar {
  public obj: Element;

  private innerBar: Element;
  public innerBarWidthAndWidth(battery: number, color: string) {
    this.innerBar.setAttribute(
      "style",
      "width: calc(" + battery + "% - 4px); background-color: " + color + ";"
    );
  }

  private leftText: Element;
  public leftTextContent(text: string) {
    this.leftText.innerHTML = text;
  }
  private midText: Element;
  public midTextContent(text: string) {
    this.midText.innerHTML = text;
  }
  private rightText: Element;
  public rightTextContent(text: string) {
    this.rightText.innerHTML = text;
  }

  constructor(
    height: number,
    leftTextContent: string = "",
    midTextContent: string = "",
    rightTextContent: string = "",
    innerBarColor: string = "var(--blue)"
  ) {
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
}

class batteryBox {
  obj: Element;

  private bar: percentageBar;

  private text: Element;

  constructor(height: number) {
    this.obj = document.createElement("div");
    this.bar = new percentageBar(height, "", "100%", "", "var(--green)");
    this.text = document.createElement("p");

    this.obj.setAttribute(
      "style",
      "height: " + (height + 60) + "px; width: 100%; bottom: 0px;"
    );

    this.text.className = "batteryOutText";

    this.text.innerHTML = "Battery:";

    this.obj.appendChild(this.bar.obj);
    this.obj.appendChild(this.text);
  }

  public upDateBattery(battery: number) {
    this.bar.midTextContent(battery + "%");
    if (battery > 40) {
      this.bar.innerBarWidthAndWidth(battery, "var(--green)");
    } else {
      this.bar.innerBarWidthAndWidth(battery, "var(--red)");
    }
  }
}

const test = document.createElement("div");
test.className = "div";
test.setAttribute("style", "height: 500px; width: 500px;");

const t = new batteryBox(40);

test.appendChild(t.obj);

desktop.appendChild(test);

const si = require('systeminformation');

si.cpu()
    .then(data => console.log(data))
    .catch(error => console.error(error));

export {batteryBox}