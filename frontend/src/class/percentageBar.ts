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

export { percentageBar };
