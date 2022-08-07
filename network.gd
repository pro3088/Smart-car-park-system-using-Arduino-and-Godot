extends Control

export (NodePath) var dropdown_path
onready var dropdown = get_node(dropdown_path)


var array = ["null","Test park"]

func _ready():
	dropdown.connect("item_selected",self,"on_item_selected")
	addDropdown()


func addDropdown():
	for item in array:
		dropdown.add_item(item)
	

func on_item_selected(id):
	if id == 1 :
		print(true)
		Network.ip = "192.168.1.184"
		Network.port = 80
	pass


func _on_Button_pressed():
	Network.setupUDP()
	if Network.connected:
		pass
