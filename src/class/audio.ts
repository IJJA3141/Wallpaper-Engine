import { percentageBar } from "./percentageBar";
import { rectagle } from "./rectagle";

declare global {
  interface Window {
    wallpaperRegisterMediaPropertiesListener: any;
    wallpaperRegisterMediaThumbnailListener: any;
    wallpaperRegisterMediaPlaybackListener: any;
    wallpaperRegisterMediaTimelineListener: any;
    wallpaperRegisterAudioListener: any;
    wallpaperPropertyListener: any;
    wallpaperMediaIntegration: any;
  }
}

interface propertiesEvent {
  title: string;
  artist: string;
  subTitle: string;
  albumTitle: string;
  albumArtist: string;
  genres: string;
}

interface thumbnailEvent {
  thumbnail: string;
  primaryColor: string;
  secondaryColor: string;
  tertiaryColor: string;
  textColor: string;
  highContrastColor: string;
}

interface mediaPlaybackEvent {
  state: any;
}

interface mediaTimelineEvent {
  position: number;
  duration: number;
}

window.wallpaperPropertyListener;
class audioBox {
  obj: HTMLElement;

  divImage: HTMLDivElement;
  image: HTMLImageElement;

  uiDiv: HTMLDivElement;

  audioVisualizationDiv: HTMLDivElement;
  audioVisualization: HTMLCanvasElement;
  audioVisualizationCtx: CanvasRenderingContext2D | null;

  barDiv: HTMLDivElement;
  bar: percentageBar;

  textDiv: HTMLDivElement;
  text: HTMLParagraphElement;
  subText: HTMLParagraphElement;

  currentAudioDuration: number;

  private wallpaperMediaPropertiesListener: Function;
  private wallpaperMediaThumbnailListener: Function;
  private wallpaperMediaPlaybackListener: Function;
  private wallpaperMediaTimelineListener: Function;

  private wallpaperAudioListener: Function;

  constructor(rect: rectagle) {
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

    this.obj.setAttribute(
      "style",
      "width: " +
        rect.width +
        "px; height: " +
        rect.height +
        "px; left:" +
        rect.left +
        "px; top:" +
        rect.top +
        "px;"
    );
    this.obj.className = "div";

    this.divImage.className = "divAudioImage";
    this.divImage.className = "audioImage";

    this.uiDiv.className = "audioUi";

    this.audioVisualizationDiv.className = "audioVisualizationDiv";
    this.audioVisualization.className = "audioVisualization";

    this.barDiv.className = "audioBar";

    this.textDiv.className = "audioText";
    this.textDiv.className = "audioSubText";

    this.wallpaperMediaPropertiesListener = (event: propertiesEvent) => {
      this.text.innerText = event.title;
      this.subText.innerText = event.artist;
    };
    window.wallpaperRegisterMediaPropertiesListener(
      this.wallpaperMediaPropertiesListener
    );

    this.wallpaperMediaThumbnailListener = (event: thumbnailEvent) => {
      this.image.src = event.thumbnail;
    };
    window.wallpaperRegisterMediaThumbnailListener(
      this.wallpaperMediaThumbnailListener
    );

    this.wallpaperMediaPlaybackListener = (event: mediaPlaybackEvent) => {
      if (event.state == window.wallpaperMediaIntegration.playback.PLAYING) {
      } else {
        ("change anim");
      }
    };
    window.wallpaperRegisterMediaPlaybackListener(
      this.wallpaperMediaPlaybackListener
    );

    this.wallpaperMediaTimelineListener = (event: mediaTimelineEvent) => {
      if (this.currentAudioDuration != event.duration) {
        ("change bar number");
        this.currentAudioDuration = event.duration;
      }
    };
    window.wallpaperRegisterMediaTimelineListener(
      this.wallpaperMediaTimelineListener
    );

    this.wallpaperAudioListener = (audioArray: Array<number>) => {
      // Clear the canvas and set it to black
      this.audioVisualizationCtx.fillStyle = "rgb(0,0,0)";
      this.audioVisualizationCtx?.fillRect(
        0,
        0,
        this.audioVisualization.width,
        this.audioVisualization.height
      );

      // Render bars along the full width of the canvas
      var barWidth = Math.round((1.0 / 128.0) * this.audioVisualization.width);
      var halfCount = audioArray.length / 2;

      // Begin with the left channel in red
      this.audioVisualizationCtx.fillStyle = "rgb(255,0,0)";
      // Iterate over the first 64 array elements (0 - 63) for the left channel audio data
      for (var i = 0; i < halfCount; ++i) {
        // Create an audio bar with its hight depending on the audio volume level of the current frequency
        var height =
          this.audioVisualization.height * Math.min(audioArray[i], 1);
        this.audioVisualizationCtx?.fillRect(
          barWidth * i,
          this.audioVisualization.height - height,
          barWidth,
          height
        );
      }
      // Now draw the right channel in blue
      this.audioVisualizationCtx.fillStyle = "rgb(0,0,255)";
      // Iterate over the last 64 array elements (64 - 127) for the right channel audio data
      for (var i = halfCount; i < audioArray.length; ++i) {
        // Create an audio bar with its hight depending on the audio volume level
        // Using audioArray[191 - i] here to inverse the right channel for aesthetics
        var height =
          this.audioVisualization.height * Math.min(audioArray[191 - i], 1);
        this.audioVisualizationCtx?.fillRect(
          barWidth * i,
          this.audioVisualization.height - height,
          barWidth,
          height
        );
      }
    };
    window.wallpaperRegisterAudioListener(this.wallpaperAudioListener);

    this.audioVisualizationCtx = this.audioVisualization.getContext("2d");
  }
}

export { audioBox };
