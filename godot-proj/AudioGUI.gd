extends CanvasLayer

@onready var cue_dropdown := $TabWindow/Playback/Split/Playback/CueDropdown
@onready var status_label := $TabWindow/Playback/Split/Playback/PlayStatus

@onready var status_strings := CriAtomEx.PlayerStatus.keys()

func _ready():
	var index = 0
	for acb in AudioMgr.acbs:
		var cues = acb.get_all_cue_infos()
		for cue in cues:
			cue_dropdown.add_item(cue.name, index)
			index += 1


func _process(_delta: float):
	status_label.text = "Status: %s  Time: %d" % [status_strings[AudioMgr.player.get_status()], AudioMgr.player.get_time()]


func _on_play_button_down():
	var cue_name = cue_dropdown.get_item_text(cue_dropdown.get_selected_id())
	AudioMgr.play(cue_name)


func _on_stop_button_down():
	AudioMgr.stop_all()


func _on_pause_toggled(button_pressed: bool):
	AudioMgr.pause_all(button_pressed)


func _on_volume_changed(value: float):
	AudioMgr.player.set_volume(value)
	AudioMgr.player.update_all()


func _on_pitch_changed(value: float):
	AudioMgr.player.set_pitch(value)
	AudioMgr.player.update_all()


func _on_pan_changed(value: float):
	AudioMgr.player.set_pan3d_angle(value)
	AudioMgr.player.update_all()
