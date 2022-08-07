extends Node

var data:Array = Network.parkarray

var park1:bool
var park2:bool
var park3:bool
var park4:bool


func _process(delta):
	if data.size() > 0:
		if data[0] == 0:
			park1 = true
		else:
			park1 = false
		
		if data[1] == 0:
			park2 = true
		else:
			park2 = false
		
		if data[2] == 0:
			park3 = true
		else:
			park3 = false
		
		if data[3] == 0:
			park4 = true
		else:
			park4 = false
	
