extends Control

export (NodePath) var dropdown_path
onready var dropdown = get_node(dropdown_path)

var connected:bool = false

#var array = ["null","Test park"]
#
#func _ready():
#	dropdown.connect("item_selected",self,"on_item_selected")
#	addDropdown()
#
#
#func addDropdown():
#	for item in array:
#		dropdown.add_item(item)
#
#
#func on_item_selected(id):
#	if id == 1 :
#		Network.ip = "192.168.43.145"
#		Network.port = 4201
#	else:
#		Network.ip = ""
#		Network.port = ""

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
