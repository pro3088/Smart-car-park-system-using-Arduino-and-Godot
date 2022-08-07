# Smart-car-park-system-using-Arduino-and-Godot


## Brief Description
This system includes a controller, an arduino microcontroller, and an app. The objective of this project is to make the parking system less stressful. This system employs sensors linked to an Arduino board to alert an app when a parking space becomes available, utilizing a Nodemcu board as a gateway.

The nodemcu connects to the app over a TCP connection. Due to this connection's non-static IP address, the app's IP address will also need to be modified frequently.

## Explanation of working concepts
Like earlier explained the code is broken into three parts:
1. App
2. Arduino
3. Nodemcu

### APP
The Godot game engine was used to create the app. This decision was made because it was simpler to develop and because the engine already had capabilities that made navigating the parking lot and finding a parking space straightforward. 

https://github.com/GDQuest/godot-demos/tree/master/2018/03-30-astar-pathfinding <- A-star algorithm with Godot

#### Car park app UI design 
![Car-park-app](https://user-images.githubusercontent.com/53413092/183291688-407df368-8f3d-4209-a0af-be952ffad949.jpg)

#### Car park app Implemented
![smart car park](https://user-images.githubusercontent.com/53413092/183291960-cce83286-76a6-4d60-8fde-1d703eb9fe61.PNG)

As can be seen in the image above, the software has a place where users can enter the IP addresses. Even if this is not the ideal circumstance, it will be useful for testing. Static IP addresses have the drawback of making it difficult for a program to maintain a connection to the nodemcu over time.

#### Code samples

```
func setupUDP():
	if port != null and ip != "":
		UdpSocket.connect_to_host(ip,port)
		if UdpSocket.is_connected_to_host():
			print("connection is made to :", ip,"  ",port)
			connected = true
		else:
			print("please retry, connection wasn't successful")
			connected = false

func sendData(data):
	if UdpSocket.is_listening():
		var pac = data.to_ascii()
		print("pac data: ", pac)
		UdpSocket.put_packet(pac)

func receiveData():
	if UdpSocket.is_connected_to_host():
		var asciiMessage = UdpSocket.get_packet()
		message = asciiMessage.get_string_from_ascii()
		print("This is the message: ", message)
```
Through handshaking, this part manages the TCP socket connection. To the nodemcu ip address, the application delivers ascii data. The connection is established if the nodemcu gets that IP address and sends a message with a similar structure.

```
func _process(delta):
	if connected:
		runApp()

func runApp():
	if Network.connected:
		Network.sendData("Connection made")
		Network.receiveData()
		if Network.message != "":
			get_tree().change_scene("res://Game.tscn")
			connected = true
			pass
		else:
			print("not connected")
			connected = false

func _on_Button_pressed():
	Network.ip = $VBoxContainer/VBoxContainer/LineEdit.text
	Network.port = 4201
	Network.setupUDP()
	runApp()

func _on_back_button_pressed():
	get_tree().change_scene("res://UI/main.tscn")
```

When the button is pressed, several events happen. First, the IP address is obtained from the input area.The ascii data is delivered, ascii data is received, ascii data is converted to a readable format, and finally the message is checked to make sure it is not null.

Upon completion of this procedure, you can locate your parking space.
This portion was my main contribution to the project because I assisted a classmate with its execution.

### Arduino

```
void IRsensor(){
  if(digitalRead(park1)== HIGH){
      parks1 = 1;
    }
    else{
      parks1 = 0;
    }
  
    //........................................
    if(digitalRead(park2)== HIGH){
      parks2 = 1;
    }
    else{
      parks2 = 0;
    }
  
    //........................................
    if(digitalRead(park3)== HIGH){
      parks3 = 1;
    }
    else{
      parks3 = 0;
    }
  
    //........................................
    if(digitalRead(park4)== HIGH){
      parks4 = 1;
    }
    else{
      parks4 = 0;
    }

    reply[0] = parks1;
    reply[1] = parks2;
    reply[2] = parks3;
    reply[3] = parks4;
    
    sprintf(str, "%u,%u,%u,%u", reply[0],reply[1],reply[2],reply[3]);
}
```
a method named IR sensors was created in the arduino code to handle the sensors input, the data is then sent to the nodemcu in f format (ascii)

###Nodemcu

```
 
void loop() 
{
  if (Serial.available()){
      string = Serial.readString();
      string.toCharArray(str, 128);
      Serial.print(str);
    }
  
    int packetSize = UDP.parsePacket();
    if(packetSize)
    {   
      Serial.print("Received packet of size ");
      Serial.println(packetSize);
      Serial.print("From ");
      IPAddress remoteIp = UDP.remoteIP();
      Serial.print(remoteIp);
      Serial.print(", port ");
      Serial.println(UDP.remotePort());
  
      // read the packet into packetBufffer
      int len = UDP.read(packet,255);
      if (len >0) packet[len]=0;
      Serial.println("Contents:");
      Serial.println(packet);
      
      // send a reply, to the IP address and port that sent us the packet we received
      UDP.beginPacket(UDP.remoteIP(), UDP.remotePort());
      Serial.println("sending :");
      Serial.println(str);
      UDP.write(str);
      UDP.endPacket();
     }
}
```

In the nodemcu loop function, the serial monitor is regularly checked if the input from the arduino has changed
```
 int len = UDP.read(packet,255);
      if (len >0) packet[len]=0;
      Serial.println("Contents:");
      Serial.println(packet);
```
This section checks if ascii data has been received from the app.
A reply is the sent to the app. 

## How to contribute
The Ip address configuration still needs a lot of work. Making the Ip address static and functional will be a good addition.

## Special Mention
https://github.com/GDQuest
