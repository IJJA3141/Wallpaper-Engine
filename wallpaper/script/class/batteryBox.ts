import { percentageBar } from "./percentageBar";

class batteryBox {
  public obj: HTMLElement;

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

export { batteryBox };
