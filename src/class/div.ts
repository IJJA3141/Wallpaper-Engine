class div {
  obj: Element;
  constructor(public parent: HTMLElement,
    public width: number,
    public height: number,
    public top: number,
    public left: number
  ) {
    this.obj = document.createElement("div");
    this.obj.id = "div";
    this.obj.setAttribute(
      "style",
      "width: " +
        width +
        "px; height: " +
        height +
        "px; top:" +
        top +
        "px; left:" +
        left +
        "px;"
    );
    parent.appendChild(this.obj);
  }
}
export { div }