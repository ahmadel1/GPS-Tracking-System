const myBtn = document.getElementById("cbtn");
startBtn = document.getElementById("startBtn");
movedDistance_span = document.getElementById("distance-span");
remainingDistance_span = document.getElementById("remDistance-span");
var port;


// if("serial" in navigator){
//     console.log("Serial");
// }



var stxt="";

myBtn.addEventListener("click" , async ()=>{
    port = await navigator.serial.requestPort();
    await port.open({baudRate:9600});

    const textDecoder = new TextDecoderStream();
    const readableStreamClosed = port.readable.pipeTo(textDecoder.writable);
    const reader = textDecoder.readable.getReader();
    
try{
    while(true){
        const {value, done} = await reader.read();
        if(done){
            reader.releaseLock();
            break;
        }else{
            stxt+=value;
            //textArea.innerHTML = stxt;
        }
    }
    
}catch(e){
    console.log("Error" + e);
}
})

startBtn.onclick = async ()=>{
    const textEncoder = new TextEncoderStream();
    const writableStreamClosed = textEncoder.readable.pipeTo(port.writable);
    const writer = textEncoder.writable.getWriter();
    
    finalCoords = document.getElementById("pinOut").innerHTML;
    console.log(finalCoords);  
    final = finalCoords.substring(finalCoords.indexOf('(')+1,finalCoords.indexOf(')'));
    //final+=" ";
    [latitude,longitude] = final.split(", ");
    console.log(latitude);
    console.log(longitude);
    newFinal = latitude.substring(0,latitude.indexOf('.')+7) + "," + longitude.substring(0,longitude.indexOf('.')+7) + " "; 
    await writer.write(newFinal).then((r)=>{console.log(r)});
    writer.releaseLock();

    showData();
}

const coords = document.getElementsByClassName('loc-span');


setLocInt = setInterval(()=>{
    console.log(stxt);
    [latitude,longitude] = stxt.split(",");
    coords[0].innerHTML = latitude;
    coords[1].innerHTML = longitude;  
},4000);

showData = () =>{
    setInterval(()=>{  
        console.log(stxt);    
        [latitude,longitude,movedDistance,remainingDistance] = stxt.split(",");
        for(i=0;i<100;i++){}
        coords[0].innerHTML = latitude;
        coords[1].innerHTML = longitude.substring(0);
        movedDistance_span.innerHTML = movedDistance.substring(0);
        remainingDistance_span.innerHTML = remainingDistance.substring(0,remainingDistance.indexOf('-'));
        stxt="";
    },1300);
}
