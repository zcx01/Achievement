import QtQuick 2.12

Canvas{
    id:canvas

//    onPaint: {
//        var vtx = getContext("2d");
//        vtx.fillStyle = "green"
//        vtx.strokeStyle ="blue"
//        vtx.lineWidth = 4
//        vtx.lineJoin = "round"
//        vtx.fillRect(20,20,160,160)
//        vtx.clearRect(30,30,140,140)
//        vtx.strokeRect(20,20,80,80)
//    }
      property var imageURL : "http://www.baidu.com/img/bdlogo.gif"
      onImageLoaded: {
          if(canvas.isImageError(imageURL)){
              console.log("Image failed to loaded!")
          }
          var vtx = getContext("2d");
          vtx.drawImage(imageURL,0,0,)
          canvas.requestPaint() //立即重绘
      }
      Component.onCompleted: {
          canvas.loadImage(imageURL)
      }
}
