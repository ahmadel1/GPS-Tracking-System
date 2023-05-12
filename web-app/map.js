const pinOut = document.querySelector('#pinOut');
const startBtn = document.getElementById("startBtn");
const tarDistance = document.querySelector("#tdist");
const checkSign = document.querySelector(".bi-check2-circle");
const minSpan = document.getElementById('min');
const secSpan = document.getElementById('sec');
const dirMethodButtons = document.getElementsByClassName("dir-method");
const dirButton = document.getElementById("dirBtn");

var lat;
var long;
var prev_lat = 0;
var prev_long = 0;
var change_in_distance = 0;
var totalDistance = 0;
var i=0;
var map, searchManager;
var realZoom,loc,cen;
var pinFlag=0;
var mydest;
var newPin;
var firstPin;
var firstPinFlag=0;
var remainingDistance=0;
var dirInterval;
var directionsManager,wayPoint,wayPoint1;
var dirFlag = 0;
var l=0; lo=0;

function loadMap() {
    // i++;
    // //change_in_distance=0;
    // lat = (document.getElementsByClassName("loc-span"))[0].innerHTML;
    // long = (document.getElementsByClassName("loc-span"))[1].innerHTML;
    // lat = parseFloat(lat.substring(0,2)) + parseFloat(lat.substring(2))/60;
    // long = parseFloat(long.substring(0,3)) + parseFloat(long.substring(3))/60;
    // change_in_distance = Math.sqrt((Math.abs(lat-prev_lat))**2 + (Math.abs(long-prev_long))**2);  //100000
    // if(i >= 3){
    //     totalDistance+=change_in_distance;
    // }
    // //totalDistance = parseFloat(parseFloat(totalDistance)+parseFloat(change_in_distance));
    // console.log("test",prev_lat,prev_long,change_in_distance);
    // distanceSpan.innerHTML = totalDistance;
    // if(totalDistance >= tarDistance.value){
    //     //start();
    //     checkSign.style.cssText = "display: block;";
    // }
    // console.log(lat,long,"Distance:",totalDistance,change_in_distance);
    // prev_lat = lat;
    // prev_long = long;

    //Initialization and loading
    map =  new window.Microsoft.Maps.Map(document.getElementById('map'), {
        credentials: '',
        center: new window.Microsoft.Maps.Location(0, 0),
        zoom: 1,
    });
    
    //Get the current center and zoom
    Microsoft.Maps.Events.addHandler(map, 'viewchange' , (e)=>{
        realZoom = map.getZoom();
        cen = map.getCenter();
    })
    
    //Add destination
    Microsoft.Maps.Events.addHandler(map,'click',(e)=>{
        if(pinFlag && !(startFlag)){
            map.entities.remove(newPin);
            clearInterval(dirInterval);
        }
        if(e.targetType === "map" && !(startFlag)){
            pinFlag = 1;
            loc = e.location;   
            mydest=loc; console.log(mydest);        
            console.log(loc.latitude, loc.longitude);
            newPin = new Microsoft.Maps.Pushpin(loc,{
                text: 'dest',
            });
            pinOut.innerHTML = loc;
            map.entities.push(newPin);
        }
        
    })

    //Load current position and update the map
    setInterval(async ()=>{
        lat = (document.getElementsByClassName("loc-span"))[0].innerHTML;
        long = (document.getElementsByClassName("loc-span"))[1].innerHTML;
        lat = parseFloat(lat);
        long = parseFloat(long);
        l=lat;
        lo=long;
        Microsoft.Maps.loadModule('Microsoft.Maps.Search', function () {
            var searchManager = new Microsoft.Maps.Search.SearchManager(map);
            var reverseGeocodeRequestOptions = {
                location: new Microsoft.Maps.Location(lat, long),  //lat long <!>
                callback: function (answer, userData) {
                    if(firstPinFlag){
                        map.entities.remove(firstPin);
                    }
                    map.setView({ zoom: realZoom, center: cen });
                    firstPin = new Microsoft.Maps.Pushpin(reverseGeocodeRequestOptions.location);
                    map.entities.push(firstPin);
                    firstPinFlag = 1;
                }
            };
            searchManager.reverseGeocode(reverseGeocodeRequestOptions);
        });
    },2000);

    //Directions and routing
    dirButton.onclick = () => {
        dirFlag++;
        //l = 30.05;
        //lo = 31.5;
        dirInterval = setInterval(()=>{
            lat = (document.getElementsByClassName("loc-span"))[0].innerHTML;
            long = (document.getElementsByClassName("loc-span"))[1].innerHTML;
            lat = parseFloat(lat);
            long = parseFloat(long);
            Microsoft.Maps.loadModule('Microsoft.Maps.Directions', () => {
                directionsManager = new Microsoft.Maps.Directions.DirectionsManager(map);
                //directionsManager.clearAll();
                if(walkingFlag){
                    directionsManager.setRequestOptions({routeMode: Microsoft.Maps.Directions.RouteMode.walking});
                }else if(carFlag){
                    directionsManager.setRequestOptions({routeMode: Microsoft.Maps.Directions.RouteMode.driving});
                }
                    wayPoint = new Microsoft.Maps.Directions.Waypoint({location: new Microsoft.Maps.Location(lat,long)});  //lat long <!>
                    wayPoint1 = new Microsoft.Maps.Directions.Waypoint({location: loc});
                
                    directionsManager.addWaypoint(wayPoint);
                    directionsManager.addWaypoint(wayPoint1);
                    directionsManager.setRenderOptions({autoUpdateMapView: false});
                    directionsManager.calculateDirections();
                    //l+=0.005; lo+=0.005;
            })
        },2000);
        
    }
    

} //loadMap function <---------->


