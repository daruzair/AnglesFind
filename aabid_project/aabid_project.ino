#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

ESP8266WebServer esp(80);
IPAddress ipAddress;

String UserName="mining";
String Password="miningrigpassword";

const int Angle1 = 13;          //D0
const int Angle2 = 14;           //D1
const int Angle3 = 12;           //D2
const int Angle4 = 2;           //D3
const int Angle5 = 16;           //D4
const int Angle6 = 4;          //D5
const int Angle7 = 5;          //D6
const int Angle8 = 0;          //D7

void setup() {
  Serial.begin(115200);
  SetPinMode();
  ConnectWifi();
  esp.on("/",processRoot);
  esp.on("/ia",HTTP_POST,interiorAngle);
  esp.on("/ea",HTTP_POST,exteriorAngle);
  esp.on("/voc",HTTP_POST,verticallyOppositeAngles);
  esp.on("/ca",HTTP_POST,correspondingAngles);
  esp.on("/aia",HTTP_POST,alternateInteriorAngles);
  esp.on("/aea",HTTP_POST,alternateExteriorAngles);
  esp.begin();
}
void processRoot(){
  esp.send(200,"text/html",WebPage());
}
void interiorAngle(){
  String id = esp.arg("id");
  digitalWrite(Angle3,!digitalRead(Angle3));
  digitalWrite(Angle4,!digitalRead(Angle4));
  digitalWrite(Angle5,!digitalRead(Angle5));
  digitalWrite(Angle6,!digitalRead(Angle6));
  esp.send(200,"text/html","success");
}
void exteriorAngle(){
  String id = esp.arg("id");
  digitalWrite(Angle1,!digitalRead(Angle1));
  digitalWrite(Angle2,!digitalRead(Angle2));
  digitalWrite(Angle7,!digitalRead(Angle7));
  digitalWrite(Angle8,!digitalRead(Angle8));
  esp.send(200,"text/html","success");
}
void verticallyOppositeAngles(){
  String id = esp.arg("id");
  if(id=="1" || id=="4"){
    digitalWrite(Angle1,!digitalRead(Angle1));
    digitalWrite(Angle4,!digitalRead(Angle4));
  }else if(id=="2" || id=="3"){
    digitalWrite(Angle2,!digitalRead(Angle2));
    digitalWrite(Angle3,!digitalRead(Angle3));
  }else if(id=="5" || id=="8"){
    digitalWrite(Angle5,!digitalRead(Angle5));
    digitalWrite(Angle8,!digitalRead(Angle8));
  }else if(id=="6" || id=="7"){
    digitalWrite(Angle6,!digitalRead(Angle6));
    digitalWrite(Angle7,!digitalRead(Angle7));
  }
  esp.send(200,"text/html","success");
}
void correspondingAngles(){
  String id = esp.arg("id");
  if(id=="1" || id=="5"){
    digitalWrite(Angle1,!digitalRead(Angle1));
    digitalWrite(Angle5,!digitalRead(Angle5));
  }else if(id=="2" || id=="6"){
    digitalWrite(Angle2,!digitalRead(Angle2));
    digitalWrite(Angle6,!digitalRead(Angle6));
  }else if(id=="3" || id=="7"){
    digitalWrite(Angle3,!digitalRead(Angle3));
    digitalWrite(Angle7,!digitalRead(Angle7));
  }else if(id=="4" || id=="8"){
    digitalWrite(Angle4,!digitalRead(Angle4));
    digitalWrite(Angle8,!digitalRead(Angle8));
  }
  esp.send(200,"text/html","success");
}
void alternateInteriorAngles(){
  String id = esp.arg("id");
  if(id=="3" || id=="6"){
    digitalWrite(Angle3,!digitalRead(Angle3));
    digitalWrite(Angle6,!digitalRead(Angle6));
  }else if(id=="4" || id=="5"){
    digitalWrite(Angle4,!digitalRead(Angle4));
    digitalWrite(Angle5,!digitalRead(Angle5));
  }
  esp.send(200,"text/html","success");
}
void alternateExteriorAngles(){
  String id = esp.arg("id");
  if(id=="1" || id=="8"){
    digitalWrite(Angle1,!digitalRead(Angle1));
    digitalWrite(Angle8,!digitalRead(Angle8));
  }else if(id=="2" || id=="7"){
    digitalWrite(Angle2,!digitalRead(Angle2));
    digitalWrite(Angle7,!digitalRead(Angle7));
  }
  esp.send(200,"text/html","success");
}
void loop() {
   esp.handleClient();
   delay(50);
}

