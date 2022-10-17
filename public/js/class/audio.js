window.wallpaperPropertyListener;
class audioBox {
    constructor(rect) {
        this.obj = document.createElement("div");
        this.divImage = document.createElement("div");
        this.image = document.createElement("img");
        this.uiDiv = document.createElement("div");
        this.audioVisualizationDiv = document.createElement("div");
        this.audioVisualization = document.createElement("canvas");
        this.barDiv = document.createElement("div");
        ("this.bar = new percentageBar()");
        this.textDiv = document.createElement("div");
        this.text = document.createElement("p");
        this.subText = document.createElement("p");
        this.obj.setAttribute("style", "width: " +
            rect.width +
            "px; height: " +
            rect.height +
            "px; left:" +
            rect.left +
            "px; top:" +
            rect.top +
            "px;");
        this.obj.className = "div";
        this.divImage.className = "divAudioImage";
        this.divImage.className = "audioImage";
        this.uiDiv.className = "audioUi";
        this.audioVisualizationDiv.className = "audioVisualizationDiv";
        this.audioVisualization.className = "audioVisualization";
        this.barDiv.className = "audioBar";
        this.textDiv.className = "audioText";
        this.textDiv.className = "audioSubText";
        this.wallpaperMediaPropertiesListener = (event) => {
            this.text.innerText = event.title;
            this.subText.innerText = event.artist;
        };
        window.wallpaperRegisterMediaPropertiesListener(this.wallpaperMediaPropertiesListener);
        this.wallpaperMediaThumbnailListener = (event) => {
            this.image.src = event.thumbnail;
        };
        window.wallpaperRegisterMediaThumbnailListener(this.wallpaperMediaThumbnailListener);
        this.wallpaperMediaPlaybackListener = (event) => {
            if (event.state == window.wallpaperMediaIntegration.playback.PLAYING) {
            }
            else {
                ("change anim");
            }
        };
        window.wallpaperRegisterMediaPlaybackListener(this.wallpaperMediaPlaybackListener);
        this.wallpaperMediaTimelineListener = (event) => {
            if (this.currentAudioDuration != event.duration) {
                ("change bar number");
                this.currentAudioDuration = event.duration;
            }
        };
        window.wallpaperRegisterMediaTimelineListener(this.wallpaperMediaTimelineListener);
        this.wallpaperAudioListener = (audioArray) => {
            var _a, _b, _c;
            // Clear the canvas and set it to black
            this.audioVisualizationCtx.fillStyle = "rgb(0,0,0)";
            (_a = this.audioVisualizationCtx) === null || _a === void 0 ? void 0 : _a.fillRect(0, 0, this.audioVisualization.width, this.audioVisualization.height);
            // Render bars along the full width of the canvas
            var barWidth = Math.round((1.0 / 128.0) * this.audioVisualization.width);
            var halfCount = audioArray.length / 2;
            // Begin with the left channel in red
            this.audioVisualizationCtx.fillStyle = "rgb(255,0,0)";
            // Iterate over the first 64 array elements (0 - 63) for the left channel audio data
            for (var i = 0; i < halfCount; ++i) {
                // Create an audio bar with its hight depending on the audio volume level of the current frequency
                var height = this.audioVisualization.height * Math.min(audioArray[i], 1);
                (_b = this.audioVisualizationCtx) === null || _b === void 0 ? void 0 : _b.fillRect(barWidth * i, this.audioVisualization.height - height, barWidth, height);
            }
            // Now draw the right channel in blue
            this.audioVisualizationCtx.fillStyle = "rgb(0,0,255)";
            // Iterate over the last 64 array elements (64 - 127) for the right channel audio data
            for (var i = halfCount; i < audioArray.length; ++i) {
                // Create an audio bar with its hight depending on the audio volume level
                // Using audioArray[191 - i] here to inverse the right channel for aesthetics
                var height = this.audioVisualization.height * Math.min(audioArray[191 - i], 1);
                (_c = this.audioVisualizationCtx) === null || _c === void 0 ? void 0 : _c.fillRect(barWidth * i, this.audioVisualization.height - height, barWidth, height);
            }
        };
        window.wallpaperRegisterAudioListener(this.wallpaperAudioListener);
        this.audioVisualizationCtx = this.audioVisualization.getContext("2d");
    }
}
export { audioBox };