// ----dealing with app functionality----

var mapInterval;
var timerInterval;

var s=0;
var m=0;

function time(){    //time        
    timerInterval = setInterval(()=>{
        if(s === 60){
            s=0;
            m++;
        }else{
            s++;
        }
        minSpan.innerHTML = (m < 10) ? `0${m}` : m;
        secSpan.innerHTML = (s < 10) ? `0${s}` : s;
    },1000);
}

//Choosing the method of setting the destination 

var destFlag,setOnMapFlag;

const destBtn = document.getElementById('destBtn');
const setOnMapBtn = document.getElementById('setOnMapBtn');

function chooseDistination(target){
    startBtn.style.pointerEvents = 'auto';
    tarDistance.style.pointerEvents = 'auto';
    target.style.backgroundColor = '#9fbd9f';
    target.style.border = '1px solid #fff';
    destFlag = 1;
    setOnMapFlag = 0;
    setOnMapBtn.style.backgroundColor = '';
}


function setOnMap(target){
    startBtn.style.pointerEvents = 'auto';
    target.style.backgroundColor = '#9fbd9f';
    target.style.border = '1px solid #fff';
    dirButton.style.pointerEvents = 'auto';
    dirMethodButtons[0].style.pointerEvents = 'auto';
    dirMethodButtons[1].style.pointerEvents = 'auto';
    document.getElementsByClassName('inner-sec')[0].style.cssText = 'box-shadow:2px 2px 2px 2px #39ac39; transition: .5s;';
    destFlag = 0;
    setOnMapFlag = 1;
    destBtn.style.backgroundColor = '';
    setTimeout(()=>{
        document.getElementsByClassName('inner-sec')[0].style.cssText = 'box-shadow: none; transition: .5s;';
    },500)
}

// Choosing direction and direction method

var walkingFlag = 0;
var carFlag = 0;

dirMethodButtons[0].onclick = ()=>{
    dirMethodButtons[0].style.backgroundColor = '#666';
    dirMethodButtons[0].style.color = '#fff';
    
    //dirMethodButtons[1].style.backgroundColor = '#eee';
    //dirMethodButtons[1].style.color = '#000';

    dirMethodButtons[1].style.cssText = 'backgorund-color: #eee;\
    color: #000; pointer-events: auto;';

    walkingFlag = 1;
    carFlag = 0;
}

