extends Position2D

export(float) var SPEED = 200.0

enum STATES { IDLE, FOLLOW }
var _state = null

onready var startpos = get_parent().get_node("startpos").position

var path = []
var target_point_world = Vector2()
var target_position = Vector2()

var velocity = Vector2()

var movemark:bool

func _ready():
	_change_state(STATES.IDLE)


func _change_state(new_state):
	if new_state == STATES.FOLLOW:
		path = get_parent().get_node('TileMap').find_path(position, target_position)
		if not path or len(path) == 1:
			_change_state(STATES.IDLE)
			return
		# The index 0 is the starting cell
		# we don't want the character to move back to it in this example
		target_point_world = path[1]
	_state = new_state


func _process(delta):
	if not _state == STATES.FOLLOW:
		if movemark == true:
			yield(get_tree().create_timer(2), "timeout")
			self.position = startpos
			self.rotation_degrees = 90
		movemark = false
		return
	var arrived_to_next_point = move_to(target_point_world)
	if arrived_to_next_point:
		path.remove(0)
		if len(path) == 0:
			_change_state(STATES.IDLE)
			return
		target_point_world = path[0]


func move_to(world_position):
	var MASS = 10.0
	var ARRIVE_DISTANCE = 10.0

	var desired_velocity = (world_position - position).normalized() * SPEED
	var steering = desired_velocity - velocity
	velocity += steering / MASS
	position += velocity * get_process_delta_time()
	rotation = velocity.angle()
	return position.distance_to(world_position) < ARRIVE_DISTANCE

#
#func _input(event):
#	if event.is_action_pressed('click'):
#		if Input.is_key_pressed(KEY_SHIFT):
#			global_position = get_global_mouse_position()
#		else:
#			target_position = get_canvas_transform().affine_inverse().xform(event.position)
#		_change_state(STATES.FOLLOW)


func _on_Area2D_input_event(viewport, event, shape_idx):
	if event.is_action_pressed('click'):
		target_position = get_canvas_transform().affine_inverse().xform(event.position)
		_change_state(STATES.FOLLOW)
		movemark = true
