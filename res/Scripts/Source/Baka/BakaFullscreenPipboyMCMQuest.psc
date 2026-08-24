Scriptname BakaFullscreenPipboyMCMQuest extends Quest Hidden

Event OnQuestInit()
	Register()
	RegisterForRemoteEvent(Game.GetPlayer(), "OnPlayerLoadGame")
EndEvent

Event Actor.OnPlayerLoadGame(Actor akSender)
	Register()
EndEvent

Function Register()
	RegisterForExternalEvent("OnMCMClose", "OnMCMClose")
EndFunction

Function OnMCMClose()
	BakaFullscreenPipboy.UpdateSettings()
EndFunction