dirMethodButtons[1].onclick = ()=>{
    dirMethodButtons[1].style.backgroundColor = '#666';
    dirMethodButtons[1].style.color = '#fff';

    // dirMethodButtons[0].style.backgroundColor = '#eee';
    // dirMethodButtons[0].style.color = '#000';

    dirMethodButtons[0].style.cssText = 'backgorund-color: #eee;\
    color: #000; pointer-events: auto;';

    carFlag = 1;
    walkingFlag = 0;
}


//Start

var startFlag=0;
var moveInterval;
const distanceSpan = document.querySelector("#distance-span");
var remSpan = document.getElementById('remDistance-span');

function start(){
    if(startFlag){ //if already started
        startFlag = 0;
        clearInterval(timerInterval);
        startBtn.innerHTML = 'Start';
    }else{  //if we haven't started
        time();
        startFlag = 1;
        startBtn.innerHTML = 'End';
        setTimeout(()=>{
            if(destFlag){
                Int=setInterval(()=>{
                    if(tarDistance - parseFloat(distanceSpan.innerHTML) <= 5){
                        done();
                        clearInterval(timerInterval);
                        clearInterval(Int);
                    }
                },600)
            }else if(setOnMapFlag){
                Int=setInterval(()=>{
                    if(parseFloat(remSpan.innerHTML) <= 5){
                        done();
                        clearInterval(timerInterval);
                        clearInterval(Int);
                    }
                     
                },600);
              
            }
        },3000);
    }
    
}

doneDiv = document.getElementById("done-div");
var xDiv = document.getElementById("cover");

function done(){    //When target is reached
    //alert("You have reached your target");
    finalDistanceMoved = document.getElementById("f-dist");
    finalTime = document.getElementById("f-time");
    timeSpan = document.getElementById("time-span");
    doneDiv.style.cssText = 'top: 50%; visibility: visible; transition: 0.5s; z-index: 1;';
    xDiv.style.display = 'block';
    finalDistanceMoved.innerHTML = distanceSpan.innerHTML;
    finalTime.innerHTML = timeSpan.innerHTML;
}

doneBtn = document.getElementById("doneBtn");
doneBtn.onclick = () =>{
    window.location.reload();
    //alert("aa");
}

startBtn.addEventListener('click', ()=>{
    start();
});

next = document.getElementById("next-btn");

next.onclick = ()=>{
    doneDiv.style.cssText = 'top: -50%; visibility: hidden; transition: 0.5s; z-index: 1;';
    xDiv.style.display = 'none';
}



/* ---------------------------------------DONE---------------------------------------*/





// function loadMap() {
//     var map = new Microsoft.Maps.Map(document.getElementById('map'), {});
//     Microsoft.Maps.loadModule('Microsoft.Maps.Search', function () {
//         var searchManager = new Microsoft.Maps.Search.SearchManager(map);
//         var reverseGeocodeRequestOptions = {
//             location: new Microsoft.Maps.Location(47.640049, -122.129797),
//             callback: function (answer, userData) {
//                 map.setView({ bounds: answer.bestView });
//                 map.entities.push(new Microsoft.Maps.Pushpin(reverseGeocodeRequestOptions.location));
//                 // document.getElementById('printoutPanel').innerHTML =
//                 //     answer.address.formattedAddress;
//             }
//         };
//         searchManager.reverseGeocode(reverseGeocodeRequestOptions);
//     });
    
// }









