extends Node


var ACF_FILE = "res://sound/ADX2_samples.acf"
var ACB_FILES = [
	["res://sound/Basic.acb", "res://sound/Basic.awb"],
	["res://sound/3Dpos.acb", null],
	["res://sound/InteractiveSound.acb", "res://sound/InteractiveSound.awb"]
]

var context: Object
var voice_pool_memory: Object
var voice_pool_stream: Object
var voice_pool_hcamx: Object
var acbs: Array
var player: Object
var source3d: Object
var listener3d: Object

func _ready():
	# Setup Library
	context = CriAtomExContext.new();
	context.initialize(ACF_FILE, {
		"max_streams": 8,
		"max_virtual_voices": 100,
		"hca_mx_sampling_rate": 32000,
	})
	
	# Setup Voice Pool
	voice_pool_memory = CriAtomExVoicePool.allocate_standard_voice_pool({"num_voices": 32, "max_sampling_rate": 96000})
	voice_pool_stream = CriAtomExVoicePool.allocate_standard_voice_pool({"num_voices": 8, "max_sampling_rate": 96000, "streaming_flag": true})
	voice_pool_hcamx = CriAtomExVoicePool.allocate_hcamx_voice_pool({"num_voices": 32, "max_sampling_rate": 32000})
	
	# Load ACB file
	for acb_file in ACB_FILES:
		var acb = CriAtomExAcb.load_acb_file(acb_file[0], acb_file[1])
		acbs.append(acb)
	
	# Setup 3D objects
	source3d = CriAtomEx3dSource.create({})
	listener3d = CriAtomEx3dListener.create({})
	
	# Setup Player
	player = CriAtomExPlayer.create({})
	player.set_3d_source(source3d)
	player.set_3d_listener(listener3d)


func play(name: String):
	player.set_cue_name(null, name)
	return player.start()


func stop_all():
	player.stop()


func pause_all(paused: bool):
	player.pause(paused)

