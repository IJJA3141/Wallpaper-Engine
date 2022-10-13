class div {
    constructor(parent = document.createElement("div"), width, height, top, left) {
        this.parent = parent;
        this.width = width;
        this.height = height;
        this.top = top;
        this.left = left;
        this.obj = document.createElement("div");
        this.obj.id = "div";
        this.obj.setAttribute("style", "width: " +
            width +
            "px; height: " +
            height +
            "px; top:" +
            top +
            "px; left:" +
            left +
            "px;");
        parent.appendChild(this.obj);
    }
}
export { div };
