extends Node

onready var park1pos = $"park 1".position
onready var park2pos = $"park 2".position
onready var park3pos= $"park 3".position
onready var park4pos= $"park 4".position


var carpreset = preload("res://car.tscn")

var car1
var car2
var car3
var car4

func _process(delta):
#	getdata()
	
	if ProcessData.park1:
		car1 = carpreset.instance()
		add_child(car1)
		car1.position = park1pos
		
	else:
		if is_instance_valid(car1):
			car1.queue_free()
	
	if ProcessData.park2:
		car2 = carpreset.instance()
		add_child(car2)
		car2.position = park2pos
	else:
		if is_instance_valid(car2):
			car2.queue_free()
	
	if ProcessData.park3:
		car3 = carpreset.instance()
		add_child(car3)
		car3.position = park3pos
	else:
		if is_instance_valid(car3):
			car3.queue_free()
	
	if ProcessData.park4:
		car4 = carpreset.instance()
		add_child(car4)
		car4.position = park4pos
	else:
		if is_instance_valid(car4):
			car4.queue_free()

func getdata():
	Network.sendData("send values")
	Network.receiveData()

func _on_Button_pressed():
	get_tree().change_scene("res://UI/network.tscn")
