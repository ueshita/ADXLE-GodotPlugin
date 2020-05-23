extends Node

onready var CriAtomExContext = preload("res://addons/adx2le/src/CriAtomExContext.gdns")
onready var CriAtomExVoicePool = preload("res://addons/adx2le/src/CriAtomExVoicePool.gdns")
onready var CriAtomExAcb = preload("res://addons/adx2le/src/CriAtomExAcb.gdns")
onready var CriAtomExPlayer = preload("res://addons/adx2le/src/CriAtomExPlayer.gdns")
onready var CriAtomEx3dSource = preload("res://addons/adx2le/src/CriAtomEx3dSource.gdns")
onready var CriAtomEx3dListener = preload("res://addons/adx2le/src/CriAtomEx3dListener.gdns")
onready var CriAtomExCategory = preload("res://addons/adx2le/src/CriAtomExCategory.gdns")

var context
var voice_pool_memory
var voice_pool_stream
var acb
var player
var category


func _ready():
	# Setup Library
	context = CriAtomExContext.new();
	context.initialize("res://sound/DemoProj.acf", {
		"max_streams": 8,
		"max_virtual_voices": 100,
	})
	
	# Setup Voice Pool
	voice_pool_memory = CriAtomExVoicePool.new()
	voice_pool_memory.allocate_standard_voice_pool({"num_voices": 32, "max_sampling_rate": 96000})
	voice_pool_stream = CriAtomExVoicePool.new()
	voice_pool_stream.allocate_standard_voice_pool({"num_voices": 8, "max_sampling_rate": 96000})
	
	# Load ACB file
	acb = CriAtomExAcb.new()
	acb.load_acb_file("res://sound/DemoProj.acb", "res://sound/DemoProj.awb")
	
	# Setup Player
	player = CriAtomExPlayer.new()
	player.create()
	
	# Category
	category = CriAtomExCategory.new()
	category.set_name("BGM")


func play(cue: int):
	player.set_cue_id(acb, cue)
	return player.start()


func stop_all():
	player.stop()


func pause_all(paused: bool):
	player.pause(paused)

