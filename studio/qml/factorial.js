function factorial(a) {
    a = parseInt(a);
	if(a <= 0){
		return 1;
	}else{
		return a * factorial(a-1);
	}
}

//import "factorial.js" as MathFunctions
//MouseArea{
//    anchors.fill: parent
//    onClicked: {
//        console.log(MathFunctions.factorial(9));
//    }
//}