// if(startBtn.innerText === 'End'){
//     startBtn.innerText = 'Start';
//     clearInterval(mapInterval);
//     clearInterval(timerInterval);
//     tarDistance.style.pointerEvents = "none";
// }else{      //Start
//     tarDistance.style.pointerEvents = "none";
//     startBtn.innerText = 'End';
//     time();
//     mapInterval = setInterval(async ()=>{    
//         console.log("started");
//         script = document.createElement('script');
//         script.setAttribute('type', "text/javascript");
//         await script.setAttribute('src', 'https://www.bing.com/maps/sdkrelease/mapcontrol?key=ArtTkyF0p5bHRAbITAYKbrugOSmjJzFx7rn_H3nzqyfRhkPFisi2-rE-EiWwxsVI&callback=loadMap');
//         document.head.appendChild(script);
//     },1000)
// }












// function start(destFlag, setOnMapFlag, mydest){    
//     if(startFlag){      //If you started,when clicked, then stop.
//         clearInterval(moveInterval);
//         startFlag = 0;
//         startBtn.innerHTML = 'Start';
//         clearInterval(timerInterval);
//     }else{      //If you still didn't start, then start.
//         startFlag = 1;
//         time();
//         startBtn.innerHTML = 'End';
//         moveInterval = setInterval(()=>{
//             if(destFlag){
//                 i++;
//                 //change_in_distance=0;
//                 lat = (document.getElementsByClassName("loc-span"))[0].innerHTML;
//                 long = (document.getElementsByClassName("loc-span"))[1].innerHTML;
//                 lat = parseFloat(lat.substring(0,2)) + parseFloat(lat.substring(2))/60;
//                 long = parseFloat(long.substring(0,3)) + parseFloat(long.substring(3))/60;
//                 change_in_distance = Math.sqrt((Math.abs(lat-prev_lat))**2 + (Math.abs(long-prev_long))**2) * 111139;  //100000
//                 if(i >= 3){
//                     totalDistance+=change_in_distance;
//                     remainingDistance = tarDistance - totalDistance;
//                 }
//                 //totalDistance = parseFloat(parseFloat(totalDistance)+parseFloat(change_in_distance));
//                 console.log("test",prev_lat,prev_long,change_in_distance);
//                 //distanceSpan.innerHTML = totalDistance;
//                 if(totalDistance >= tarDistance.value){
//                     done();       
//                     start();
//                     checkSign.style.cssText = "display: block;";
//                 }
//                 remSpan.innerHTML = remainingDistance;
//                 console.log(lat,long,"Distance:",totalDistance,change_in_distance,remainingDistance);
//                 prev_lat = lat;
//                 prev_long = long;  
//             }else if(setOnMapFlag){
//                 i++;
//                 //change_in_distance=0;
//                 lat = (document.getElementsByClassName("loc-span"))[0].innerHTML;
//                 long = (document.getElementsByClassName("loc-span"))[1].innerHTML;
//                 lat = parseFloat(lat.substring(0,2)) + parseFloat(lat.substring(2))/60;
//                 long = parseFloat(long.substring(0,3)) + parseFloat(long.substring(3))/60;
//                 change_in_distance = Math.sqrt((Math.abs(lat-prev_lat))**2 + (Math.abs(long-prev_long))**2) * 111139;  //100000
//                 if(i >= 3){
//                     totalDistance+=change_in_distance;
//                     remainingDistance = Math.sqrt((Math.abs(mydest.latitude - lat))**2 + (Math.abs(mydest.longitude - long))**2) * 111139;
//                 }
//                 //totalDistance = parseFloat(parseFloat(totalDistance)+parseFloat(change_in_distance));
//                 console.log("test",prev_lat,prev_long,change_in_distance);
//                 //distanceSpan.innerHTML = totalDistance;
//                 if(remainingDistance <= 15 && remainingDistance !== 0){
//                     console.log('rem',remainingDistance);
//                     done();       
//                     start();
//                 }
//                 //remSpan.innerHTML = remainingDistance;
//                 console.log(lat,long,"Distance:",totalDistance,change_in_distance,remainingDistance);
//                 prev_lat = lat;
//                 prev_long = long;
//             }
//     },1000);  
//     }
        
// }