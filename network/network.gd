extends Node
var UdpSocket = PacketPeerUDP.new()
var port 
var ip 
var connected:bool = false
var message
var timer
var parkarray:Array

#func _ready():
#	ip = "192.168.25.61"
#	port = 4201
#	setupUDP()
#
#
#func _process(delta):
#	sendData("connection made")
#	receiveData()


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


func separateData():
	if message != null:
		parkarray = message.split(",")

