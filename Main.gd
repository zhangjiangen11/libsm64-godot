extends Spatial


export var sm64_handler: Resource

onready var rom_picker: FileDialog = $FileDialog


func _ready():
	rom_picker.popup_centered()
	yield(rom_picker, "file_selected")
	sm64_handler.rom_filename = rom_picker.current_path
	
	sm64_handler.global_init()
	load_static_sufaces()
	for mario in get_tree().get_nodes_in_group("Mario"):
		mario.create()


func load_static_sufaces() -> void:
	var faces := PoolVector3Array()
	
	for mesh_instance in get_tree().get_nodes_in_group("static_surfaces"):
		var mesh_faces: PoolVector3Array = mesh_instance.get_mesh().get_faces()
		var offset: Vector3 = mesh_instance.global_transform.origin
		for i in range(mesh_faces.size()):
			mesh_faces[i] += offset
		faces.append_array(mesh_faces)
	
	sm64_handler.static_surfaces_load(faces)