void SetPinMode(){
  pinMode(Angle1,OUTPUT);
  pinMode(Angle2,OUTPUT);
  pinMode(Angle3,OUTPUT);
  pinMode(Angle4,OUTPUT);
  pinMode(Angle5,OUTPUT);
  pinMode(Angle6,OUTPUT);
  pinMode(Angle7,OUTPUT);
  pinMode(Angle8,OUTPUT);
}
void ConnectWifi(){
 //Turn on ESP8266 station mode: connecting to WiFi Hot sopt
 WiFi.begin(UserName,Password);

 //Stop ESP from running unless connected to HOTSPOT
 Serial.println("Loading");
 int times=0;
 while(WiFi.status() != WL_CONNECTED){
  DoubleBlink(HIGH);
  delay(300);
  DoubleBlink(LOW);
  times++;
  if(times==10){
    Serial.println();
    times=0;
  }
  Serial.print(".");
  delay(300);
 }
 blinkLeds(LOW);
 Serial.println();
 Serial.println("Ready");
 ipAddress=WiFi.localIP();
 Serial.println(ipAddress);
}
void DoubleBlink(int Cmd){
  digitalWrite(Angle1,!Cmd);
  digitalWrite(Angle2,Cmd);
  digitalWrite(Angle3,Cmd);
  digitalWrite(Angle4,!Cmd);
  digitalWrite(Angle5,!Cmd);
  digitalWrite(Angle6,Cmd);
  digitalWrite(Angle7,Cmd);
  digitalWrite(Angle8,!Cmd);
}
void blinkLeds(int Cmd){
  digitalWrite(Angle1,Cmd);
  digitalWrite(Angle2,Cmd);
  digitalWrite(Angle3,Cmd);
  digitalWrite(Angle4,Cmd);
  digitalWrite(Angle5,Cmd);
  digitalWrite(Angle6,Cmd);
  digitalWrite(Angle7,Cmd);
  digitalWrite(Angle8,Cmd);
}
String WebPage(){
  String page=R"(<!DOCTYPE html>
<html lang='en'>
    <head>
        <meta charset='UTF-8'>
        <meta http-equiv='X-UA-Compatible' content='IE=edge'>
        <meta name='viewport' content='width=device-width, initial-scale=1.0'>
        <link href='https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.0.0/css/all.min.css'
        rel='stylesheet'>
        <title>Types Of Angle</title>
        <style>
            .creater{
                position: fixed;
                bottom: 5%;
                right: 5%;
                color: rgb(141, 141, 141);
                font-style: italic;
            }
            .creater span:last-child{
                font-style: italic;
            }
            .btn{
                cursor: pointer;
                background-color: transparent;
                border: 1px solid black;
                padding: 0.5rem 1rem;
                border-radius: 3px;
                display: inline-block;
                transition: .3s background linear;
                box-shadow: 0px 20px 15px -10px gray;
            }

        .btn:hover{
           
            color: #f0f0f0;
            animation:  btn-animate .9s .1s linear forwards;
        }
        @keyframes btn-animate {
            0%{
                transform: scaleX(1) scaleY(1);
            }
            15%{
                transform: scaleX(1.5) scaleY(0.5);
            }
            30%{
                transform: scaleX(0.75) scaleY(1.25);
            }
            50%{
                transform: scaleX(1.15) scaleY(0.85);
            }
            75%{
                transform: scaleX(0.9) scaleY(1.1);
            }
            100%{
                transform: scaleX(1) scaleY(1);
            }



        }
            *{
                padding: 0%;
                margin: 0%;
                box-sizing: border-box;
                user-select: none;
            }
            body{
                width: 100%;
                background-color: rgb(34, 34, 37);
            }
            .main{
                display: flex;
                justify-content: center;
                flex-direction: column;
                align-items: center;
                margin: 30px;
            }
            .wrapper{
                display: flex;
                margin: 5px;
            }
            .section{
                margin-top: 20px;
            }
            .box:hover{
                cursor:pointer;
            }
            h3{
                color: white;
            }
            .box{
                margin: 1px 7px;
                min-width: 55px;
                padding: 15px;
                height: 45px;
                box-shadow: inset 1px 1px 6px 0 #fff,
                        inset 0px 0px 6px 0 #000;
                display: flex;  
                align-items: center;
                justify-content: center;
                border-radius: 10%;
                transition: 0.5s all ease;
            }
            .button .active{
                box-shadow: inset 0px 0px 6px 0 #fff,
                        inset 1px 1px 6px 0 #000; 
            }
            .active h3{
                color: #0ff;
                text-shadow: 0px 0px 5px #0ff;
                transition: 0.5s all ease;
            }
            .content{
                font-size: 1.1rem;
                color: white;
                text-align: center;
                margin-bottom: 10px;
                text-decoration: underline;
            }
            .main>.content{
                font-size: 1.5rem;
                border-bottom: 1px solid white;
                margin: 0;
            }
            
        </style>
    </head>
    <body>
        <main class='main'>       
            <div class="content">Types Of Angles</div>
            <div class="section interior-angles">
                <div class='wrapper'>
                    <div class='button'>
                        <div id='i' class='box btn'>
                            <h3>Interior &#8736;`s</h3>
                        </div>
                    </div>
                    <div class='button'>
                        <div id='e' class='box btn'>
                            <h3>Exterior &#8736;`s</h3>   
                        </div>
                    </div>
                    
                </div>
            </div>
            <div class="section vertically-opposite-angles">
                <div class="content">Vertically Opposite Angles</div>
                <div class='wrapper'>
                    <div class='button'>
                        <div id='1' class='box btn'>
                            <h3>&#8736; 1</h3>
                        </div>
                    </div>
                    <div class='button'>
                        <div id='2' class='box btn'>
                            <h3>&#8736; 2</h3>
                        </div>
                    </div>
                    <div class='button'>
                        <div id='3' class='box btn'>
                            <h3>&#8736; 3</h3>
                        </div>
                    </div>
                    <div class='button'>
                        <div id='4' class='box btn'>
                            <h3>&#8736; 4</h3>   
                        </div>
                    </div>
                </div>
                <div class='wrapper'>
                    <div class='button'>
                        <div id='5' class='box btn'>
                            <h3>&#8736; 5</h3>
                        </div>
                    </div>
                    <div class='button'>
                        <div id='6' class='box btn'>
                            <h3>&#8736; 6</h3>
                        </div>
                    </div>
                    <div class='button'>
                        <div id='7' class='box btn'>
                            <h3>&#8736; 7</h3>
                        </div>
                    </div>
                    <div class='button'>
                        <div id='8' class='box btn'>
                            <h3>&#8736; 8</h3>
                        </div>
                    </div>
                </div>
            </div>
            <div class="section corresponding-angles">
                <div class="content">Corresponding Angles</div>
                <div class='wrapper'>
                    <div class='button'>
                        <div id='1' class='box btn'>
                            <h3>&#8736; 1</h3>
                        </div>
                    </div>
                    <div class='button'>
                        <div id='2' class='box btn'>
                            <h3>&#8736; 2</h3>
                        </div>
                    </div>
                    <div class='button'>
                        <div id='3' class='box btn'>
                            <h3>&#8736; 3</h3>
                        </div>
                    </div>
                    <div class='button'>
                        <div id='4' class='box btn'>
                            <h3>&#8736; 4</h3>   
                        </div>
                    </div>
                </div>
                <div class='wrapper'>
                    <div class='button'>
                        <div id='5' class='box btn'>
                            <h3>&#8736; 5</h3>
                        </div>
                    </div>
                    <div class='button'>
                        <div id='6' class='box btn'>
                            <h3>&#8736; 6</h3>
                        </div>
                    </div>
                    <div class='button'>
                        <div id='7' class='box btn'>
                            <h3>&#8736; 7</h3>
                        </div>
                    </div>
                    <div class='button'>
                        <div id='8' class='box btn'>
                            <h3>&#8736; 8</h3>
                        </div>
                    </div>
                </div>
            </div>
            <div class="section alternate-interior-angles">
                <div class="content">Alternate Interior Angles</div>
                <div class='wrapper'>                    
                    <div class='button'>
                        <div id='3' class='box btn'>
                            <h3>&#8736; 3</h3>
                        </div>
                    </div>
                    <div class='button'>
                        <div id='4' class='box btn'>
                            <h3>&#8736; 4</h3>   
                        </div>
                    </div>
                    <div class='button'>
                        <div id='5' class='box btn'>
                            <h3>&#8736; 5</h3>
                        </div>
                    </div>
                    <div class='button'>
                        <div id='6' class='box btn'>
                            <h3>&#8736; 6</h3>
                        </div>
                    </div>
                </div>
            </div>
            <div class="section alternate-exterior-angles">
                <div class="content">Alternate Exterior Angles</div>
                <div class='wrapper'>
                    <div class='button'>
                        <div id='1' class='box btn'>
                            <h3>&#8736; 1</h3>
                        </div>
                    </div>
                    <div class='button'>
                        <div id='2' class='box btn'>
                            <h3>&#8736; 2</h3>
                        </div>
                    </div>
                    <div class='button'>
                        <div id='7' class='box btn'>
                            <h3>&#8736; 7</h3>
                        </div>
                    </div>
                    <div class='button'>
                        <div id='8' class='box btn'>
                            <h3>&#8736; 8</h3>
                        </div>
                    </div>
                </div>
               
            </div>
        </main>
        <div class="creater">
                <span>Created by :</span> <span>Aabid Fayaz</span>
        </div>
    </body>
    <script>
        let interiorAngle=document.querySelector("#i");
        let exteriorAngle=document.querySelector("#e");
        let verticallyOppositeAngles=document.querySelectorAll(".vertically-opposite-angles .box");
        let correspondingAngles=document.querySelectorAll(".corresponding-angles .box");
        let alternateInteriorAngles=document.querySelectorAll(".alternate-interior-angles .box");
        let alternateExteriorAngles=document.querySelectorAll(".alternate-exterior-angles .box");
        
        interiorAngle.addEventListener("click",function(event){
               const supers=this;
                executeCommand(this.id,"ia",function(){
                    supers.classList.toggle("active");
                });
            });
        exteriorAngle.addEventListener("click",function(event){
            const supers=this;
            executeCommand(this.id,"ea",function(){
                supers.classList.toggle("active");
            });
        });

        verticallyOppositeAngles.forEach(function(voa){
            
            voa.addEventListener("click",function(event){
               const supers=this;
                executeCommand(this.id,"voc",function(){
                    supers.classList.toggle("active");
                });
            });
        });
        correspondingAngles.forEach(function(ca){

            ca.addEventListener("click",function(event){
               const supers=this;
                executeCommand(this.id,"ca",function(){
                    supers.classList.toggle("active");
                });
            }); 
        });
        alternateInteriorAngles.forEach(function(aia){

            aia.addEventListener("click",function(event){
               const supers=this;
                executeCommand(this.id,"aia",function(){
                    supers.classList.toggle("active");
                });
            });   
        });
        alternateExteriorAngles.forEach(function(aea){

            aea.addEventListener("click",function(event){
               const supers=this;
                executeCommand(this.id,"aea",function(){
                    supers.classList.toggle("active");
                });
            }); 
        });

        function executeCommand(id,command,responcefunc){
            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function() {
                if (this.readyState == 4 && this.status == 200) {
                    responcefunc();
                }
            }
            xhttp.open('POST', '/'+command, true );
            xhttp.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
            
            xhttp.send('id='+id);
        }
    </script>
</html>

)";
  return page;
}
